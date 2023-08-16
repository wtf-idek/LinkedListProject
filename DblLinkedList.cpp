#include "DblLinkedList.h"
#include <iostream>
#include <string>
#include "JJStringList.h"


using namespace std;

DblLinkedList::DblLinkedList() { //constructor
	head = nullptr;
	tail = nullptr;
	it = nullptr;
	count = 0;
}

DblLinkedList::DblLinkedList(const DblLinkedList& dll) { //copy constructor

	dll.resetIterator(); //starts dll at begining
	head = dll.head;
	tail = dll.tail;
	it = dll.head; 

	for (int i = 0; i < dll.count; ++i) { //copies it all over
		it = dll.it;
		if (dll.it != nullptr) {
			dll.it = dll.it->next;
		}
	}
	count = dll.count;
}

DblLinkedList::~DblLinkedList(){ //destructor
	Node* tempPtr = head; //sets a new pointer to the head
	head = head->next; //sets head to next

	while (head != nullptr){ //cycles through until empty
		delete tempPtr; //deletes the info at tempPtr
		tempPtr = head; //resets the pointer to head
		head = head->next; //sets the head to the next thing
	}
	
}


bool DblLinkedList::push_back(const JJString& str) {
	Node* newNode; //new node for item
	newNode = new Node(str); //adds string info

	if (head == nullptr) { //if list is empty
		head = newNode;
		tail = newNode;
		it = newNode;
	}
	else {
		it = tail; //points to end
		it->next = newNode; //from end, the next thing is the new string
		newNode->prev = it; //the previous string is the the previous end
		newNode->next = nullptr; //the next thing is null
		it = newNode; //now the iteration is at the new node
		tail = it; //and so is the tail
	}
	
	count++;

	return true;
}

void DblLinkedList::resetIterator() const { //resets the iterator to the begining
	it = head;
}

bool DblLinkedList::hasMore() const { //checks for more
	if (it->next ==  nullptr) { //returns false if at the end
		return false;
	}
	else { //returns true otherwise
		return true;
	}
}

JJString DblLinkedList::next() const { //gets the string the it pointer is pointing to then moves the it pointer to next "node" 

	JJString stub;

	if (it->next != nullptr) { //if not at the end
		stub = it->data; //creates a string of the data that the iterator is pointing at
		it = it->next; //moves the iterator
 //returns the string
	}
	else { //if at the end
		it = tail->prev; //it doesn't move
		it->next = nullptr; //the next thing will be null
		stub = "\0"; //returns a null string

	}

	return stub;
}

void DblLinkedList::testConnections() { // write test for connections:  loop through the list testing each node 
	if (head == nullptr) { //checks for a list
		cout << "Empty list" << endl;
	}
	else if (head != nullptr) { //goes through each item on list
		resetIterator();
		while (it->next != nullptr) {
			it = it->next;
		}

		cout << "TEST CONNECTIONS Passed\n"; //yay pass
	}
	else {
		cout << "TEST CONNECTIONS failed\n"; //some sort of failure
	}

}

ostream& operator<<(ostream& ostrm, DblLinkedList& dll) {//output the data to the ostream (separate each string with a blank space)
	if (dll.head == nullptr) { //checks for list
		cout << "Empty list" << endl;
	}
	else { //goes through list and outputs until the end
		dll.it = dll.head;
		while (dll.it->next != nullptr) {
			ostrm << dll.it->data << " ";
			dll.next();
		}
		ostrm << dll.it->data << " "; //outputs the final pieces of data
	}

	return ostrm;
}

bool DblLinkedList::operator=(const DblLinkedList& dll) { //assignment operator

	if (this != &dll) { //if not already pointing at the list 

		this->head = dll.head; //copies head
		this->tail = dll.tail; //copies tail
		dll.resetIterator(); //resets the itrerator just in case
		this->it = this->head; //this is now pointing at it's head

		while (this->it->next != nullptr) { //while not at end
			this->it = dll.it; //copies each node
			dll.next(); //moves to the next
			count++;
		}
		return true; //when finished
	}
	else {
		return false; //some sort of error
	}

}

/*insert the string argument into the list in the proper 
place (smallest to largest). Do not insert the string if 
the DLL already has a string of that value. Return true 
if the string was inserted, otherwise return false*/
bool DblLinkedList::insert(const JJString& str) {

	resetIterator(); //start from the begining

	if (head != nullptr) { //if not empty
		while (it != nullptr) { //checks to see if str is already in the list
			if (it->data == str) {
				cout << str << " is already in the list" << endl;
				return false; //ends if in the list
			}
			it = it->next;
		}
		resetIterator(); //starts over

		Node* newItem = new Node(str); //creates a new item with data

		int length = str.length(); //getting size to put in proper place
		int compLength = it->data.length();

		while ((length > compLength) && (it->next != nullptr)) { //compares the lengths
			it = it->next;
			compLength = it->data.length();

		}


		if (it->next != nullptr) { //if not the longest, puts in proper place
			Node* temp = it;
			newItem->next = temp->next;
			temp->next = newItem;
			newItem->prev = temp;
			count++;
		}
		else { //if longest, puts at end
			push_back(str); //no count++ because pushback() adds to count
		}

		return true;
	}
	if (head == nullptr) { //if empty list
		Node* newItem = new Node(str);
		head = newItem;
		it = newItem;
		tail = newItem;
		count++;
		return true;
	}

	cout << "Error inserting item" << endl; //there was an error
	return false;
}

//if the string argument is found in the DLL remove it from the DLL object. Return true if a string was removed, otherwise return false.
bool DblLinkedList::remove(const JJString& str) { 

	JJString tempStr;

	if (head != nullptr) { //list is not empty
		resetIterator(); //set iterator to head

		while ((tempStr != str) && (it->next != nullptr)) { //as long as the strings don't match and we're not at the end of the list
			tempStr = it->data; //a temporary string is equal to the data that is being pointed at
			if (it->next != nullptr) { //if not at end
				it = it->next; //move through the list
			}
		}

		if (tempStr == str) { //if data is the string 
			Node* temp = it->prev; //goes back one because of previous list movement

			if (temp == head) { //if begining of list
				head = temp->next;
				it = head;
				delete temp; //deletes item
			}
			else if ((temp != head) && (temp->next != nullptr)) { //if mid list
				it = temp->prev; 
				it->next = temp->next;
				delete temp; //deletes item
			}
			else if (temp->next == nullptr) { //if end of list
				it = temp->prev;
				tail = it;
				delete temp; //deletes item
			}

			count--; 
			return true;
		}

		else if (tempStr != str) { //if the data is not the string
			return false;
		}
	}
	cout << "Error removing item" << endl; //if there's an error of some sort to get here
	return false;
}

int DblLinkedList::getCount() { //returns the number of items on list
	if (head == nullptr) { //if empty list
		return 0;
	}
	return count;
}
