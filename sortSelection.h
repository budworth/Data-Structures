/***********************************************************************
 * Header:
 *    Sort Selection
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
	for (int i = 0; i < num; i++)
	{
		int pos = i;
		T temp = array[i];

		for (int j = i + 1; j < num; j++)
		{
			if (temp > array[j])
			{
				pos = j;
				temp = array[pos];
			}
		}

		array[pos] = array[i];
		array[i] = temp;
	}
}


#endif // SORT_SELECTION_H
