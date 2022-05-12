#include "To_Sort_Array_H.h"

//----------------------------------------------------------------------// 

ToSortArray::ToSortArray(const int size) 
// The constructor gets the size of the array he wants to build, 
// creates one and initializes the index of the beginning, end and size of the array(the data members of the class).
{
	this->m_Sort_Array = new double[size];
	this->m_Start = INITIAL_VALUE;
	this->m_Array_Size = size;
	this->m_End = -1;
}

ToSortArray::ToSortArray(const ToSortArray& other) // Copy constructor 
{
	this->m_Sort_Array = new double[other.m_Array_Size];
	for (int i = 0; i < other.m_Array_Size; i++)
	{
		this->m_Sort_Array[i] = other.m_Sort_Array[i];
	}
	this->m_Start = other.m_Start;
	this->m_End = other.m_End;
	this->m_Array_Size = other.m_Array_Size;
}

ToSortArray::~ToSortArray() // Destructor- Releases the memory allocated to the array.
{
	delete[] m_Sort_Array;
}

//----------------------------------------------------------------------// 

double* ToSortArray::get_Array() const // Return the start address of the array.
{
	return this->m_Sort_Array;
}

int ToSortArray::get_Start() const // Return the start index of the array.
{
	return this->m_Start;
}

int ToSortArray::get_End() const // Return the end index of the array.
{
	return this->m_End;
}

bool ToSortArray::set_Start(int start) // Return true, if the placement operation was successful & start is a positive number or 0.
{
	if (start >= 0)
	{
		this->m_Start = start;
		return true;
	}
	else
		return false;
}

bool ToSortArray::set_End(int end) // Return true, if the placement operation was successful & end is a positive number or 0.
{
	if (end >= 0)
	{
		this->m_End = end;
		return true;
	}
	else
		return false;
}

bool ToSortArray::set_ArraySize(int size) // Return true, if the placement operation was successful & size is a positive number.	
{
	if (size > 0)
	{
		this->m_Array_Size = size;
		return true;
	}
	else
		return false; 
}

//----------------------------------------------------------------------// 

void ToSortArray::AddToArray(double input) // Get an input from user and add the element to the end of the array.
{
	(this->m_Sort_Array)[this->m_End + 1] = input;
	this->m_End++;
}

//----------------------------------------------------------------------// 

bool ToSortArray::isDigitOrPoint(char ch) // Check if the char we got is . or - or a digit. If so, he will return true.
{
	if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-')
	{
		return true;
	}

	return false; 
}

ToSortArray* ToSortArray::legalInputCheck(int& n, int& requested_Index) // check Input Integrity.
{
	bool wrongInput = false;
	cin >> n >> requested_Index;
	if (n <= 0 || requested_Index < 1 || requested_Index > n) // check if requested_Index is between 1 to n & if n is a negative number.
	{
		wrongInput = true;
	}

	if (wrongInput) // If we find an input error, return null.
	{
		return nullptr;
	}
	else
	{
		string* buffer;
		double result;
    	int counter = 0;
		buffer = new string[n];
		ToSortArray* arr = new ToSortArray(n);

		for (int k = 0; k < n && wrongInput == false; k++)
		{
			cin >> buffer[k];
			if (ToSortArray::convert_String_To_Double(buffer[k], result)) // Check if the string we got is a double number with 1-4 digit only after the decimal point.
			{
				arr->AddToArray(result);
				counter++;
			}
			else
				wrongInput = true;
		}

		streambuf* pbuf = cin.rdbuf();
		int bufferRemainder = pbuf->in_avail();

		if (wrongInput || counter != n || bufferRemainder > 1) // Check if the user didn't enter n numbers / enter more than n numbers / enter an invaild input
		{
			delete arr; // Releases allocated memory.
			delete[] buffer; // Releases allocated memory.
			return nullptr; 
		}
		else
		{
			delete[] buffer; // Releases allocated memory.
			return arr;
		}
	}
}

bool ToSortArray::convert_String_To_Double(string number, double& result)
{
	bool there_Is_Decimal_Point = false;
	int digits_After_Point_Counter = -1;
	for (int index = 0; index < number.size(); index++) // pass over each char in the string
	{
		if (!isDigitOrPoint(number.at(index))) // check if the char we are checking is a digit / . (decimal point) / - (for negative number)
		{
			return false;
		}

		if (there_Is_Decimal_Point != false || number.at(index) == '.')
		{
			digits_After_Point_Counter++; // count how many digit has after the decimal point.æ
			there_Is_Decimal_Point = true;
		}
	}
	if (there_Is_Decimal_Point == false)
		return false; // the input is integer, not double.
	else if (digits_After_Point_Counter > 4)
		return false; // the input has more then four digits after the point.
	else
	{
		result = stod(number); // convert from string to double.
		return true;
	}
}

