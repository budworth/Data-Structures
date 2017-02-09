/***********************************************************************
 * Header:
 *    Quick Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H
 /*****************************************************
 * Sort
 * Sorts the array
 ****************************************************/
template <class T>
void sort(T array[], int first, int last)
{
	//--Variables
	int left = first;
	int right = last;

	//--Pivot is set to middle 
	int pivot = (first + last) / 2;

	//--Oranizes everything into the right or left of pivot.
	while (left <= right)
	{
		//--If number is in correct spot, move on
		while (array[pivot] > array[left])
			left++;
		while (array[right] > array[pivot])
			right--;

		if (left <= right)
		{
			//--Switches left and right
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;

			//--Changes pivot
			if (pivot == left)
				pivot = right;
			else if (pivot == right)
				pivot = left;

			//--Increments to get out of loop
			left++;
			right--;
		}
	}

	//--Recursion. Keeps sending the array until organized
	if (first < right)
		sort(array, first, right);
	if (left < last)
		sort(array, left, last);
}

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
	sort(array, 0, num - 1);
}




#endif // SORT_QUICK_H
