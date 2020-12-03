#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Composer.h"
#include "Node.h"
using namespace std;

template <typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	bool isEmpty();
	void printList() const;
	void append(const T data);
	void prepend(const T data);
	bool removeFront();
	void insert(const T data);
	bool remove(const T data);
	bool find(const T data);
	T getFirst() const;
	T getLast() const;
private:
	Node<T>* head;
	Node<T>* tail;
};

//Default constructor sets everything to null
template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

//destructor iterates through the list
//deletes each node starting from the head
//until it reaches nullptr
template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* nodePtr = head;
	while (nodePtr != nullptr) {
		head = head->next;
		delete nodePtr;
		nodePtr = head;
	}
};

//isEmpty() checks if the head is not null
//if head is null, list is empty returns true
//else returns false
template <typename T>
bool LinkedList<T>::isEmpty() {
	if (head == nullptr)
		return true;
	else
		return false;
}

//Appends to the end of the list
//If list is empty sets the node as the head
//and tail
template <typename T>
void LinkedList<T>::append(const T data) {
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}

	else {
		Node<T>* nodePtr = head;
		while (nodePtr->next) {
			nodePtr = nodePtr->next;
		}

		nodePtr->next = newNode;
		tail = newNode;
	}
}

//Prepends a node to the beginning of the list
template <typename T>
void LinkedList<T>::prepend(const T data) {
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	if (isEmpty()) {
		newNode->data = data;
		head = newNode;
		tail = newNode;
	}

	else {
		newNode->next = head;
		head = newNode;
	}
}

//Removes the front Node
template <typename T>
bool LinkedList<T>::removeFront() {
	if (isEmpty()) {
		return false;
	}

	else {
		Node<T>* newNode = head;
		head = head->next;
		delete newNode;
		return true;
	}
}

//Accepts a value and will insert the value into 
//the linked list in the correct order.
//(Numerical ascending order)
//the trailNode is key here
//The idea is to find the two nodes the new node
//is to be inserted in between in
template <typename T>
void LinkedList<T>::insert(const T data) {

	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	if (isEmpty()) {
		newNode->data = data;
		head = newNode;
		tail = newNode;
	}

	else if (head->data > data) {
		newNode->next = head;
		head = newNode;
	}

	else {
		Node<T>* currNode = head;
		Node<T>* trailNode = head;
		while (!(currNode->data > data)) {
			currNode = currNode->next;
			if (currNode == nullptr) {
				tail = newNode;
				break;
			}
			else if (!(currNode->data > data)) {
				trailNode = trailNode->next;
			}
		}
		trailNode->next = newNode;
		newNode->next = currNode;
	}
}

//Accepts a value and will remove the node with that value from the list. 
//If the list is empty, the function returns false
//else it iterates through the list to search for the number
//Return true if the node was found
//and removed and return false otherwise.
//It's still important to track the trail node
//so that after removing a node, it will be updated
//to point to the succeeding node.
template <typename T>
bool LinkedList<T>::remove(const T data) {
	if (isEmpty()) {
		cout << "The list is empty" << endl;
		return false;
	}

	else if (data == head->data) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}

	else {
		Node<T>* nodePtr = head;
		Node<T>* trailNode = head;
		while (data != nodePtr->data && nodePtr != nullptr) {
			nodePtr = nodePtr->next;
			if (data != nodePtr->data) {
				trailNode = trailNode->next;
			}
		}

		if (nodePtr == nullptr) {
			return false;
		}

		else {
			trailNode->next = nodePtr->next;
			if (trailNode->next == nullptr) {
				tail = trailNode;
			}
			delete nodePtr;
		}
	}
}

//Searches for the data being passed in
//if it's in the list or not.
//returns true if data is in the list
//if not it returns false
template <typename T>
bool LinkedList<T>::find(const T data) {
	Node<T>* nodePtr = head;
	bool matchFound = false;
	while (nodePtr != nullptr) {
		if (data == nodePtr->data) {
			matchFound = true;
			break;
		}
		nodePtr = nodePtr->next;
	}
	return matchFound;
}