//----------------------------------------------------------------------// 

double ToSortArray::InsertionSort(int requested_Index) // Sort the double array and return the i-element in his size in the array.
{
	for (int i = 1; i <= this->m_End; i++) // pass over the array index 1 to n
	{
		bool stop = false;
		int j = i - 1;
		double temp = this->m_Sort_Array[i];

		while (j >= 0 && stop == false) 
		{
			if (temp < (this->m_Sort_Array)[j])
			{
				// swap elements of array that are bigger than temp, with the element in position ahead from their current position.
				// we want to make place for temp in the array, so we do a shift right. 
				ToSortArray::swap(this->m_Sort_Array[j + 1], this->m_Sort_Array[j]);
				j--;
			}
			else
				stop = true; 
		}

		this->m_Sort_Array[j + 1] = temp; // j+1 is now the position we need to enter temp into. 
	}

	return this->m_Sort_Array[requested_Index - 1]; // return the i-element in his size in the array.
}

double ToSortArray::SelectionSort(int requested_Index) // return recursively the i-element in his size of array.
{
	int pivot; 
	int leftPart; 

	pivot = this->Partition(); 
	leftPart = pivot - this->m_Start + 1;
	if (requested_Index == leftPart) 
		return this->m_Sort_Array[pivot];
	if (requested_Index < leftPart) 
	{
		if (this->set_End(pivot - 1)) // Search recursively in the left part of the current array. 
		{
			return this->SelectionSort(requested_Index);
		}
	}
	else                         
	{
		if (this->set_Start(pivot + 1)) // Search recursively in the right part of the current array. 
		{
			return this->SelectionSort(requested_Index - leftPart);
		}
	}
}

double ToSortArray::RecursiveFiveSort(int requested_Index)
{
	if (this->m_Array_Size <= SIZE_OF_EACH_ARRAY) // check if the size of the current array is smaller / eqval to 5.
	{
		this->BubbleSort(); // sort the array.
		return this->m_Sort_Array[(requested_Index - 1)];  // return the i - element in his size in the array.
	}
	else
	{
		int numOfSubArray = this->m_Array_Size / SIZE_OF_EACH_ARRAY; // claculate the number of A sub array.
		bool isDividedBy5 = this->m_Array_Size % SIZE_OF_EACH_ARRAY == 0; // check if the size of A array is divided by 5.
		int sizeOfB = isDividedBy5 ? numOfSubArray : numOfSubArray + 1; // if so, the size of B will be the number of A sub array, else he will be number of A sub array + 1.
		int preStartIndex = this->m_Start; // we will change the start index of array soon, so we will keep it ahead of time.

		ToSortArray B(sizeOfB); // create B array base the size we calulate before.

		for (int i = 0, j = this->m_Start; i < numOfSubArray; i++, j += SIZE_OF_EACH_ARRAY) // divide A to n/5 sub array by "playing" with end and start index in A array. 
		{
			if ((this->set_Start(j) && this->set_End(j + 4)))
			{
				this->BubbleSort(); // sort the current part in the array.
				B.AddToArray(this->m_Sort_Array[this->m_Start + 2]); // add the middle number in the current part in the array to the end of B array. 
			}
		}

		if (!isDividedBy5) // if A is not divided by 5.
		{
			int sizeOfRemainder = this->m_Array_Size % SIZE_OF_EACH_ARRAY; // calculate the size of the rest of the array.
			if (this->set_Start(this->m_End + 1) && this->set_End(this->m_End + sizeOfRemainder))
			{
				if (sizeOfRemainder <= 2) // if remainder is smaller than 3, we will add the first number in the remainder part. 
				{
					B.AddToArray(this->m_Sort_Array[this->m_Start]);
				}
				else // remainder is more than 3
				{
					this->BubbleSort(); // sort the array.
					B.AddToArray(this->m_Sort_Array[(sizeOfRemainder / 2) + this->m_Start]); // add the middle in the current part in the array to the end of B array. 
				}
			}
		}

		this->set_Start(preStartIndex); // update start to be previous start index (before divided A).

		double pivot = B.RecursiveFiveSort((sizeOfB / 2) + 1); // find in the recursion the median in B.
		int positionPivotInAArray = this->FindPositionElementInArray(pivot);  // find median position in A array. 
		ToSortArray::swap(this->m_Sort_Array[this->m_Start], this->m_Sort_Array[positionPivotInAArray]); // swap between the element in start position to the median position ia A array, so the median will be most lest in the current part of array.
		int k = this->Partition() + 1; // k is now the k-element in his size of array.
		// Notice!! k is the k-element in his size of array, and he is not the position of pivot that Partition returns.

		// k-1 is the position of pivot that Partition returns.
		if (requested_Index < (k - 1)) 
		{
			if (this->set_End(k - 2)) // Search recursively in the left part of the current array. 
			{
				if (this->set_ArraySize(this->m_End - this->m_Start + 1)) // update the size if the current array we want to search into.
				{
					return RecursiveFiveSort(requested_Index);
				}
			}
		}
		else if (requested_Index > (k - 1))
		{
			if (this->set_Start(k)) // Search in the recursively  right part of the current array.
			{
				if (this->set_ArraySize(this->m_End - this->m_Start + 1)) // update the size if the current array we want to search into.
				{
					return RecursiveFiveSort(requested_Index - k + this->m_Start);
				}
			}
		}
		else if (requested_Index == (k - 1)) 
		{
			return pivot; // he is the requested_Index-element in his size in the array.
		}
	}
}

