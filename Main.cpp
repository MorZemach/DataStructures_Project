#include "To_Sort_Array_H.h"

int main()
{
	int n, requested_Index;
	n = requested_Index = INITIAL_VALUE; 

	ToSortArray* arr = ToSortArray::legalInputCheck(n, requested_Index);

	if (arr == nullptr)
	{
		cout << "wrong input" << endl;
	}
	else
	{
		ToSortArray copyForInsertionSort = *arr;
		ToSortArray copyForSelection = *arr;
		ToSortArray copyForFiveSort = *arr;

		ofstream myfile("Measure.txt"); // The name of the file.
		copyForInsertionSort.CalculateRunTimeInsertionSort(myfile, requested_Index);
		copyForSelection.CalculateRunTimeSelectionSort(myfile, requested_Index);
		copyForFiveSort.CalculateRunTimeRecursiveFiveSort(myfile, requested_Index);
		myfile.close();
	}

	delete arr;
	
}