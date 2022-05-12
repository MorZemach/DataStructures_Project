#pragma once
#include "CollectHeaders.h"

class Array;

class MinHeap
{
private:

	typedef struct Node
	{
		long int priority;
		int arrayPart;
		int currentArrayIndex = 1;

		Node(long int i_Priority = 0, int i_ArrayPart = -1, int i_ArrayPartSize = -1) 
		{
			priority = i_Priority;
			arrayPart = i_ArrayPart; 
			currentArrayIndex = i_ArrayPartSize * arrayPart + 1;
		}
		void SetCurrentArrayIndex() { currentArrayIndex++; }

	}Node;

private:

	Node* m_Heap;
	const int m_MaxHeapSize;
	int m_HeapSize;
	int m_Allocated;

public:

	friend class Array;
	MinHeap(int i_HeapSize);
	MinHeap(const MinHeap& i_Other);
	~MinHeap();

	static int Left(int i_Node);
	static int Right(int i_Node);
	static int Parent(int i_Node);

	Node* GetHeap() const { return m_Heap; }
	int GetHeapSize() const { return m_HeapSize; }
	int GetMaxHeapSize() const { return m_MaxHeapSize; }
	bool IncreaseHeapSize();
	bool DecreaseHeapSize();

	void CopyHeapData(const Node* i_Heap);
	bool Insert(Node i_Item);
	void FixHeap(int i_Node);
	Node Min();
	Node DeleteMin();
	void Heapify(int i_Node);
	bool MinHeapIsFull();
};

