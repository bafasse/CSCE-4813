//------------------------------------------------------------
// Purpose: Implementation of integer Heap class.
// Author:  John Gauch
//------------------------------------------------------------
#include "heap2.h"

//------------------------------------------------------------
// Constructor function.
//------------------------------------------------------------
Heap::Heap()
{
   HeapCount = 0;
   MapCount = 0;
   for (int index = 0; index <= MAX_HEAP_SIZE; index++)
   {
      heap[index].key = 0;
      heap[index].value = 0;
      heap[index].handle = 0;
      heap_map[index] = 0;
   }
}

//------------------------------------------------------------
// Destructor function.
//------------------------------------------------------------
Heap::~Heap()
{
}

//------------------------------------------------------------
// Insert an element into the heap.
//------------------------------------------------------------
bool Heap::Insert(HeapNode node, int &handle)
{
   // Check for full heap
   if (IsFull())
      return false;

   // Shuffle data up the heap
   HeapCount++;
   int child = HeapCount;
   int parent = child / 2;
   while ((child > 1) && (heap[parent].key > node.key))
   {
      heap_map[ heap[parent].handle ] = child;
      heap[child] = heap[parent];
      child = parent;
      parent = child / 2;
   }

   // Insert new entry in heap
   node.handle = MapCount++;
   heap_map[ node.handle ] = child;
   heap[child] = node;
   handle = node.handle;
   return true;
}

//------------------------------------------------------------
// Remove an element from the heap.
//------------------------------------------------------------
bool Heap::Remove(HeapNode &node)
{
   // Check for empty heap
   if (IsEmpty())
      return false;

   // Save top of heap
   heap_map[ heap[1].handle ] = 0;
   node = heap[1];

   // Swap last value into root position
   if (HeapCount > 1)
   {
      heap_map[ heap[HeapCount].handle ] = 1;
      heap[1] = heap[HeapCount];
   }
   HeapCount--;

   // Shuffle data down the heap
   int parent = 1;
   int smallest = 0;
   while (parent != smallest)
   {
      // Check left node
      smallest = parent;
      int left = parent * 2;
      if ((left <= HeapCount) && (heap[left].key < heap[smallest].key))
	 smallest = left;

      // Check right node
      int right = left + 1;
      if ((right <= HeapCount) && (heap[right].key < heap[smallest].key))
	 smallest = right;

      // Swap data values if needed
      if (parent != smallest)
      {
         heap_map[ heap[parent].handle ] = smallest;
         heap_map[ heap[smallest].handle ] = parent;
	 HeapNode temp = heap[parent];
	 heap[parent] = heap[smallest];
	 heap[smallest] = temp;
	 parent = smallest;
	 smallest = 0;
      }
   }
   return true;
}

//------------------------------------------------------------
// Print the contents of the heap.
//------------------------------------------------------------
void Heap::Print()
{
   // Print (key,handle) values
   for (int index = 1; index <= HeapCount; index++)
      cout << "(" << heap[index].key 
           << " " << heap[index].handle << ") ";
   cout << endl;

   // Print heap_map values
   for (int index = 0; index < MapCount; index++)
      cout << heap_map[index] << " ";
   cout << endl;
}

//------------------------------------------------------------
// Check if the heap is empty
//------------------------------------------------------------
bool Heap::IsEmpty()
{
   return HeapCount == 0;
}

//------------------------------------------------------------
// Check if the heap is full
//------------------------------------------------------------
bool Heap::IsFull()
{
   return (HeapCount == MAX_HEAP_SIZE);
}

//------------------------------------------------------------
// Get key using handle
//------------------------------------------------------------
int Heap::GetKey(int handle)
{
   if ((handle >= 0) && (handle <= MapCount) &&
      (heap_map[handle] > 0) && (heap_map[handle] <= HeapCount))
      return heap[ heap_map[handle] ].key; 
   else
      return -1;
}

//------------------------------------------------------------
// Get value using handle
//------------------------------------------------------------
int Heap::GetValue(int handle)
{
   if ((handle >= 0) && (handle <= MapCount) &&
      (heap_map[handle] > 0) && (heap_map[handle] <= HeapCount))
      return heap[ heap_map[handle] ].value; 
   else
      return -1;
}

//------------------------------------------------------------
// Decrease key using handle
//------------------------------------------------------------
bool Heap::DecreaseKey(int handle, int key)
{
   int index = heap_map[handle];
   if (heap[index].key < key)
      return false;
   else
   {
      // Save key value
      HeapNode node;
      node.key = key;
      node.value = heap[index].value;
      node.handle = heap[index].handle;

      // Shuffle data up the heap
      int child = index;
      int parent = child / 2;
      while ((child > 1) && (heap[parent].key > node.key))
      {
         heap_map[ heap[parent].handle ] = child;
         heap[child] = heap[parent];
         child = parent;
         parent = child / 2;
      }

      // Save node
      heap_map[ node.handle ] = child;
      heap[child] = node;
      return true;
   }
}

#ifdef HEAP_MAIN
//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
int main()
{
   Heap heap;
   HeapNode node;
   int data[10] = {3,1,4,1,5,9,3,6,5,3};
   int handle[10];

   // Test insert operations
   for (int i = 0; i < 10; i++)
   {
      node.key = data[i];
      node.value = 0;
      node.handle = 0;
      heap.Insert( node, handle[i] );
      cout << "insert " << data[i] << " " << handle[i] << endl;
      heap.Print();
   }

   // Test handle operations
   for (int i = 0; i < 10; i++)
   {
      cout << "decrease " << i << " " << heap.GetKey(handle[i]) << " " << i << endl;
      heap.DecreaseKey(handle[i], i);
      heap.Print();
   }

   // Test remove operations
   while (heap.Remove( node ))
   {
      cout << "remove " << node.key << " " << node.handle << endl;
      heap.Print();
   }
}
#endif
