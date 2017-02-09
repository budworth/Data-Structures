/**********************************************************************
* Header:
*    set.h
* Summary:
*    This class is the set class, it will allow the user to input
*    data elements such as a, b, and c. It can get rid of duplicates in a set
*    it can also add or subtract from to sets.
*
*    This will contain the class definition of:
*        set         : A class that holds stuff
*        setIterator : An interator through Set
* Author
*    Bud Wortham, Tyler Stanley, and David Pruitt
************************************************************************/

#ifndef SET_H
#define SET_H

#include <algorithm>

// forward declaration for ContainerIterator
template <class T>
class SetIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
  Set() : numItems(0), cap(0), data(0x00000000) {}
   
   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Set(int cap) throw (const char *);
   
   // destructor : free everything
   ~Set()              { if (cap) delete [] data;                  }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;                     }

   // remove all the items from the container
   void clear()        { numItems = 0; cap = 0; data = 0x00000000; }

   // how many items are currently in the container?
   int size() const    { return numItems;                          }

   // Get the capacity of the vector
   int capacity()      { return cap;                               }
   
   // add an item to the set
   void insert(const T & t) throw (const char *);

   //Erase : removes an element from the set (uses an iterator
   void erase(SetIterator<T> it) throw(const char *);

   //find : tales a template item as parameter and returns an iterator
   //returns set :: end(); if nothing is found.
   SetIterator<T> find(const T & t) throw(const char *);

   // Intersection Operator: returns a new set obj with all the new elements
   Set & operator && (Set & rhs);

   // Union Operator : parameter with a set obj. returns a new set obj with
   // all of the new elements NOTE: parameters may not be right.
   Set & operator || (Set & rhs);
   
   // This is going to be returned from the RHS
   // Assignment Operator
   Set & operator = (Set & rhs);

   // Overloaded (): return by value, behaves like bracket operator
   // This works like A = f(x); so I can assign a function to a variable
   T operator()(int index)  { return data[index];                        }
   
   // Will contain the data of index so the user may select within the array
   T & operator[](int index)  { return data[index];                      }

   // Const Method for [], it goes at the end of the function name
   // This is because is not to change the private variables.
   T & operator[](const int index) const { return data[index];           }
  
   // return an iterator to the beginning of the list
   SetIterator <T> begin() { return SetIterator<T>(data);                }

   // return an iterator to the end of the list
   SetIterator <T> end()   { return SetIterator<T>(data + numItems);     }
   
  private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;      // how many items can I put on the Container before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(0x00000000) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}

   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }

   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }
   
   // Equals Operator to return a bool on lhs
   bool operator == (const SetIterator & lhs) const
   {
      return lhs.p == this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   SetIterator <T> & operator -- ()
   {
	   p--;
	   return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

   SetIterator <T> operator--(int postfix)
   {
	   SetIterator tmp(*this);
	   p--;
	   return tmp;
   }

   SetIterator <T> operator + (int rhs)
   {
	   p + rhs;
	   return *this;
   }

   SetIterator <T> operator - (int rhs)
   {
	   p - rhs;
	   return *this;
   }
      
  private:
   T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = 0x00000000;
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
   //assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capacity);
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
Set <T> :: Set(int cap) throw (const char *)
{
      
   // do nothing if there is nothing to do
   if (cap == 0)
   {
      this->cap = this->numItems = 0;
      this->data = 0x00000000;
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
 * INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
	if (cap == 0)
	{
		// set capacity to one but then create a vector with one element
		cap = 1;
		T * tmp = new T[cap];
		delete[] data;
		data = tmp;
		cap = 1;
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

			for (int i = numItems; i < cap; i++)
			{
				tmp[i] = T();
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

	SetIterator<T> iInsert = find(t);
	 

	if (*iInsert != t)
	{
		
		data[numItems] = t;
		sort(data, data + numItems + 1);

		numItems++;
	}

}

/***************************************************
 * ERASE
 * removes an element from the set. This method takes
 * an iterator as a parameter, reffering to the element
 * to be removed from the set. There is not return value.
 **************************************************/
template <class T>
void Set <T> :: erase(SetIterator<T> it) throw(const char *)
{

	for (int i = 0; i < numItems; i++)
	{
		if (data[i] == *it)
		{
			data[i] = data[--numItems];
			sort(data, data + numItems);
			return;
		}
	}
}

/***************************************************
 * FIND
 * Takes a template item as a parameter, and returns
 * an iterator pointing to the corresponding item in
 * the set. If there is no item, it returns SET :: end();
 **************************************************/
template <class T>
SetIterator<T> Set <T> :: find(const T & t) throw(const char *)
{

	SetIterator<T> it;

	for (it = begin(); it != end(); it++)
	{
		if (*it == t)
		{
			return it;
		}
	}

	return end();
}

/***************************************************
 * Intersection Operator &&
 * the parameter is a set object. THe return value is a
 * new set object containing all the elements that are
 * in the both this ---->AND<--- in the parameter.
 **************************************************/
template <class T>
Set <T> & Set<T> :: operator && (Set & rhs)
{
	Set<T> *s3 = new Set;

	for (int i = 0; i < numItems; i++)
	{
		if (*rhs.find(data[i]) != *end())
		{
			s3->insert(data[i]);
		}
	}

	return *s3;
}
/***************************************************
 * Union Operator ||
 * the parameter is a set object, and the return value
 * is a new set object containing all the elements that
 * are in both this ---->OR<---- in the parameter.
 **************************************************/
template <class T>
Set <T> & Set<T> :: operator || (Set & rhs)
{
	Set<T> *s3 = new Set;
	*s3 = *this;

	for (int i = 0; i < rhs.numItems; i++)
	{
		s3->insert(rhs.data[i]);
	}

	return *s3;
  
}
/***************************************************
 * Overloaded Assignment Operator
 * This overloaded assignment operator will allow the
 * vector to assign one vector to another.
 **************************************************/
template <class T>
Set <T> & Set <T> :: operator = (Set & rhs)
{

   cap = rhs.capacity();
   numItems = rhs.size();
   delete [] data;  // To free up memory, can you help me understand this better
   data = new T[rhs.capacity()];
   
   for (int i = 0; i < rhs.size(); i++)
   {
      data[i] = rhs.data[i];
   }
   return *this;
   
}

#endif // Vector_H

