#pragma once
#include<iostream>
#include<string>
using namespace std;

class Composers {
public:
	string name;
	int death;
};

int getNumberOfComposers(ifstream&);
void createDatabase(Composers*, ifstream&, int);

