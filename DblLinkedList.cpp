#include "DblLinkedList.h"
#include <iostream>
#include <string>
#include "JJStringList.h"


using namespace std;

DblLinkedList::DblLinkedList() {
	head = nullptr;
	tail = nullptr;
	it = nullptr;
	count = 0;
}

DblLinkedList::DblLinkedList(const DblLinkedList& dll) {
	head = dll.head;
	tail = dll.tail;
	it = dll.head;
	dll.it = dll.head;
	for (int i = 0; i <= dll.count; ++i) {
		it = dll.it;
		it->prev = dll.it->prev;
		it->next = dll.it->next;
		dll.it = dll.it->next;
	}
	count = dll.count;
	cout << "using copy constructor" << endl;
}

//this is commented out because it throws an error and as far as I can tell it shouldn't
//I've been ignoring this problem for now
//DblLinkedList::~DblLinkedList(){ //destructor
//	//Node* tempPtr = head;
//	//head = head->next;
//
//	//while (head != nullptr)
//	//{
//	//	delete tempPtr;
//	//	--count;
//	//	tempPtr = head;
//	//	head = head->next;
//	//}
//	//tail = nullptr;
//
//	head = nullptr;
//}


bool DblLinkedList::push_back(const JJString& str) {
	Node* newNode = new Node(str);
	newNode->prev = tail;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = nullptr;
	}
	tail = newNode;
	count++;

	return true;
}

void DblLinkedList::resetIterator() const {	
	it = head;
}

bool DblLinkedList::hasMore() const {
	if (it == tail) {
		return false;
	}
	else {
		return true;
	}
}
//THE REAL PROBLEM WAS HIDING HERE ALL ALONG
JJString DblLinkedList::next() const {
	//gets the string the it pointer is pointing to
	//then moves the it pointer to next "node" (could be nullptr)
	JJString stub;
	stub = it->data;
	if (it->next != nullptr) {
		it = it->next;

		return stub;
	}
	else {
		it = tail->prev;
		it->next = nullptr;
		return "null";

	}
}

void DblLinkedList::testConnections() {	
	// write test for connections:  loop through the list testing each node 
	if (head == nullptr) {
		cout << "Empty list" << endl;
	}
	else if (head != nullptr) {
		int i;
		resetIterator();
		for (i = 1; it != tail; ++i) {
			next();
		}
		cout << "TEST CONNECTIONS Passed\n";
	}
		
}

//output the data to the ostream (separate each string with a blank space)
ostream& operator<<(ostream& ostrm, DblLinkedList& dll) {
	if (dll.head == nullptr) {
		cout << "Empty list" << endl;
	}
	else {
		dll.it = dll.head;
		while (dll.it != dll.tail) {
			cout << dll.it->data << " ";
			dll.next();
		}
		cout << dll.it->data << " ";
	}

	return ostrm;
}

//assignment operator
bool DblLinkedList::operator=(const DblLinkedList& dll) {
	if (this != &dll) {
		this->head = dll.head;
		this->tail = dll.tail;
		dll.resetIterator();
		this->it = dll.it;
		while(this->it != tail) {
			this->it = dll.it;
			dll.next();
			count++;
		}
		return true;
	}
	else {
		return false;
	}
	
}

///*insert the string argument into the list in the proper 
//place (smallest to largest). Do not insert the string if 
//the DLL already has a string of that value. Return true 
//if the string was inserted, otherwise return false*/
bool DblLinkedList::insert(const JJString& str) {
	resetIterator();

	if (it != nullptr) {
		while (it != nullptr) {
			if (it->data == str) {
				cout << str << " is already in the list" << endl;
				return false;
			}
			it = it->next;
		}
		resetIterator();

		Node* newItem;
		newItem = new Node(str);

		if (head != nullptr) {
			it = head;
			int length = str.length();
			int compLength = it->data.length();

			while ((length > compLength) && (it->next != nullptr)) {
				it = it->next;
				compLength = it->data.length();

			}

		
			if (it->next != nullptr) {
				Node* temp = it;
				newItem->next = temp->next;
				temp->next = newItem;
				newItem->prev = temp;
				
				count++;
			}
			else {
				push_back(str);
			}

		}
		return true;
	}
	cout << "Error inserting item" << endl;
	return false;
}

//if the string argument is found in the DLL remove it from the DLL object. Return true if a string was removed, otherwise return false.
bool DblLinkedList::remove(const JJString& str) { //not working when removed from front of list;
	JJString tempStr;
	if (head != nullptr) { //list is not empty
		resetIterator(); //set iterator to head
		tempStr = it->data;

		while ((tempStr != str) && (it->next != nullptr)) { //while the data isn't the string not at the end
			tempStr = it->data;
			it = it->next; //move through list
		}

		if (tempStr == str) { //if data is the string 
			Node* temp = it;
			//breaks after this
			if (it == head) { //if begining of list
				head = temp->next;
				it = temp->next;
			}
			else if((it != head) && (it->next != nullptr)){ //if mid list
				it = temp->prev;
				it->next = temp->next;
			}
			else if (it->next == nullptr) { //if end of list
				it = temp->prev;
				tail = temp;
			}

			count--;
			return true;
		}
		
		else if (tempStr != str) { //if the data is not the string
			return false;
		}
	}
	cout << "Error removing item" << endl;
	return false;
}

int DblLinkedList::getCount() {
	if (head == nullptr) {
		return 0;
	}
	return count;
}
