//-----------------------------------------------------------
//  Purpose:    Header file for the Graph class.
//  Author:     John Gauch
//-----------------------------------------------------------

#include "heap2.h"
#include <time.h>
#include <climits>
#include <iostream>
using namespace std;

#define GRAPH_SIZE 2000
#define MAX_DISTANCE 1000000

//-----------------------------------------------------------
// Define the GraphNode class interface 
//-----------------------------------------------------------
class GraphNode
{
public:
   int Distance;
   int Previous;
   int Handle;
};

//-----------------------------------------------------------
// Define the Graph class interface 
//-----------------------------------------------------------
class Graph
{
 public:
   // Constructors
   Graph();
   Graph(const Graph & graph);
    ~Graph();

   // Methods
   bool GetWeight(int row, int col, int &weight);
   bool SetWeight(int row, int col, int weight);
   bool SetBiWeight(int row, int col, int weight);
   bool GetNode(int row, GraphNode &node);
   bool SetNode(int row, GraphNode node);
   void FindPath(int start, int end, string &path, int &distance);
   void Print();

 private:
   int Weight[GRAPH_SIZE][GRAPH_SIZE];
   GraphNode Node[GRAPH_SIZE];
   int Size;
};
