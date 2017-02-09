/***********************************************************************
 * Header:
 *    Deque Class
 * Summary:
 *    This class contains the notion of a Deque:
 *    a deque allows the user to add elements to the
 *    front of the line or the back of the line.
 *    this allows for priorities, and allows popping
 *    or removing from both the front and back as well.
 *
 *    This will contain the class definition of:
 *        Deque          : A class that holds stuff
 * Author
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 *    Following the Container code that was initial coding by Br. Helfrich
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <string>
#include <iostream>
#include <deque>

/************************************************
 * Deque
 * A class that holds stuff   
 ***********************************************/
template <class T>
class Deque
{
    
public:
    // default constructor
    Deque() : myFront(0), myBack(0), cap(0), numItems(0), data(0x00000000) {}
    
    // non-default constructor
    Deque(int nCap) throw (const std::string);
    
    // copy constructor
    Deque(const Deque & rhs) throw (const std::string);
    
    // destructor
    ~Deque()            { if (cap) 	delete[] data; 	}
    
    // is the Queue currently empty
    bool empty()		{
        
		return (this->numItems == 0);
    }
    
    // remove all the items from the Queue
    void clear()			{
       myFront = 0;
       myBack = 0;
       cap = 0;
       numItems = 0;
    }
    
    // how many items are currently in the Queue?
    int size() const    { return numItems; }
    
    // push function to put a new item on at the front
    void push_front(const T & rhs) throw (const std::string);

    // push function to put a new item on at the back
    void push_back(const T & rhs) throw (const std::string);
    
    // pop fuction to remove the front item on the Queue
    void pop_front() throw (const char *);

    // pop fuction to remove the front item on the Queue
    void pop_back() throw (const char *);
    
    // top function returns the item at the front of the Queue
    T & front() throw (const char *);
    
    // back function to return the back item
    T & back() throw (const char *);
    
    // capacity function will return the capacity of the storage
    int capacity() 		{ return cap; }
    
    // overload: operator = (Assignment operator to copy a Queue)
    Deque<T> & operator = (const Deque<T> & rhs) throw (const std::string)
    {
        try
        {
            T * tmp = new T[rhs.cap];
            for (int i = 0; i < rhs.cap; i++)
            {
                tmp[i] = rhs.data[i];
            }
            // Get REAL copy by setting lhs to temp and not a COPY of
            // rhs's location
            delete[] data;
            data = tmp;
            cap = rhs.cap;
            myFront = rhs.myFront;
            myBack = rhs.myBack;
            numItems = rhs.numItems;
        }
        catch (std::string e)
        {
            throw "ERROR: Unable to allocate a new buffer for Queue";
        }
        return *this; //Error here.
    }   
    
  private:
    T * data; 	 // Queue data
    int myFront; // next item to pull off the queue
    int myBack;	 // next location for the next queued item
    int cap;	 // array capacity
    int numItems;// keep track of the number of items
    
};

/*****************************************************************
 * Code for the prototypes
 ******************************************************************/
/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Queue to "cap"
 **********************************************/
template <class T>
Deque<T> ::Deque(int qCap) throw (const std::string)
{
    assert(qCap >= 0);
    // do nothing if there is nothing to do
    if (qCap == 0)
    {
        cap = 0;
        myFront = 0;
        myBack  = 0;
        numItems = 0;
        data = NULL;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[qCap];
    }
    catch (std::string)
    {
        throw "ERROR: Unable to allocate a new buffer for Queue";
    }
    
    // initialize the Queue
    for (int i = 0; i < qCap; i++)
    {
        data[i] = T();
    }
    // copy over the stuff
    cap = qCap;
    myFront = 0;
    myBack  = 0;
    numItems = 0;
} // end non-default constructor

/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> ::Deque(const Deque <T> & rhs) throw (const std::string)
{
    // if equal 0, there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        myFront = 0;
        myBack  = 0;
        numItems = 0;
        data = NULL;
        return;
    }
    
    // now we have something to do if we are at this pointer
    try
    {
        data = new T[rhs.cap];
        
    }
    catch (std::string e)
    {
        throw "ERROR: Unable to allolcate a new buffer for Queue";
    }
    
    cap = rhs.cap;
    myFront = rhs.myFront;
    myBack  = rhs.myBack;
    numItems = rhs.numItems;
    
   
    for (int i = 0; i < cap; i++)
         data[i] = rhs.data[i];
           
} // end copy constructor

/***************************************************
 * CONTAINER :: Push_front
 * Adds an item to the queue takes a single parameter (the item to be added the
 * front of the queue)
 **************************************************/
