//-----------------------------------------------------------
// Purpose: Implementation of 3D tic-tac-toe
// Author:  John Gauch
//-----------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

const char empty = ' ';
const char user = 'x';
const char computer = 'o';
const int NUM_ROWS = 76;

class Board
{
public:
   Board();
   void user_move(char player);
   void chimp_mode(int & lev, int & row, int & col);
   void kindergarten_mode(int & lev, int & row, int & col);
   void professor_mode(int & lev, int & row, int & col);
   void wizard_mode(int & lev, int & row, int & col);
   void computer_move(char player, char level);
   void print();
   int count(int lev1, int row1, int col1, 
      int lev2, int row2, int col2, char player);
   bool winner(char player);

private:
   char board[4][4][4];
   int rows[NUM_ROWS][6];
};

//-----------------------------------------------------------
Board::Board()
{
   // Initialize board to empty character
   for (int lev=0; lev<4; lev++)
   for (int row=0; row<4; row++)
   for (int col=0; col<4; col++)
      board[lev][row][col] = empty;

   // Read rows.txt file
   ifstream din;
   din.open("rows.txt");
   for (int i=0; i<NUM_ROWS; i++)
   for (int j=0; j<6; j++)
      din >> rows[i][j];
   din.close();
}

//-----------------------------------------------------------
void Board::user_move(char player)
{
   int lev, row, col;
   do {
      // Prompt user for their move
      cout << "\nEnter " << (char)toupper(player) << " move: ";
      cin >> lev >> row >> col;
   } while ((lev < 1) || (lev > 4) || 
            (row < 1) || (row > 4) || 
            (col < 1) || (col > 4) ||
            (board[lev-1][row-1][col-1] != empty));

   // Perform move
   board[lev-1][row-1][col-1] = player;
}

//-----------------------------------------------------------
void Board::chimp_mode(int & lev, int & row, int & col)
{
   do {
      // Choose random position
      lev = random() % 4;
      row = random() % 4;
      col = random() % 4;
   } while (board[lev][row][col] != empty);
}

//-----------------------------------------------------------
void Board::kindergarten_mode(int & lev, int & row, int & col)
{
   // Choose center position
   lev = random() % 2 + 1;
   row = random() % 2 + 1;
   col = random() % 2 + 1;
   if (board[lev][row][col] != empty)
   {
      // Choose corner position
      lev = random() % 2 * 3;
      row = random() % 2 * 3;
      col = random() % 2 * 3;
   }
   while (board[lev][row][col] != empty)
   {
      // Choose random position
      lev = random() % 4;
      row = random() % 4;
      col = random() % 4;
   }
}

//-----------------------------------------------------------
void Board::professor_mode(int & lev, int & row, int & col)
{
   // Loop over all possible rows
   int max_count = 0;
   int max_index = 0;
   for (int i=0; i<NUM_ROWS; i++)
   {
      // Calculate counts
      // locations 0,1,2 are starting point
      // locations 3,4,5 are ending poing
      int user_count = count(rows[i][0],rows[i][1],rows[i][2], 
                             rows[i][3],rows[i][4],rows[i][5], user);
      int computer_count = count(rows[i][0],rows[i][1],rows[i][2], 
                                 rows[i][3],rows[i][4],rows[i][5], computer);

      // Find best row
      if ((user_count >= max_count) && (computer_count == 0))
      {
         max_count = user_count;
         max_index = i;
      }
      if ((computer_count >= max_count) && (user_count == 0))
      {
         max_count = computer_count;
         max_index = i;
      }
   }

   // Find first empty position
   lev = rows[max_index][0];
   row = rows[max_index][1];
   col = rows[max_index][2];
   for (int step = 0; step < 4; step++)
   {
      if (board[lev][row][col] == empty) 
         break;
      lev += (rows[max_index][3]-rows[max_index][0])/3;
      row += (rows[max_index][4]-rows[max_index][1])/3;
      col += (rows[max_index][5]-rows[max_index][2])/3;
   }
}

//-----------------------------------------------------------
void Board::wizard_mode(int & lev, int & row, int & col)
{
   // Initialize total score
   int total[4][4][4];
   for (int l=0; l<4; l++)
   for (int r=0; r<4; r++)
   for (int c=0; c<4; c++)
      total[l][r][c] = 0;

   // Loop over all possible rows
   for (int i=0; i<NUM_ROWS; i++)
   {
      // Calculate counts for this row
      // locations 0,1,2 are starting point
      // locations 3,4,5 are ending poing
      int user_count = count(rows[i][0],rows[i][1],rows[i][2], 
                             rows[i][3],rows[i][4],rows[i][5], user);
      int computer_count = count(rows[i][0],rows[i][1],rows[i][2], 
                                 rows[i][3],rows[i][4],rows[i][5], computer);

      // Calculate score for this row
      int score = 0;
      if (user_count == 0)
         score = (int)pow(5.0, computer_count);
      if (computer_count == 0)
         score = (int)pow(5.0, user_count);

      // Add to total score
      lev = rows[i][0];
      row = rows[i][1];
      col = rows[i][2];
      for (int step = 0; step < 4; step++)
      {
         if (board[lev][row][col] == empty) 
            total[lev][row][col] += score;
         lev += (rows[i][3]-rows[i][0])/3;
         row += (rows[i][4]-rows[i][1])/3;
         col += (rows[i][5]-rows[i][2])/3;
      }
   }

   // Find best location on the board
   lev = random() % 4;
   row = random() % 4;
   col = random() % 4;
   int max = total[lev][row][col];
   for (int l=0; l<4; l++)
   for (int r=0; r<4; r++)
   for (int c=0; c<4; c++)
   {
      if (total[l][r][c] > max)
      {
         lev = l;
         row = r;
         col = c;
         max = total[lev][row][col];
      }
   }
}

