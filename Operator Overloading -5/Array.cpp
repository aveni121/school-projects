#include <iostream>
#include <time.h>
#include "Array.h"
using namespace std;

//contains definitions of class

//default constructor
Array::Array() 
{
	arrPtr = nullptr;
	arrSize = 0;
}

//overloaded constructor
Array::Array(int size) { 
	arrSize = size;
	arrPtr = new int[size];
	totalElements += arrSize; //track total elements
}

//performs a deep copy
Array::Array(const Array& objCopy) { 
	if (this != &objCopy) { //check if addresses are same
		arrSize = objCopy.arrSize;
		totalElements += arrSize; //track total elements
		arrPtr = new int[arrSize];
		for (int i = 0; i < arrSize; i++) {
			*(arrPtr + i) = *(objCopy.arrPtr + i);
		}
	}
}

//returns a reference at the ith/val position
int& Array::operator[](int val) { 
	return arrPtr[val];
}

//performs a deep copy
Array& Array::operator=(const Array& objCopy) { 
	if (this != &objCopy) {
		delete[] arrPtr;
		totalElements -= arrSize;
		arrSize = objCopy.arrSize;
		totalElements += arrSize;
		arrPtr = new int[arrSize];
		for (int i = 0; i < arrSize; i++)
			*(arrPtr + i) = *(objCopy.arrPtr + i);
	}
	return *this;
}

//appends an array into another array
Array& Array::operator+=(const Array& objAdd) {
	if (this != &objAdd) {
		int tempSize = this->getSize();	//store the array in temp values
		int* tempArr = new int[tempSize];
		for (int i = 0; i < tempSize; i++) {
			tempArr[i] = *(this->getVal() + i);
		}

		delete[] arrPtr; //delete old array
		totalElements -= arrSize;
		arrSize = tempSize + objAdd.getSize(); //sum of size of two arrays
		arrPtr = new int[arrSize]; //create new array with sum

		//initialize first values with
		//previously stored values in temp
		for (int i = 0; i < tempSize; i++) {
			arrPtr[i] = tempArr[i];
		}

		//NOTE: start where previous loop ended
		//but appended values are at index 0 of objAdd
		for (int j = tempSize, k = 0; j < arrSize; j++, k++) {
			arrPtr[j] = *(objAdd.getVal() + k);
		}
		delete[] tempArr;//delete temp array from heap
	}
	return *this;
}

//shuffles the array
Array& Array::operator!() { 
	srand(time(NULL));
	int randomIndex;

	//shuffle by swapping values
	for (int i = 0; i < arrSize; i++) {
		randomIndex = rand() % arrSize;
		int temp = arrPtr[i];
		arrPtr[i] = arrPtr[randomIndex];
		arrPtr[randomIndex] = temp;
	}
	return *this; //returns values
}

//increments each value by 1
//will return values before incrementation
Array Array::operator++(int one) { 
	Array beforeInc = *this; //save the data of Array before incrementation

	for (int i = 0; i < arrSize; i++) {
		arrPtr[i]++; //apply post incrementation
	}

	totalElements -= beforeInc.arrSize;
	return beforeInc;
}

//decrements each value by 1
Array& Array::operator--() {
	for (int i = 0; i < arrSize; i++) {
		arrPtr[i] -= 1;
	}
	return *this;
}

//finds minimum value and returns it
int Array::operator*() { 
	int min = arrPtr[0];
	for (int i = 1; i < arrSize; i++) {
		if (arrPtr[i] < min)
			min = arrPtr[i];
	}
	return min;
}

//Prints out array into output stream
//NOTE: os is cout in this case
ostream& operator<<(ostream& os, const Array& arr1) {
	for (int i = 0; i < arr1.getSize(); i++) {
		os << (*(arr1.getVal() + i)) << " ";
	}
	os << endl;
	return os;
}

//checks if individual in-order values of arr1
//is a subset of arr2
bool operator==(const Array& arr1, const Array& arr2) {
	int arr1Size = arr1.getSize();
	int arr2Size = arr2.getSize();
	int length;
	bool flag = true;//tracks validity 

	//check which array has a lower size and use that length in for loop
	//this prevents printing out of bounds access
	if (arr1Size > arr2Size)
		length = arr2Size;
	else if (arr2Size > arr1Size)
		length = arr1Size;
	else //if arrays are equal it will just use the length of arr1
		length = arr1Size;

	for (int i = 0; i < length; i++) {
		if (*(arr1.getVal() + i) != *(arr2.getVal() + i)) { 
			flag = false;
		}
	}
	return flag;
}

//checks if values of arr1 is < or > arr2
bool operator<(const Array& arr1, const Array& arr2) {
	int length = arr1.getSize();
	bool flag = true; //tracks validity
	int val1;
	int val2;
	for (int i = 0; i < length; i++) {
		val1 = *(arr1.getVal() + i);
		val2 = *(arr2.getVal() + i);
		if (val1 < val2) {
			flag = true;
			break;
		}
		else if (!(val1 < val2))
			flag = false;
		else
			flag = false;
	}
	return flag;
}

//static int definition
int Array::totalElements = 0;

//destructor
Array::~Array() {
	delete[] arrPtr;
}