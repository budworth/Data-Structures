/***********************************************************************
 * Header:
 *    Heap Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

template <class T>
class Heap
{
  public:
   // non default constructor  (takes an array and the num)
   Heap(T * array, int num);
   
   // destructor
   ~Heap(){};
   
   // getMax returns myArray[1]
   T & getMax() {return *(array + 1);}
   
   // deleteMax() needs to delete myArray[1] assigns myArray[num] to myArray[1] /
   void deleteMax();

   // heapify
   void heapify();
   
   // sort
   void sort();

   // percolateDown
   void percolateDown(int index);
   
  private:
  
   T * array; // this is the data content array
   int num;   // number of elements
   int left(int index) {if (index * 2 <= num) return (index * 2); else return -1;}
   int right(int index) {if (index * 2 + 1 <= num) return (index * 2  + 1); else return -1;}
   int parent(int index) {if (index > 1) return (index / 2); else return -1;}
   
};

/*****************************************************
 * defined constructor
 ****************************************************/
template <class T>
Heap <T> :: Heap(T * array, int num)
{
   this->array = array;
   this->num = num;

   --this->array;
}

/*****************************************************
 * deleteMax() : deletes myArray[1] and replaces it
 * with the num elements to the first position
 ****************************************************/
template <class T>
void Heap<T>::deleteMax()
{
   if(num > 1)
   {
      T tmp = *(array + 1);
      *(array + 1) = *(array + num);
      *(array + num) = tmp;
   }

   num--;
   
}

/*****************************************************
 * heapify() : 
 ****************************************************/
template <class T>
void Heap<T>::heapify()
{

   // for r = num / 2 down to 1 // start at the last nonleaf
   int index = num / 2;
   // apply percolatedown() to the subtree myArray[r] to myArray[num]
   while(index >= 1)
   {
      percolateDown(index);
      index--;
   }
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort, this is the display function
 * essentialy
 ****************************************************/
template <class T>
void sortHeap(T *array, int num)
{
   // create a heap
   Heap <T> heap(array, num);

   // heapify the semi heap, and then sort it.
   heap.heapify();
   heap.sort();
}

/*****************************************************
 * heapSort : sorts the heap
 * position 0 is reserved for some reason or another
 * consider x to be our tree array
 *******************************************************/
template <class T>
void Heap <T>:: sort()
{
   while (num > 0)
   {
      deleteMax(); // go to the first element or root
      percolateDown(1); // why one you ask? because it
                        // increments down the list
   }
   
}

/*****************************************************
 * percolateDown: 
 *******************************************************/
template <class T>
void Heap<T>:: percolateDown(int index)
{
   int leftC = left(index);
   int rightC = right(index);
   
   if(leftC > 0 && rightC > 0)
   {
      if(*(array + leftC) > *(array + index) || *(array + rightC) > *(array + index))
      {
         if(*(array + leftC) > *(array + rightC))
         {
            T tmp = *(array + index);
            *(array + index) = *(array + leftC);
            *(array + leftC) = tmp;
            percolateDown(leftC); // go down the left node
         }
         else
         {
            T tmp = *(array + index);
            *(array + index) = *(array + rightC);
            *(array + rightC) = tmp;
            percolateDown(rightC); // go down the right node       
         }
      }
   }
   else if (leftC > 0)
   {
      if((*(array + leftC) > *(array + index)))
      {
         T tmp = *(array + index);
         *(array + index) = *(array + leftC);
         *(array + leftC) = tmp;
         percolateDown(leftC); // go down the right node       
      }
      
   }
}


#endif // SORT_HEAP_H