//-----------------------------------------------------------
void Board::computer_move(char player, char level)
{
   // Perform chimp mode move
   int lev=0, row=0, col=0;
   if (level == 'c')
      chimp_mode(lev, row, col);

   // Perform kindergarten mode move
   else if (level == 'k')
      kindergarten_mode(lev, row, col);

   // Perform professor mode
   else if (level == 'p')
      professor_mode(lev, row, col);

   // Perform wizard mode
   else if (level == 'w')
      wizard_mode(lev, row, col);

   // Perform move
   cout << "\n" << (char)toupper(player) << " move " 
        << lev+1 << " " << row+1 << " " << col+1 << endl;
   board[lev][row][col] = player;
}

//-----------------------------------------------------------
void Board::print()
{
   // Loop over rows lev col to print board
   for (int row=0; row<4; row++)
   {
      cout << "  +---+---+---+---+   +---+---+---+---+   +---+---+---+---+   +---+---+---+---+\n";
      for (int lev=0; lev<4; lev++)
      {
         cout << "  | "; 
         for (int col=0; col<4; col++)
            cout << board[lev][row][col] << " | ";
      }
      cout << endl;
   }
   cout << "  +---+---+---+---+   +---+---+---+---+   +---+---+---+---+   +---+---+---+---+\n";

}

//-----------------------------------------------------------
int Board::count(int lev1, int row1, int col1, 
   int lev2, int row2, int col2, char player)
{
   // Check endpoints are valid
   // cout << lev1 << " " << row1 << " " << col1 << " " 
   //      << lev2 << " " << row2 << " " << col2 << endl;
   if ((lev1 < 0) || (lev1 > 3) || (row1 < 0) || 
       (row1 > 3) || (col1 < 0) || (col1 > 3) ||
       (lev2 < 0) || (lev2 > 3) || (row2 < 0) || 
       (row2 > 3) || (col2 < 0) || (col2 > 3))
      return 0;
   if ((lev1 == lev2) && (row1 == row2) && (col1 == col2)) 
      return 0;

   // Loop over four positions
   int count = 0;
   int lev = lev1;
   int row = row1;
   int col = col1;
   for (int step = 0; step < 4; step++)
   {
      // Count number of matching moves
      if (board[lev][row][col] == player) 
         count++;
      lev += (lev2-lev1)/3;
      row += (row2-row1)/3;
      col += (col2-col1)/3;
   }
   return count;
}

//-----------------------------------------------------------
bool Board::winner(char player)
{
   // Loop over all possible rows
   for (int i=0; i<NUM_ROWS; i++)
   {
      // Check for tic-tac-toe
      // locations 0,1,2 are starting point
      // locations 3,4,5 are ending poing
      if (count(rows[i][0],rows[i][1],rows[i][2], 
                rows[i][3],rows[i][4],rows[i][5], player) == 4)
      {
         // Loop over four positions
         int lev = rows[i][0];
         int row = rows[i][1];
         int col = rows[i][2];
         for (int step = 0; step < 4; step++)
         {
            // Highlight move
            board[lev][row][col] = toupper(player);
            lev += (rows[i][3]-rows[i][0])/3;
            row += (rows[i][4]-rows[i][1])/3;
            col += (rows[i][5]-rows[i][2])/3;
         }
         return true;
      }
   }
   return false;
}

//-----------------------------------------------------------
int main()
{
   // Get game difficulty level\n";
   srandom(time(NULL));
   if (system("clear") == -1)
      printf("Error: could not execute system command\n");
   cout << "Welcome to John's 3D tic-tac-toe program\n";
   char level;
   do {
      cout << "  c) chimp mode\n";
      cout << "  k) kindergarten mode\n";
      cout << "  p) professor mode\n";
      cout << "  w) wizard mode\n";
      cout << "Enter difficulty level: ";
      cin >> level;
   } while ((level != 'c') && (level != 'k') && 
            (level != 'p') && (level != 'w'));

   Board board;
   while (true)
   {
      // Process user move
      board.print();
      board.user_move(user);
      if (board.winner(user))
      {
         board.print();
         cout << "\nCongratulations, You win!!!\n";
         return 0;
      }
      
      // Process computer move
      board.print();
      board.computer_move(computer, level);
      if (board.winner(computer))
      {
         board.print();
         cout << "\nSorry, You lose...\n";
         return 0;
      }
   }
}