//gets the data at the head of the list
template <typename T>
T LinkedList<T>::getFirst() const {
	return head->data;
}

//gets the data at the tail of the list
template <typename T>
T LinkedList<T>::getLast() const {
	return tail->data;
}

//Prints all the data in the list
template <typename T>
void LinkedList<T>::printList() const {
	Node<T>* nodePtr = head;
	while (nodePtr != nullptr) {
		cout << " " << nodePtr->data;
		nodePtr = nodePtr->next;
	}
}

//overloaded operators

//for insert function
template <typename T>
bool operator>(const Composers& nodeData, T& newData) {
	if (nodeData.death > newData.death) {
		return true;
	}
	else {
		return false;
	}
}

//for printlist function
//prints the name and time of death of the composer
ostream& operator<<(ostream& os, const Composers& nodeData) {
	os << nodeData.name << " - " << nodeData.death << endl;
	return os;
}

//for remove function
//checks if the name entered is in the list
//if it is, it prints out the name
//you might notice the static bool firstCall here
//I used it because  my remove function calls
//'!=' twice. If it wasn't there it would print twice.
//With it, the name is printed either in the first call
//or the second call depending on the iteration
template <typename T>
bool operator!=(const T& userData, const Composers& nodeData) {
	if (&nodeData != nullptr) {
		string strToParse = nodeData.name;
		string strToFind = userData.name;
		static bool firstCall = true;
		//allows for a case insensitive search
		for (int i = 0; i < strToFind.length(); i++) {
			strToFind[i] = tolower(strToFind[i]);
		}

		for (int i = 0; i < strToParse.length(); i++) {
			strToParse[i] = tolower(strToParse[i]);
		}

		//checks if there's a match
		if (strToParse.find(strToFind) != string::npos) {
			if (firstCall) {
				cout << endl << setw(15) << " " << nodeData.name;
				firstCall = false;
			}
			else
				firstCall = true;
			return false;
		}
		else
			return true;
	}
}

//for find function
//checks if the name entered is in the list
//if it is it prints out the name
template <typename T>
bool operator==(const T& userData, const Composers& nodeData) {
	if (&nodeData != nullptr) {
		string strToParse = nodeData.name;
		string strToFind = userData.name;
		//allows for a case insensitive search
		for (int i = 0; i < strToFind.length(); i++) {
			strToFind[i] = tolower(strToFind[i]);
		}

		for (int i = 0; i < strToParse.length(); i++) {
			strToParse[i] = tolower(strToParse[i]);
		}

		//checks if there's a match
		if (strToParse.find(strToFind) != string::npos) {
			cout << endl << setw(15) << " " << nodeData.name;
			return true;
		}
		else
			return false;
	}
}

//To process the input and returns the char inputted by user
//used Composers object instead of string
//so that there will be no need to overload
//the () operator.
//user input will be stored in searchFor.name
char processInput(char choice, Composers searchFor, LinkedList<Composers>& composerList) {
	cout << "Enter 's' to search, 'r' to remove, 'd' to display,"
		<< "or 'e' to exit: ";
	cin >> choice;
	cin.ignore(10000, '\n');
	switch (choice) {
	case 's':
		cout << "Enter a composers name to search for: ";
		getline(cin, searchFor.name);
		if (composerList.find(searchFor))
			cout << " was found in the list\n" << endl;
		else {
			cout << endl << setw(15) << " " << searchFor.name
				<< " was not found\n" << endl;
		}
		break;
	case 'r':
		cout << "Enter a composer's name to remove: ";
		cin >> searchFor.name;
		if (composerList.remove(searchFor))
			cout << " was successfully removed from the list\n\n";
		else {
			cout << endl << setw(15) << " " << searchFor.name
				<< " was not found\n" << endl;
		}
		break;
	case 'd':
		composerList.printList();
		break;
	case 'e':
		cout << endl << setw(15) << " " << "Exiting...\n" << endl;
		break;
	default:
		cout << endl << setw(15) << " " << "INVALID INPUT\n" << endl;
		break;
	}
	return choice;
}