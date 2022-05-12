#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS
#define SIZE_OF_EACH_ARRAY 5
#define INITIAL_VALUE 0
using namespace std;

class ToSortArray
{
private:
	double* m_Sort_Array; // Array of n diffrent double numbers
	int m_Array_Size; // Array's size
	int m_Start; // Array start index
	int m_End; // Array end index

public:
	//--------------------------------- Constructor & Destructor -----------------------------------//
	ToSortArray(const int size = 1);
	ToSortArray(const ToSortArray& other);
	~ToSortArray();

	//--------------------------------- Getters & Setters -----------------------------------------//
	double* get_Array() const;
	int get_Start() const;
	int get_End() const;
	bool set_Start(int start);
	bool set_End(int end);
	bool set_ArraySize(int size);

	void AddToArray(double input);

	//-------------------------------- Sort Algorithm & Secondary functions -----------------------//
	double InsertionSort(int requested_Index);
	double SelectionSort(int requested_Index);
	double RecursiveFiveSort(int requested_Index);
	int FindPositionElementInArray(double val);
	void BubbleSort();
	int Partition();

	//-------------------------------- Calculate Run Time Functions -------------------------------//
	void CalculateRunTimeInsertionSort(ofstream& file, int requested_Index);
	void CalculateRunTimeSelectionSort(ofstream& file, int requested_Index);
	void CalculateRunTimeRecursiveFiveSort(ofstream& file, int requested_Index);

	//----------------------------- check Input Integrity Functions -------------------------------//
	static ToSortArray* legalInputCheck(int& n, int& requested_Index);
	static bool convert_String_To_Double(string number, double& result);
	static bool isDigitOrPoint(char ch);

	template <class T>
	static void swap(T& a, T& b);
};

template <class T>
void ToSortArray::swap(T& a, T& b) // get two T type parameters and swap them. 
{
	T temp = a;
	a = b;
	b = temp;
}

