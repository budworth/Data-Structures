/***********************************************************************
 * Header:
 *    Insertion Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{

	int middle;

	for (int i = 1; i < num; i++)
	{
		int first = 0;
		int last = i;

		while (first < last)
		{
			middle = (first + last) / 2;

			if (array[i] > array[middle])
				first = middle + 1;
			else
				last = middle;
		}

		T temp = array[i];

		if (first != i)
		{
			for (int j = 0; j <= i - first - 1; j++)
			{
				array[i - j] = array[i - j - 1];
			}

			array[first] = temp;
		}
	}

	
}


#endif // SORT_INSERTION_H
