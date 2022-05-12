#pragma once
#include "CollectHeaders.h"

class MinHeap;

template <class T>
void Swap(T& a, T& b) // get two T type parameters and swap them. 
{
	T temp = a;
	a = b;
	b = temp;
}


class Array
{
private:
	long int* m_Array;
	int m_Start;
	int m_End;
	int m_LogicSize;
	int m_PhysicalSize;
	int m_MaximumValue;

public:
	Array(int i_Size);
	~Array();

	long int* GetArray() const { return m_Array; }
	int GetStart() const { return m_Start; }
	int GetEnd() const { return m_End; }
	int GetLogicSize() const { return m_LogicSize; }
	int GetPhysicalSize() const { return m_PhysicalSize; }
	bool SetPhysicalSize(int i_PhysicalSize);
	bool SetLogicSize(int i_LogicSize);
	bool SetStart(int i_Start);
	bool SetEnd(int i_End);
	void AddToArray(int i_Data);
	void K_WayMergeAlgorithm(int k);
	void Helper_K_WayMergeAlgorithm(int k, int i_ArrayPart, MinHeap& i_MinHeap);
	void QuickSort();
	int Partition();
	void Merge(MinHeap& i_MinHeap, Array& i_ArrayMerge);
};


