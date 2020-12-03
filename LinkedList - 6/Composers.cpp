#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Composer.h"
using namespace std;

//reads the each line in the file which corresponds to
//the number of composers.
//passes in the file and returns an int
int getNumberOfComposers(ifstream& inFile) {
	string lineRead;
	int count = 0;
	if (inFile) {
		while (getline(inFile, lineRead)) {
			count++;
		}
	}

	inFile.clear();
	inFile.seekg(0, inFile.beg);
	return count;
}

//creates a temporary database for composers in the heap
//which will be deleted once the values are
//inserted and copied into the list
void createDatabase(Composers* compPtr, ifstream& inFile, int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		getline(inFile, compPtr[i].name, ',');
		inFile.ignore();
		inFile >> compPtr[i].death;
		inFile.ignore();
	}
}


