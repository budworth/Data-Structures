/***********************************************************************
 * Header:
 *    Binary Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	BST<T> tree;

	for (int i = 0; i < num; ++i)
		tree.insert(array[i]);

	int i = 0;
	for (BSTIterator<T> it = tree.begin(); it != tree.end(); ++it, ++i)
		array[i] = *it;

	return;
}


#endif // SORT_BINARY_H
