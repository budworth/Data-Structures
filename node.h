/***********************************************************************
 * Header:
 *    Node.h
 * Summary:
 *    This class is going to allow the user to have a linked list
 *    which will store data since link listed are the best type of
 *    abstract data types to insert data into the middle we are
 *    going to use this linked list to make it happen.
 *
 *    This will contain the class definition of:
 *        Node          : A class that holds the elements with pointers.
 * Author
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 ***********************************************************************/
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

#ifndef NODE_H
#define NODE_H

/************************************************
 * Linked List Assignment, This is a singly linked list
 * this will only point to the next node and never go back.
 ***********************************************/
template <class T>
class Node
{
  public:
   // Default Constructor.
  Node() :  /*data(0x00000000),*/ pNext(NULL){};
   
   // Non Default Constructor.
  Node(T data) : data(data), pNext(NULL){};

   // 2nd Non Default Constructor       
  Node(T data, Node <T> * pNext) : data(data), pNext(pNext){};


   ~Node() {};

      
   T data;                  // This allocated array of T?
   Node <T> * pNext;
};

/************************************************
 * Copy() : Copies a linked list.  takes a pointer
 * to a node as a parameter and returns a newly
 * created linked-list containing a copy of all
 * the nodes below the list represented by the
 * parameters.
 ***********************************************/
template <class T>
Node <T> * copy(Node <T> *pHead) throw (const char *)
{
   if (pHead == NULL)
   {
      return NULL;
   }

   Node <T> *tempHead = pHead; // This will increment and go down the list for the head
   Node <T> *first    = new Node <T>; // 
   Node <T> *next     = first;    // this is the next item to be pointed at


   do
   {
      if (tempHead->pNext == NULL)
         next->pNext = NULL;
      else
         next->pNext = new Node <T>;

      next->data = tempHead->data;
      next       = next->pNext;
      tempHead   = tempHead->pNext;
      
   }
   while(tempHead != NULL);
      
   return first;
}

/************************************************
 * Insert(): This will insert a new node into the
 * current list, the first parameter is the value to
 * be placed in the new node, the 2nd is the node prevois
 * to the the new node, and the boolean is to express if we
 * are adding at the begining of a head.
 ***********************************************/
template <class T>
void insert(T data, Node <T> *& preNode, bool insertHead = false) throw (const char *)
{
//   if(preNode == NULL)
//      return;
   Node <T> *pNew = new Node <T>; // A new node to do things.
   pNew->data = data;

   // if insert is empty
   if(preNode == NULL)
   {
      pNew->pNext = NULL;
      preNode = pNew;
   }
   // This is if its at the front
   else if(preNode != NULL && insertHead)
   {
      pNew->pNext = preNode;
      preNode = pNew;
   }
   // If its in the middle somewhere
   else
   {
      pNew->pNext = preNode->pNext;
      preNode->pNext = pNew;
   }
   // if insert into the middle
}

/************************************************
 * Find()
 * Finds the node at the corresponding spot. The First
 * parameter is a ptr to the front of a list.  the second
 * is the item to be found. This should also return the value
 * of a ptr if one is found.
************************************************/
template <class T>
Node <T> * find(Node <T>* ptr, T item) throw (const char *)
{
	for (Node<T> * p = ptr; p; p = p->pNext)
	{
		if (item == p->data)
		{
			return p;
		}
	}
}

/************************************************
 * FreeData(): This is going to release all of the
 * memory contained in a given linked list. 
 ***********************************************/
template <class T>
void freeData(Node <T> *&pHead) throw (const char *)
{
    for(Node <T> *pSave = pHead; pHead; pSave = pHead)
   {
      pHead = pSave->pNext;
      delete pSave;
   }
}

/************************************************
 * Extraction Operator : This is going to overload
 * the extraction operator.  THis will allow me to be
 * able to use the << for delelting a long list.
 ***********************************************/
template <class T>
ostream & operator << (ostream & out, Node <T> * rhs)
{
	for (Node<T> * p = rhs; p; p = p->pNext)
	{
		if(p->pNext == NULL)
		{
			out << p->data;
		}
		else
		{
			out << p->data << ", ";
		}
		
	}
	
	return out;
	
}

#endif // NODE_H