template <class T>
void Deque<T> ::push_front(const T & rhs) throw (const std::string)
{
	   if (cap == 0)
	   {
		   // set capacity to one but then create a vector with one element
		   cap = 1;
		   T * tmp = new T[cap];
		   delete[] data;
		   data = tmp;
		   cap = 1;
		   myFront = 0;
		   myBack = 0;
		   numItems = 0;
	   }

	   else if ((cap == numItems))// && (cap == myBack) && (myFront == 0))
	   {
		   try
		   {
			   // if cap = numItems increase size & create temporary, copy data
			   // to tmp, then reassign new local to data
			   cap *= 2;
			   T * tmp = new T[cap];

			   for (int i = 0; i < numItems; i++)
			   {
				   tmp[i] = data[i];
			   }

			   delete[] data;
			   data = tmp;
		   }
		   catch (std::string e)
		   {
			   throw "ERROR: unable to allocate a new buffer for Queue";
			   return;
		   }
	   } // end else if
	   else if ((cap == numItems) && (myFront > 0) && (myBack <= myFront))
	   {
		   try
		   {
			   int tmpCap = cap;
			   cap *= 2;
			   T * tmp = new T[cap];

			   for (int i = 0; i < myBack; i++)
				   tmp[i] = data[i];

			   for (int i = myFront; i < numItems; i++)
				   tmp[i + tmpCap] = data[i];

			   delete[] data;
			   data = tmp;
			   myFront += tmpCap;
		   }
		   catch (std::string e)
		   {
			   throw "ERROR: unable to allocate a new buffer for Queue";
			   return;
		   }
	   } // end else if

	   int newFront = myFront - 1;

	   if (newFront < 0)
	   {
		   newFront = cap -1;
	   }

	   data[newFront] = rhs;
	   myFront = newFront;
	   ++numItems;
         
   // numItems++;
}
/***************************************************
 * CONTAINER :: Push_back
 * Adds an item to the queue takes a single parameter (the item to be added the
 * end of the queue)
 **************************************************/
template <class T>
void Deque<T> ::push_back(const T & rhs) throw (const std::string)
{
    if (cap == 0)
    {
        // set capacity to one but then create a vector with one element
        cap = 1;
        T * tmp = new T[cap];
        delete[] data;
        data = tmp;
        cap = 1;
        myFront = 0;
        myBack = 0;
        numItems = 0;
    }
    
    else if ((cap == numItems))// && (cap == myBack) && (myFront == 0))
    {
        try
        {
            // if cap = numItems increase size & create temporary, copy data
            // to tmp, then reassign new local to data
            cap *= 2;
            T * tmp = new T[cap];
            
            for (int i = 0; i < numItems; i++)
            {
                tmp[i] = data[i];
            }
            
            delete[] data;
            data = tmp;
        }
        catch (std::string e)
        {
            throw "ERROR: unable to allocate a new buffer for Queue";
            return;
        }
    } // end else if
    else if ((cap == numItems) && (myFront > 0) && (myBack <= myFront))
    {
        try
        {
            int tmpCap = cap;
            cap *= 2;
            T * tmp = new T[cap];
            
            for (int i = 0; i < myBack; i++)
                tmp[i] = data[i];
                
                for (int i = myFront; i < numItems; i++)
                    tmp[i + tmpCap] = data[i];
                    
                delete[] data;
                data = tmp;
                myFront += tmpCap;
        }
        catch (std::string e)
        {
            throw "ERROR: unable to allocate a new buffer for Queue";
            return;
        }
    } // end else if

	int newBack = myBack + 1;

	if (newBack == cap)
	{
		newBack = 0;
	}

	data[newBack] = rhs;
	myBack = newBack;
	++numItems;
}

/***************************************************
 * CONTAINER :: Pop_front
 * Removes an item from the head of the queue.
 * reduce the size by one.
 **************************************************/
template <class T>
void Deque<T> ::pop_front()throw (const char *)
{
	if (!empty())
	{
		int newFront = myFront + 1;

		if (newFront == cap)
		{
			newFront = 0;
		}
		
		myFront = newFront;
		--numItems;
	}

}


/***************************************************
 * CONTAINER :: Pop_back
 * Removes an item from the back of the deque.
 * reduce the size by one.
 **************************************************/
template <class T>
void Deque<T> ::pop_back()throw (const char *)
{
	int newBack = myBack - 1;

	if (newBack < 0)
	{
		newBack = cap - 1;
	}

	myBack = newBack;
	numItems--;
}

/***************************************************
 * CONTAINER :: Front()
 * Returns the item currently at the front of the queue.
 * returned by reference so last item can be changed through
 * the front() method
 **************************************************/
template <class T>
T & Deque<T> ::front() throw (const char *)
{
    if (!empty())
    {
        if (myFront == cap)
            myFront = 0;
        return data[myFront];
    }

}  // end front

/***************************************************
 * CONTAINER :: back()
 * Returns the item currently at the back of the queue.
 *
 **************************************************/
template <class T>
T & Deque <T> :: back() throw (const char *)
{
	int newBack = myBack - 1;
	if (newBack < 0)
	{
		newBack = cap - 1;
	}

    if (!empty())
    {
        return data[newBack];
    }
   
}  // end back

#endif // QUEUE_H
