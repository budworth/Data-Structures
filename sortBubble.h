/***********************************************************************
 * Header:
 *    Bubble Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 * Used CS124 code
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{

	bool switched = true;

	for (int iSpot = num - 1; iSpot >= 1 && switched; iSpot--)
		for (int iCheck = 0, switched = false; iCheck <= iSpot - 1; iCheck++)
		{

			if (array[iCheck] > array[iCheck + 1])
			{
				T temp = array[iCheck];
				array[iCheck] = array[iCheck + 1];
				array[iCheck + 1] = temp;
				switched = true;
			}
		}

}


#endif // SORT_BUBBLE_H
