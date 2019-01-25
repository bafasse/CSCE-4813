//----------------------------------------------
// Purpose: Implement simple Graph class.
// Author:  John Gauch
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "graph3.h"

//----------------------------------------------
// Constructor function.
//----------------------------------------------
Graph::Graph()
{
   for (int row = 0; row < GRAPH_SIZE; row++)
      for (int col = 0; col < GRAPH_SIZE; col++)
	 Weight[row][col] = -1;
   for (int row = 0; row < GRAPH_SIZE; row++)
   {
      Node[row].Distance = -1;
      Node[row].Previous = -1;
      Node[row].Handle = -1;
   }
   Size = 0;
}

//----------------------------------------------
// Constructor function.
//----------------------------------------------
Graph::Graph(const Graph & g)
{
   for (int row = 0; row < GRAPH_SIZE; row++)
      for (int col = 0; col < GRAPH_SIZE; col++)
	 Weight[row][col] = g.Weight[row][col];
   for (int row = 0; row < GRAPH_SIZE; row++)
      Node[row] = g.Node[row];
   Size = g.Size;
}

//----------------------------------------------
// Destructor function.
//----------------------------------------------
Graph::~Graph()
{
   for (int row = 0; row < GRAPH_SIZE; row++)
      for (int col = 0; col < GRAPH_SIZE; col++)
	 Weight[row][col] = -1;
   for (int row = 0; row < GRAPH_SIZE; row++)
   {
      Node[row].Distance = -1;
      Node[row].Previous = -1;
      Node[row].Handle = -1;
   }
   Size = 0;
}

//----------------------------------------------
// Get weight at Weight[row][col].
//----------------------------------------------
bool Graph::GetWeight(int row, int col, int &weight)
{
   if ((row < 0) || (row >= GRAPH_SIZE) ||
       (col < 0) || (col >= GRAPH_SIZE) || 
       (Weight[row][col] < 0))
      return false;
   else
      weight = Weight[row][col];
   return true;
}

//----------------------------------------------
// Set weight at Weight[row][col].
//----------------------------------------------
bool Graph::SetWeight(int row, int col, int weight)
{
   if ((row < 0) || (row >= GRAPH_SIZE) || 
       (col < 0) || (col >= GRAPH_SIZE))
      return false;
   else
      Weight[row][col] = weight;
   if (Size < row)
      Size = row;
   if (Size < col)
      Size = col;
   return true;
}

//----------------------------------------------
// Set weight at Weight[row][col] and Weight[col][row].
//----------------------------------------------
bool Graph::SetBiWeight(int row, int col, int weight)
{
   return (SetWeight(row, col, weight) && 
           SetWeight(col, row, weight));
}

//----------------------------------------------
// Get node Node[row].
//----------------------------------------------
bool Graph::GetNode(int row, GraphNode &node)
{
   if ((row < 0) || (row >= GRAPH_SIZE))
      return false;
   else
      node = Node[row];
   return true;
}

//----------------------------------------------
// Set node Node[row].
//----------------------------------------------
bool Graph::SetNode(int row, GraphNode node)
{
   if ((row < 0) || (row >= GRAPH_SIZE))
      return false;
   else
      Node[row] = node;
   if (Size < row)
      Size = row;
   return true;
}

//----------------------------------------------
// Find path using Dijkstra's algorithm.
//----------------------------------------------
void Graph::FindPath(int start, int end, string &path, int &distance)
{
   // Declare variables
   HeapNode hnode;
   Heap heap;
   GraphNode gnode;
   int current = start;
   int weight = 0;
   char temp[100];

   // Initialize graph and heap
   for (int i=1; i<=Size; i++)
   {
      // Set distance
      if (i == start)
         gnode.Distance = 0;
      else
         gnode.Distance = MAX_DISTANCE;

      // Insert heap node
      hnode.key = gnode.Distance;
      hnode.value = i;
      if (!heap.IsFull())
         heap.Insert(hnode, gnode.Handle);

      // Set graph node
      gnode.Previous = -1;
      SetNode(i, gnode);
   }

   // Traverse graph to find path
   while (!heap.IsEmpty() && current != end)
   {
      // Select node from heap
      heap.Remove(hnode);
      current = hnode.value;
      distance = hnode.key;

      // Follow all edges
      for (int neighbor = 0; neighbor <= Size; neighbor++)
      if (current != neighbor && GetWeight(current, neighbor, weight))
      {
         // Calculate distance to neighbor
         GetNode(neighbor, gnode);
         int new_distance = distance + weight;
         if (gnode.Distance > new_distance)
         {
            gnode.Distance = new_distance;
            gnode.Previous = current;
            SetNode(neighbor, gnode);
            heap.DecreaseKey(gnode.Handle, new_distance);
         }
      }
   }

   // Check for no shortest path
   path = "";
   if (distance >= MAX_DISTANCE)
   {
      distance = 0;
      return;
   }
   
   // Print out shortest path
   current = end;
   while (current != start)
   {
      sprintf(temp, "%d ", current);
      path = temp + path;
      GetNode(current, gnode);
      current = gnode.Previous;
   } 
   sprintf(temp, "%d ", current);
   path = temp + path;
}

//----------------------------------------------
// Print contents of graph.
//----------------------------------------------
void Graph::Print()
{
   // Print weights
   cout << "\nWeight information:\n";
   for (int row = 1; row <= Size; row++)
   {
      cout << "row " << row << " ";
      for (int col = 0; col <= Size; col++)
	 if (Weight[row][col] >= 0)
	    cout << "(" << col << "," << Weight[row][col] << ") ";
      cout << endl;
   }

   // Print nodes
   cout << "\nNode information:\n";
   for (int row = 1; row <= Size; row++)
   {
      cout << "row " << row << " ";
      cout << Node[row].Distance << " ";
      cout << Node[row].Previous << " ";
      cout << Node[row].Handle << endl;
   }
}

#ifdef GRAPH_MAIN
//-----------------------------------------------------------
// Testing function
//-----------------------------------------------------------
int main()
{
   Graph graph;

   // Create graph with 6 nodes
   graph.SetBiWeight(1, 2, 7);
   graph.SetBiWeight(1, 3, 9);
   graph.SetBiWeight(1, 6, 14);
   graph.SetBiWeight(2, 3, 10);
   graph.SetBiWeight(2, 4, 15);
   graph.SetBiWeight(3, 4, 11);
   graph.SetBiWeight(3, 6, 2);
   graph.SetBiWeight(4, 5, 6);
   graph.SetBiWeight(5, 6, 9);
   graph.Print();

   // Find path from node 2 to 6
   string path;
   int distance;
   graph.FindPath(1, 5, path, distance);
   cout << "\nFindPath 1 5\n";
   cout << "path: " << path << endl;
   cout << "distance: " << distance << endl;
   graph.Print();
   return 0;
}
#endif