int ToSortArray::FindPositionElementInArray(double val) // Find the position of current element in the current array. 
{
	for (int index = this->m_Start; index <= this->m_End; index++) // pass over the current array from index start to end
	{
		if (this->m_Sort_Array[index] == val) // if the current element in the array is eqval to the value we got as parameter, return his position (index) in the array. 
		{
			return index;
		}
	}
}

void ToSortArray::BubbleSort() // Sorting algorithm that works by repeatedly swapping the adjacent elements if they are in wrong order.
{
	for (int i = this->m_Start; i < this->m_End; i++)
	{
		int sizeOfJ = this->m_Start + this->m_End - i;
		for (int j = this->m_Start; j < sizeOfJ; j++)
		{
			if (this->m_Sort_Array[j] > this->m_Sort_Array[j + 1])
				ToSortArray::swap(this->m_Sort_Array[j], this->m_Sort_Array[j + 1]);
		}
	}
}

int ToSortArray::Partition()
// In each iteration, index moves one step towards pivot depending on the side pivot is located.
// In each iteration the distance between the index to pivot is reduced by 1.
// In the end, pivot will be in his position in the array (by his size) and in his left part will be numbers that arr smaller than his,
// and in his right part, will be numbers bigger than his.
{
	int pivot = this->m_Start;
	int index = this->m_End;

	while (pivot != index) 
	{
		if (pivot < index)
		{
			if (this->m_Sort_Array[pivot] > this->m_Sort_Array[index])
			{
				ToSortArray::swap(this->m_Sort_Array[pivot], this->m_Sort_Array[index]);
				ToSortArray::swap(pivot, index);
				index++;
			}
			else
			{
				index--;
			}
		}
		else
		{
			if (this->m_Sort_Array[pivot] < this->m_Sort_Array[index])
			{
				ToSortArray::swap(this->m_Sort_Array[pivot], this->m_Sort_Array[index]);
				ToSortArray::swap(pivot, index);
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

//----------------------------------------------------------------------// 

void ToSortArray::CalculateRunTimeInsertionSort(ofstream& file,int requested_Index) // Calculte run time of Insertion Sort algorithm.
{
	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	double result = this->InsertionSort(requested_Index);
	auto end = chrono::high_resolution_clock::now();
		// Calculating total time taken by the program.
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	file << "Time taken by function <Insertion sort> is : " << fixed
		<< time_taken << setprecision(9);
	file << " sec" << endl;

	cout << "Insertion sort i'th element: ";
	cout << fixed << setprecision(4) << result << endl;
}

void ToSortArray::CalculateRunTimeSelectionSort(ofstream& file, int requested_Index) // Calculte run time of Selection Sort algorithm.
{
	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	double result = this->SelectionSort(requested_Index);
	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	file << "Time taken by function <Selection sort> is : " << fixed
		<< time_taken << setprecision(9);
	file << " sec" << endl;

	cout << "Selection i'th element: ";
	cout << fixed << setprecision(4) << result << endl;
}

void ToSortArray::CalculateRunTimeRecursiveFiveSort(ofstream& file, int requested_Index) // Calculte run time of Recursive Five Sort algorithm.
{
	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	double result = this->RecursiveFiveSort(requested_Index);
	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	file << "Time taken by function <Recursive five sort> is : " << fixed
		<< time_taken << setprecision(9);
	file << " sec" << endl;

	cout << "Quintuplet algorithm i'th element: ";
	cout << fixed << setprecision(4) << result << endl;
}

//----------------------------------------------------------------------// 
