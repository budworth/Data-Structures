/***********************************************************************
 * Header:
 *    Hash Class
 * Summary:
 *    This is the hash.h class, it will implement a pure virtual function
 *     of a hash class data type.
 * Author
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 ************************************************************************/

#ifndef HASH_H
#define HASH_H

#include <cassert>
#include <string>
#include <iostream>
#include <list>
using namespace std;
/************************************************
 * Hash
 * A class that holds stuff   
 ***********************************************/
template <class T>
class Hash
{
    
  public:
   // default constructor
  Hash() : numBuckets(0), cap(0), data(0) {}
   
   // non-default constructor numbuckets will become the cap inserted
  Hash(int numBuckets) : numBuckets(0), cap(numBuckets), data(NULL) {}

   // copy constructor
  Hash(const Hash & rhs);

   // destructor                
   ~Hash(){}

   // assignment operator
   Hash<T> & operator = (const Hash<T> & rhs);
  
   bool empty()     { if(numBuckets == 0) return true; else return false; }
    
   // how many items are currently in the Queue?
   int size() const { return numBuckets; }
   
   // capacity function will return the capacity of the storage
   int capacity()const   { return cap; }

   void clear();

   bool find(T value);
   
   void insert(T value);

   // hash() : THis is a pure virtual function taken an element as a parameter
   //          and returning an index into the underlying array
   
   virtual int hash(const T & value) const { return 0; }


   
  private:
   //std:: list <T> listArray[];
   int cap;	 // array capacity
   int numBuckets;// keep track of the number of items
   list<T> * data;
};

/*******************************************************************************
 * Clear : Clears the contents, takes no parameters and returns nothing
 ******************************************************************************/
template <class T>
void Hash<T>::clear()
{
   for(int i = 0; i < size(); i++)
   {
      delete data[i];
   }
   numBuckets = 0;
   cap = 0;
}

/*******************************************************************************
 * Find : 
******************************************************************************/
template <class T>
bool Hash<T>::find(T value)
{
	int index = hash(value);

   if(data[index].front() == value)
      return true;
   else
      return false;
   
}

/*******************************************************************************
 * Insert : Array[hash(value)] = value
 * this way it returns an interget or float with the driver class.
******************************************************************************/
template <class T>
void Hash<T>::insert(T value)
{
	try
	{
		data = new list<T>;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	int index = hash(value);
	data[index].push_back(value);
    numBuckets++;

}

template<class T>
inline Hash<T>::Hash(const Hash & rhs)
{
	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = numBuckets = 0;
		data = 0x00000000;
		return;
	}

	// attempt to allocate
	try
	{
		data = new list<T>[rhs.cap];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the capacity and size
	//assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capacity);
	cap = rhs.cap;
	numBuckets = rhs.numBuckets;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numBuckets; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numBuckets; i < cap; i++)
		data[i] = list<T>();
}

/******************************************************************************
 * Assignment operator : copys one hash to another.
 *****************************************************************************/
template <class T>
Hash<T> & Hash <T> ::operator = (const Hash<T> & rhs)
{
   // assigns the cap to the rhs cap
   cap = rhs.capacity();
   // assigns the number of buckets to the rhs buckets
   numBuckets = rhs.size();

   return *this;
}

   
#endif // HASH_H
