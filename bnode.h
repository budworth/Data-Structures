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
#include "node.h"
using namespace std;

#ifndef BNODE_H
#define BNODE_H

/************************************************
 * Linked List Assignment, This is a singly linked list
 * this will only point to the next node and never go back.
 ***********************************************/
template <class T>
class BinaryNode
{
  public:
   // Default Constructor.
	  BinaryNode() : pRight(NULL), pLeft(NULL), pParent(NULL){};
   
   // Non Default Constructor.
	  BinaryNode(T data) : data(data), pRight(NULL), pLeft(NULL), pParent(NULL){};

   // A size function?
   int size() { return count(this);}

   int count(BinaryNode <T> *newNode);
   
   // Add a node to the left of the current Node
   BinaryNode <T> addLeft(T data) throw (const char *);

   // Adds a node to the left of the current node
   BinaryNode <T> addLeft(BinaryNode <T> *newNode) throw (const char *);
   
   // Add a node to the right of the current Node
   BinaryNode <T> addRight(T data) throw (const char *);

   // Adds a node to the left of the current node    
   BinaryNode <T> addRight(BinaryNode <T> *newNode) throw (const char *);
    
   T data;
   BinaryNode <T> * pRight; // less then the parent
   BinaryNode <T> * pLeft;  // more then the parent
   BinaryNode <T> * pParent; // the Ancestor Node
};

template<class T>
inline int BinaryNode<T>::count(BinaryNode<T>* newNode)
{
	if (newNode == NULL)
		return 0;  // The tree is empty.  It contains no nodes.
	else {
		int count = 1;   // Start by counting the root.
		count += newNode->count(newNode->pLeft);  // Add the number of nodes
										  //     in the left subtree.
		count += newNode->count(newNode->pRight); // Add the number of nodes
										  //    in the right subtree.
		return count;  // Return the total.
	}
}

/**********************************************************************
 * addLeft(T data)
 * This is the template variable data type add Left. A new node will be
 * allocated pParent will point to the current node.  The return will be
 * this. It will throw an error if unable to allocate.
 *********************************************************************/
template <class T>
BinaryNode <T> BinaryNode <T> :: addLeft(T data) throw (const char *)
{
	BinaryNode * newNode = new BinaryNode<T>;

   try
   {
	   newNode->data = data;
	   newNode->pParent = this;
	   this->pLeft = newNode;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/**********************************************************************
 * addLeft(Binary Node)
 * This will add a node to the left of the current node. This will take
 * a binary node in the parameters. the past node will point to the new
 * node. pParent will point to the current node. The return value is this.
 * In case of allocation error it will return an error message.
 *********************************************************************/
template <class T>
BinaryNode <T> BinaryNode <T> :: addLeft(BinaryNode <T> * leftNode) throw (const char *)
{
   try
   {

	   this->pLeft = leftNode;
	   if (leftNode != NULL)
	   {
		   /*leftNode->pLeft = NULL;
		   leftNode->pRight = NULL;*/
		   leftNode->pParent = this;
	   }     
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/**********************************************************************
 * addRight(T data)
 * This is the template variable data type add Right. A new node will be
 * allocated pParent will point to the current node.  The return will be
 * this. It will throw an error if unable to allocate.
 *********************************************************************/
template <class T>
BinaryNode <T> BinaryNode <T> :: addRight(T data) throw (const char *)
{
	BinaryNode * newNode = new BinaryNode<T>;

	try
	{
		newNode->data = data;
		newNode->pParent = this;
		this->pRight = newNode;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
	return *this;
}

/**********************************************************************
 * addRight(Binary Node)
 * This will add a node to the right of the current node. This will take
 * a binary node in the parameters. the past node will point to the new
 * node. pParent will point to the current node. The return value is this.
 * In case of allocation error it will return an error message.
 *********************************************************************/
template <class T>
BinaryNode <T> BinaryNode <T> :: addRight(BinaryNode <T> * rightNode) throw (const char *)
{

   try
   {

	   this->pRight = rightNode;
	   if (rightNode != NULL)
	   {
		   /*rightNode->pLeft = NULL;
		   rightNode->pRight = NULL;*/
		   rightNode->pParent = this;    
	   }  
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   
   return *this;
}
/**********************************************************************
 * DeleteBinaryTree()
 * this will go through all of the elements of the tree and delete its
 * content using LRV.  (Left, Right, and Vertex)
 *********************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> *newNode)
{
	if (newNode == NULL)
	{
		return;
	}

	if (newNode->pLeft != NULL)
	{
		deleteBinaryTree(newNode->pLeft);
	}

	if (newNode->pRight != NULL)
	{
		deleteBinaryTree(newNode->pRight);
	}
	delete newNode;
}

/**********************************************************************
 * Insertion Operator()
 * this will put a space between the data as it traverses though the
 * tree using an Infix order. LVR (Left, Vertex, and Right)
 *********************************************************************/
template <class T>
std :: ostream& operator <<(std:: ostream & out, const BinaryNode <T> * node)
{
   if(node->pLeft != NULL)
      out << node->pLeft;

   out << node->data << " ";

   if(node->pRight != NULL)
      out << node->pRight;
   
   return out;
}

#endif // BNODE_H
