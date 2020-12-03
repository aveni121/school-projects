#pragma once
#include <iostream>
using namespace std;

//Class declaration containing function declarations
class Array{
public:

	Array();
	Array(int size);
	Array(const Array&);
	~Array();
	int getSize() const { return arrSize; }
	int* getVal() const { return arrPtr; }
	int& operator[](int);
	Array& operator=(const Array&);
	Array& operator+=(const Array&);
	Array& operator!();
	Array operator++(int);
	Array& operator--();
	friend bool operator==(const Array&, const Array&);
	friend ostream& operator<<(ostream&, const Array&);
	friend bool operator<(const Array&, const Array&);
	int operator*();
	static int getNumberOfElements() { return totalElements; }

private:
	int* arrPtr;
	int arrSize;
	static int totalElements;

};

