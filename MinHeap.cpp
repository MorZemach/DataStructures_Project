#include "MinHeap.h"

MinHeap::MinHeap(int i_Size) : m_MaxHeapSize(i_Size)
{
	m_Heap = new Node[i_Size];
	m_HeapSize = 0;
	m_Allocated = 1;
}

MinHeap::MinHeap(const MinHeap& i_Other) : m_MaxHeapSize(i_Other.m_MaxHeapSize)
{
	m_Heap = new Node[m_MaxHeapSize];
	m_HeapSize = i_Other.m_HeapSize;
	m_Allocated = 1;

	for (int i = 0; i < m_MaxHeapSize; i++)
	{
		m_Heap[i] = i_Other.m_Heap[i];
	}
}

void MinHeap::CopyHeapData(const Node* i_Heap)
{
	for (int i = 0; i < m_HeapSize; i++)
	{
		m_Heap[i] = i_Heap[i];
	}
}

MinHeap::~MinHeap()
{
	if (m_Allocated == 1)
	{
		delete[] m_Heap;
	}
	
	m_Heap = nullptr;
}

bool MinHeap::IncreaseHeapSize()
{
	bool isSuccess = false;

	if (m_HeapSize < m_MaxHeapSize)
	{
		m_HeapSize++;
		isSuccess = true;
	}

	return isSuccess;
}

bool MinHeap::DecreaseHeapSize()
{
	bool isSuccess = false;

	if (m_HeapSize > 0)
	{
		m_HeapSize--;
		isSuccess = true;
	}

	return isSuccess;
}

int MinHeap::Left(int i_Node)
{
	return (2 * i_Node + 1);
}

int MinHeap::Right(int i_Node)
{
	return (2 * i_Node + 2);
}

int MinHeap::Parent(int i_Node)
{
	return (i_Node - 1) / 2;
}

bool MinHeap::Insert(Node i_Item)
{
	bool insertSuccess = false;

	if (IncreaseHeapSize() == true)
	{
		m_Heap[m_HeapSize - 1] = i_Item;
		Heapify(m_HeapSize);		
		insertSuccess = true;
	}

	return insertSuccess;
}

void MinHeap::Heapify(int i_Node)
{
	int parent = Parent(i_Node);

	if (m_Heap[parent].priority > m_Heap[i_Node].priority)
	{
		Swap(m_Heap[parent], m_Heap[i_Node]);
		Heapify(parent);
	}
	else
	{
		return;
	}
}

MinHeap::Node MinHeap::DeleteMin()
{
	MinHeap::Node min;

	if (m_HeapSize < 1) 
	{
		cout << "There is no items at the minimum heap!";
	}

	min = m_Heap[0];

	if (DecreaseHeapSize() == true)
	{
		m_Heap[0] = m_Heap[m_HeapSize];
		FixHeap(0);
	}

	return min;
}

void MinHeap::FixHeap(int i_Node)
{
	int min, left = Left(i_Node), right = Right(i_Node);

	if (left < m_HeapSize && m_Heap[left].priority < m_Heap[i_Node].priority)
	{
		min = left;
	}
	else
	{
		min = i_Node;
	}

	if (right < m_HeapSize && m_Heap[right].priority < m_Heap[min].priority)
	{
		min = right;
	}

	if (min != i_Node)
	{
		Swap(m_Heap[i_Node], m_Heap[min]);
		FixHeap(min);
	}
	else
	{
		return;
	}
}

MinHeap::Node MinHeap::Min()
{
	return m_Heap[0];
}

bool MinHeap::MinHeapIsFull()
{
	bool isFull = false;

	if (m_MaxHeapSize == m_HeapSize)
	{
		isFull = true;
	}

	return isFull;
}

