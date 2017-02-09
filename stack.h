/***********************************************************************
 * Header:
 *    stack.h
 * Summary:
 *    This is the stack class, a stack is like a drawer of cloths. The first
 *    one in is the last one out.  Which works like the LIFO of stocks.
 *
 * Author
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

// forward declaration for ContainerIterator
template <class T>
class StackIterator;

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
    // default constructor : empty and kinda useless
    Stack() : numItems(0), cap(0), data(0x00000000) {}
        
    // copy constructor : copy it
    Stack(const Stack & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Stack(int cap) throw (const char *);
    
    // destructor : free everything
    ~Stack()        { if (cap) delete [] data; }
        
    // is the container currently empty
    bool empty() const  { return numItems == 0;         }
    
    // remove all the items from the container
    void clear()        { numItems = 0;                 }
    
    // how many items are currently in the container?
    int size() const    { return numItems;              }
    
    // This is going to increment the number of elements in a stack.
    int getNumItems()   { return numItems;              }
    
    // Get the capacity of the stack
    int capacity(){return cap;          }
    
    // This will push the stack back
    void push(const T & t) throw (const char *);
    
    // This will pop the next one.
    void pop() throw (const char *);
    
    // This will be the last item on the array
    T & top() throw (const char *);
	const T & const_top() const {
		if (numItems == 0)
		{
			throw "ERROR: Unable to reference the element from an empty Stack";
		}

		return data[numItems - 1];
	}
    
    // This is going to be returned from the RHS
    Stack & operator = (Stack & rhs)
    {
        
        cap = rhs.capacity();
        numItems = rhs.size();
        // perhaps a memory leak can occur here?
        data = new T[rhs.capacity()];
        
        for (int i = 0; i < rhs.size(); i++)
        {
            data[i] = rhs.data[i];
        }
        return *this;
    }
    
    // return an iterator to the beginning of the list
    StackIterator <T> begin() { return StackIterator<T>(data); }
    
    // return an iterator to the end of the list
    StackIterator <T> end() { return StackIterator<T>(data + numItems);}
    
private:
    T * data;          // dynamically allocated array of T
    int numItems;      // how many items are currently in the Container?
    int cap;      // how many items can I put on the Container before full?
};

/**************************************************
 * CONTAINER ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class StackIterator
{
public:
    // default constructor
    StackIterator() : p(NULL) {}
    
    // initialize to direct p to some item
    StackIterator(T * p) : p(p) {}
    
    // copy constructor
    StackIterator(const StackIterator & rhs) { *this = rhs; }
    
    // assignment operator
    StackIterator & operator = (const StackIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // not equals operator
    bool operator != (const StackIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // Equals Operator to return a bool on lhs
    bool operator == (const StackIterator & lhs) const
    {
        return lhs.p == this->p;
    }
    
    // dereference operator
    T & operator * ()
    {
        return *p;
    }
    
    // prefix increment
    StackIterator <T> & operator ++ ()
    {
        p++;
        return *this;
    }
    
    // postfix increment
    StackIterator <T> operator++(int postfix)
    {
        StackIterator tmp(*this);
        p++;
        return tmp;
    }
    
private:
    T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = numItems = 0;
        data = NULL;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    
    // copy over the capacity and size
    cap = rhs.cap;
    numItems = rhs.numItems;
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numItems; i++)
       data[i] = rhs.data[i];
    
    // the rest needs to be filled with the default value for T
    for (int i = numItems; i < cap; i++)
       data[i] = T();
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int cap) throw (const char *)
{
    
    // do nothing if there is nothing to do
    if (cap == 0)
    {
        this->cap = this->numItems = 0;
        this->data = NULL;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[cap];
    }
    catch (std::bad_alloc)
    {
       throw "ERROR: Unable to allocate buffer";
    }
    
    
    // copy over the stuff
    this->cap = cap;
    this->numItems = 0;
    
    // initialize the container by calling the default constructor
    for (int i = 0; i < cap; i++)
       data[i] = T();
}

/***************************************************
 * CONTAINER :: PUSH_BACK
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Stack <T> :: push(const T & t) throw (const char *)
{
    try
    {
        // check if cap is 0
        if (cap == 0) // empty()
        {
            cap = 1;
            // need to assign a new location in memory
            // if it was empty to start with
            T * tmp = new T[cap];
            this->data = tmp;
        }
        else if (cap == numItems)
        {
            // double the capacity
            cap *= 2;
            T * tmp = new T[cap];
            
            int i = 0;
            for(StackIterator<T> it = this->begin(); it != this->end(); ++it)
            {
                tmp[i++] = *it;
            }
            
            // passing the pointer from tmp to data
            this->data = tmp;
        }
        
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Stack\n";
    }
    
    //add an item to the end
    this->data[numItems++] = t;
}


/***************************************************
 * CONTAINER :: Pop
 * Returns the top item of the Stack and removes it from
 * the list.
 **************************************************/
template <class T>
void Stack <T> :: pop()throw (const char *)
{
    if(numItems == 0)
    {
        throw "ERROR: Unable to pop from an empty Stack";
    }
    else
    {
        numItems--;
    }
    
}

/***************************************************
 * CONTAINER :: Top
 * This method will return the top value of the Stack
 **************************************************/
template <class T>
T & Stack <T> :: top() throw (const char *)
{
    if(numItems == 0)
    {
        throw "ERROR: Unable to reference the element from an empty Stack";
    }
    
    return data[numItems - 1];
    
}

#endif // Stack_H
