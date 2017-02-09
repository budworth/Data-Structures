/***********************************************************************
 * Header:
 *    Merge Sort
 * Author:
 *    Bud Wortham, David Pruitt, and Tyler Stanley
 * Summary:
 *    This program will implement the Merge Sort
 *	  We used the book code and an online source.
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
	//--Arrays to copy and split and merge
	T * mainArray = array;
	T * tempArray = new T[num];

	//--Variable to go through array
	int begin1 = 0;
	int max1 = 0;
	int begin2 = 0;
	int max2 = 0;
	int tempBegin = 0;

	while (true)
	{
		while (begin1 < num)
		{
			//--Gets the first sub-array
			max1 = begin1;
			while (!(mainArray[max1] > mainArray[max1 + 1]) && max1 < num)
				max1++;
			max1++;

			//--Gets the second sub-array
			begin2 = max2 = max1;
			while (!(mainArray[max2] > mainArray[max2 + 1]) && max2 < num)
				max2++;
			max2++;

			//--Exit infinite loop
			if (begin1 == 0 && max1 == num)
			{
				if (tempArray == mainArray)
				{
					T * temp = mainArray;
					mainArray = tempArray;
					tempArray = temp;

					for (int i = 0; i < num; i++)
						mainArray[i] = tempArray[i];
				}

				delete[] tempArray;

				return;
			}

			//--Merge the sub-arrays into temp array
			tempBegin = begin1;

			while (begin1 < max1 && begin2 < max2 && begin1 < num && begin2 < num)
			{
				if (mainArray[begin1] > mainArray[begin2])
				{
					tempArray[tempBegin] = mainArray[begin2];
					begin2++;
				}
				else
				{
					tempArray[tempBegin] = mainArray[begin1];
					begin1++;
				}

				tempBegin++;
			}

			while (begin1 < max1 && begin1 < num)
			{
				tempArray[tempBegin] = mainArray[begin1];
				begin1++;
				tempBegin++;
			}
			while (begin2 < max2 && begin2 < num)
			{
				tempArray[tempBegin] = mainArray[begin2];
				begin2++;
				tempBegin++;
			}

			begin1 = max2;
		}

		T * temp = mainArray;
		mainArray = tempArray;
		tempArray = temp;

		begin1 = 0;
	}
}


#endif // SORT_MERGE_H
