#include "Array.h"
#include <climits>

Array::Array(int i_Size)
{
	m_Array = new long int[i_Size];
	m_LogicSize = 0;
	m_PhysicalSize = i_Size;
	m_Start = 0;
	m_End = -1;
	m_MaximumValue = LONG_MIN;
	
}

Array::~Array()
{
	delete[] m_Array;
}

bool Array::SetLogicSize(int i_LogicSize)
{
	bool isSuccess = false;

	if (i_LogicSize > 0 && i_LogicSize < m_PhysicalSize)
	{
		m_LogicSize = i_LogicSize;
		isSuccess = true;
	}
	else
	{
		if (SetPhysicalSize(m_PhysicalSize * 2) == true)
		{
			isSuccess = true;
		}
	}

	return isSuccess;
}

bool Array::SetPhysicalSize(int i_PhysicalSize)
{
	bool isSuccess = false;
	long int* temp = m_Array;

	if (i_PhysicalSize > m_PhysicalSize)
	{
		m_Array = new long int[i_PhysicalSize];
		
		for (int i = 0; i < m_PhysicalSize; i++)
		{
			m_Array[i] = temp[i];
		}

		m_PhysicalSize = i_PhysicalSize;
	}

	delete[] temp;
	return isSuccess;
}

bool Array::SetStart(int i_Start)
{
	bool isSuccess = false;

	if (i_Start >= 0 && i_Start < m_PhysicalSize)
	{
		m_Start = i_Start;
		isSuccess = true;
	}

	return isSuccess;
}

bool Array::SetEnd(int i_End)
{
	bool isSuccess = false;

	if (i_End >= 0 && i_End < m_PhysicalSize)
	{
		m_End = i_End;
		isSuccess = true;
	}

	return isSuccess;
}

void Array::AddToArray(int i_Data)
{
	if (m_LogicSize >= m_PhysicalSize)
	{
		SetPhysicalSize(m_PhysicalSize * 2);
	}

	m_Array[m_LogicSize] = i_Data;
	m_LogicSize++;
	m_End++;

	if (i_Data > m_MaximumValue)
	{
		m_MaximumValue = i_Data;
	}
}

void Array::K_WayMergeAlgorithm(int k)
{
	if (k >= m_LogicSize)
	{
		QuickSort();
	}
	else
	{
		MinHeap minHeap(k);
		Helper_K_WayMergeAlgorithm(k, 0, minHeap);
	}
}

// צריך לזכור לטפל במקרים שהאן לא מתחלק בקיי.
// ceil מעגלת כלפיי מעלה.
// int בחלוקה יעדכן כרגיל כלפיי מטה.
void Array::Helper_K_WayMergeAlgorithm(int k, int i_ArrayPart, MinHeap& i_MinHeap)
{
	if (k >= m_LogicSize)
	{
		QuickSort();
		MinHeap::Node node(m_Array[0], i_ArrayPart, (m_PhysicalSize / k));
		i_MinHeap.Insert(node);

		/*if (i_MinHeap.MinHeapIsFull() == true)
		{
			Merge(i_MinHeap);
		}*/

		//return;    **** We dont need to return here! We should merge all the arrays.
		///////////////// If there is only one REC call we are never merge the arrays if there is return here.
	}
	else
	{
		if (SetLogicSize(m_LogicSize / k) == true)
		{
			int subArrayCount = 0;

			for (int i = 0; i < m_PhysicalSize; i += m_LogicSize)
			{
				if (SetStart(i) == true && SetEnd(i + m_LogicSize - 1) == true)
				{
					Helper_K_WayMergeAlgorithm(k, subArrayCount, i_MinHeap);
					subArrayCount++;
				}
			}

			/*if (SetStart(0) == true)
			{
				Array arrayMerge(m_PhysicalSize);
				Merge(i_MinHeap, arrayMerge);
			}*/
		}
	}

	if (SetStart(0) == true)          // We are done the if-else. all the arrays are sorted and the heap is full of items.
		                              // Now we should merege it all anyway. So it will be after the if-else.
	{
		Array arrayMerge(m_PhysicalSize);
		Merge(i_MinHeap, arrayMerge);
	}
}

void Array::Merge(MinHeap& i_MinHeap, Array& i_ArrayMerge)
{
	MinHeap::Node currentMin;

	for (int i = 0; i < m_PhysicalSize; i++)
	{
		currentMin = i_MinHeap.DeleteMin();

		if ((currentMin.arrayPart + 1) * m_LogicSize > currentMin.currentArrayIndex) ////*********** check if m_LogicSize == (n/k);
		{
			i_ArrayMerge.m_Array[i] = currentMin.priority;
			MinHeap::Node newNode(m_Array[currentMin.currentArrayIndex],
				currentMin.arrayPart, currentMin.currentArrayIndex + 1);
			i_MinHeap.Insert(newNode);
		}
		else
		{
			MinHeap::Node maxNode(m_MaximumValue + 1);
			i_MinHeap.Insert(maxNode);
		}
	}
}

void Array::QuickSort()
{
	int pivot;

	if (m_Start < m_End)
	{
		pivot = Partition();

		if (SetEnd(pivot - 1) == true)
		{
			QuickSort();
		}

		if (SetStart(pivot + 1) == true)
		{
			QuickSort();
		}
	}
	else
	{
		return;
	}
}

// In each iteration, index moves one step towards pivot depending on the side pivot is located.
// In each iteration the distance between the index to pivot is reduced by 1.
// In the end, pivot will be in his position in the array (by his size) and in his left part will be numbers that arr smaller than his,
// and in his right part, will be numbers bigger than his.
int Array::Partition()
{
	int pivot = m_Start;
	int index = m_End;

	while (pivot != index)
	{
		if (pivot < index)
		{
			if (m_Array[pivot] > m_Array[index])
			{
				Swap(m_Array[pivot], m_Array[index]);
				Swap(pivot, index);
				index++;
			}
			else
			{
				index--;
			}
		}
		else
		{
			if (m_Array[pivot] < m_Array[index])
			{
				Swap(m_Array[pivot], m_Array[index]);
				Swap(pivot, index);
				index--;
			}
			else
			{
				index++;
			}
		}
	}

	return pivot; // pivot and index in the same position in the array, so we can return pivot.
}


