// HeapSort.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "HeapSort.h"
using namespace std;

//template <typename T>
//inline void swap(T &x, T &y)
//{
//	T temp = x;
//	x = y;
//	y = temp;
//}

template <typename T>
void heapify(T *array, int size, int elem)
{
	int lChild = elem * 2 + 1;
	int rChild = lChild + 1;
	while (rChild<size)
	{
		if (array[lChild] >= array[elem] && array[rChild] >= array[elem])
		{
			return;
		}
		if (array[lChild] <= array[rChild])
		{
			swap(array[lChild], array[elem]);
			elem = lChild;
		}
		else
		{
			swap(array[rChild], array[elem]);
			elem = rChild;
		}
		lChild = elem * 2 + 1;
		rChild = lChild + 1;
	}
	if (lChild<size&&array[lChild]<array[elem])
	{
		swap(array[lChild], array[elem]);
	}
}

template <typename T>
static void HeapSort::heapSort(T *array, int size)
{
	if (size>1)
	{
		for (int i = size / 2 - 1; i >= 0; i--)
		{
			heapify(array, size, i);
		}
		swap(array[0], array[size - 1]);
		heapSort(array, --size);
	}
}


