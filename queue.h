/***********************************************************************
* Header:
*    Queue Class
* Summary:
*    This class contains the notion of a Queue:
*    a queue allows the user to add elements to the
*    the back of the line and pop from the front of the line.
*
*    This will contain the class definition of:
*        Deque          : A class that holds stuff
* Author
*    Bud Wortham, David Pruitt, and Tyler Stanley
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cassert>

using namespace std;

template <class T>
class Queue
{
public:
	Queue() : myFront(0), myBack(0), capacityInt(0), numItems(0) { array = new T[capacityInt]; }
	//--Default Constructor

	Queue(int cap) : myFront(0), myBack(0), capacityInt(0), numItems(0) { capacityInt = cap;  array = new T[cap]; }
	//--Non-Default Constructor. Takes Capacity as Parameter

	Queue(const Queue<T> & rhs);
	//--Copy Constuctor

	~Queue() { delete[] array; }
	//--Destructor

	Queue & operator = (const Queue <T> & rhs);
	//--Assignment Operator

	bool empty() const { return (numItems == 0); }
	//--Tests if queue is empty. Returns true/false value

	int size() { return numItems; }
	//--Returns size of queue.

	int capacity() { return capacityInt; }
	//--Returns current capacity

	void clear()
	{
		while (!empty())
		{
			pop();
		}
	}
	//--Empties out the queue

	void push(const T & value);
	//--Adds item to the end of the queue

	void pop();
	//--Removes the item at the front of the queue

	T front();
	//--Returns the item at the front of the queue

	T back();
	//--Returns the item at the back of the queue

private:
	int capacityInt,
		numItems,
		myFront,
		myBack;
	T * array;
};

/*******************************************
* COPY CONSTRUCTOR
******************************************/
template<class T>
inline Queue<T>::Queue(const Queue<T> & rhs)
{
	assert(rhs.capacityInt >= 0);

	// do nothing if there is nothing to do
	if (rhs.capacityInt == 0)
	{
		capacityInt = numItems = 0;
		array = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		array = new T[rhs.capacityInt];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capacityInt);
	capacityInt = rhs.capacityInt;
	numItems = rhs.numItems;
	myFront = rhs.myFront;
	myBack = rhs.myBack;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		array[i] = rhs.array[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < capacityInt; i++)
		array[i] = T();
}


/*******************************************
* ASSIGNMENT OPERATOR
******************************************/
template<class T>
inline Queue<T> & Queue<T>::operator=(const Queue<T> & rhs)
{
	if (this == &rhs)
		return *this;
	delete[] array;
	try
	{
		array = new T[rhs.capacityInt];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	capacityInt = rhs.capacityInt;
	numItems = rhs.numItems;
	myFront = rhs.myFront;
	myBack = rhs.myBack;

	for (int i = myFront; i < myBack; i++)
		array[i] = rhs.array[i];
	for (int i = numItems; i < capacityInt; i++)
		array[i] = T();

	return *this;
}


/*******************************************
* PUSH
* Adds item to the end of the queue
******************************************/
template<class T>
inline void Queue<T>::push(const T & item)
{

	if (numItems >= capacityInt)
	{
		if (capacityInt == 0)
		{
			capacityInt = 2;
		}
		else
		{
			capacityInt *= 2;
		}
	}

	int newBack = (myBack + 1);
	
	if (newBack != myFront)
	{
		array[myBack] = item;
		myBack = newBack;
		numItems++;
	}
}

/*******************************************
* POP
* Removes the item at the front of the queue
******************************************/
template<class T>
inline void Queue<T>::pop()
{
	int newFront = (myFront + 1);

	if (!empty())
	{
		myFront = newFront;
		numItems--;
	}
	else
	{
		cerr << "ERROR: attempting to pop from an empty queue";
		exit(1);
	}
}


/*******************************************
* FRONT
* Returns the item at the front of the queue
******************************************/
template<class T>
inline T Queue<T>::front()
{
	if (!empty())
	{
		return array[myFront];
	}
	else
	{
		cerr << "ERROR: attempting to access an item in an empty queue";
		exit(1);
	}
}


/*******************************************
* BACK
* Returns the item at the back of the queue
******************************************/
template<class T>
inline T Queue<T>::back()
{
	if (!empty())
	{
		return array[myBack - 1];
	}
	else
	{
		cerr << "ERROR: attempting to access an item in an empty queue";
		exit(1);
	}
}

#endif // !QUEUE_H
