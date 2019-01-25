//-----------------------------------------------------------
// Purpose: Implementation of 3D tic-tac-toe
// Author:  John Gauch
//-----------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const char empty = ' ';
const char user = 'x';
const char computer = 'o';

class Board
{
public:
   Board();
   void user_move(char player);
   void chimp_mode(int & lev, int & row, int & col);
   void kindergarten_mode(int & lev, int & row, int & col);
   void professor_mode(int & lev, int & row, int & col);
   void computer_move(char player, char level);
   void print();
   int count(int lev1, int row1, int col1, 
      int lev2, int row2, int col2, char player);
   bool winner(char player);

private:
   char board[4][4][4];
};

//-----------------------------------------------------------
Board::Board()
{
   // Initialize board to empty character
   for (int lev=0; lev<4; lev++)
   for (int row=0; row<4; row++)
   for (int col=0; col<4; col++)
      board[lev][row][col] = empty;
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
   bool offense = (random() % 2 == 0);
   int max_count = 0;
   int max_lev1 = 0; 
   int max_row1 = 0; 
   int max_col1 = 0; 
   int max_lev2 = 0; 
   int max_row2 = 0; 
   int max_col2 = 0; 

   // Loop over starting points
   for (int lev1=0; lev1<4; lev1++)
   for (int row1=0; row1<4; row1++)
   for (int col1=0; col1<4; col1++)
   {
      // Loop over ending points
      for (int lev2=lev1-3; lev2<4; lev2+=3)
      for (int row2=row1-3; row2<4; row2+=3)
      for (int col2=col1-3; col2<4; col2+=3)
      {
         // Calculate counts
         int user_count = count(lev1,row1,col1, lev2,row2,col2, user);
         int computer_count = count(lev1,row1,col1, lev2,row2,col2, computer);

         // Find best row
         if (offense && (computer_count >= max_count) && (user_count == 0))
         {
            max_count = computer_count;
            max_lev1 = lev1; 
            max_row1 = row1; 
            max_col1 = col1; 
            max_lev2 = lev2; 
            max_row2 = row2; 
            max_col2 = col2; 
         }
         else if (!offense && (user_count >= max_count) && (computer_count == 0))
         {
            max_count = user_count;
            max_lev1 = lev1; 
            max_row1 = row1; 
            max_col1 = col1; 
            max_lev2 = lev2; 
            max_row2 = row2; 
            max_col2 = col2; 
         }
      }
   }

   // Find first empty position
   lev = max_lev1;
   row = max_row1;
   col = max_col1;
   for (int step = 0; step < 4; step++)
   {
      if (board[lev][row][col] == empty) 
         break;
      lev += (max_lev2-max_lev1)/3;
      row += (max_row2-max_row1)/3;
      col += (max_col2-max_col1)/3;
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
   // Loop over starting points
   for (int lev1=0; lev1<4; lev1++)
   for (int row1=0; row1<4; row1++)
   for (int col1=0; col1<4; col1++)
   {
      // Loop over ending points
      for (int lev2=lev1-3; lev2<4; lev2+=3)
      for (int row2=row1-3; row2<4; row2+=3)
      for (int col2=col1-3; col2<4; col2+=3)
      {
         // Check for tic-tac-toe
         if (count(lev1,row1,col1, lev2,row2,col2, player) == 4)
         {
            // Loop over four positions
            int lev = lev1;
            int row = row1;
            int col = col1;
            for (int step = 0; step < 4; step++)
            {
               // Highlight move
               board[lev][row][col] = toupper(player);
               lev += (lev2-lev1)/3;
               row += (row2-row1)/3;
               col += (col2-col1)/3;
            }
            return true;
         }
      }
   }
   return false;
}

//-----------------------------------------------------------
int main()
{
   // Get game difficulty level\n";
   if (system("clear") == -1)
      printf("Error: could not execute system command\n");
   cout << "Welcome to John's 3D tic-tac-toe program\n";
   char level;
   do {
      cout << "  c) chimp mode\n";
      cout << "  k) kindergarten mode\n";
      cout << "  p) professor mode\n";
      cout << "Enter difficulty level: ";
      cin >> level;
   } while ((level != 'c') && (level != 'k') && (level != 'p'));

   Board board;
   srandom(time(NULL));
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
