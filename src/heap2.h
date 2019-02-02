//------------------------------------------------------------
// Purpose: Header file for the Heap class.
// Author:  John Gauch
//------------------------------------------------------------
#include <iostream>
using namespace std;

//------------------------------------------------------------
// The data HeapNode for Heap class
//------------------------------------------------------------
class HeapNode
{
public:
   int key;
   int value;
   int handle;
};

//------------------------------------------------------------
// The Heap class definition for a heap of HeapNodes 
//------------------------------------------------------------
class Heap
{
 public:
   // Constructor functions
   Heap();
   ~Heap();

   // General heap operation
   bool Insert(HeapNode node, int &handle);
   bool Remove(HeapNode &node);
   bool IsEmpty();
   bool IsFull();
   void Print();
   int GetKey(int handle);
   int GetValue(int handle);
   bool DecreaseKey(int handle, int key);

 private:
   int HeapCount;
   int MapCount;
   static const int MAX_HEAP_SIZE = 2000;
   HeapNode heap[MAX_HEAP_SIZE+1];
   int heap_map[MAX_HEAP_SIZE+1];
};

