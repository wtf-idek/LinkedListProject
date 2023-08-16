#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H
#include <iostream>
#include <string>
#include "JJStringList.h"

using namespace std;

class Node {   // fully defined here due to its simplicity
	public:
	Node() {
		next = prev = nullptr;
	}
	Node(JJString cstr) {
		data = cstr;
		next = prev = nullptr;
	}

	JJString data;
	Node *next;
	Node *prev;
};


class DblLinkedList {
  public:
	DblLinkedList();
	DblLinkedList(const DblLinkedList& dll); //copy constructor
	~DblLinkedList(); //destructor
	bool push_back(const JJString& str); //places new str at the end of the list
	void resetIterator() const; //resets the itereator to the beginning
	bool hasMore() const; //checks to see if there is more to the list
	JJString next() const; // returns the current string and moves to the next 
	void testConnections(); // tests connections
	bool operator=(const DblLinkedList& dll); //assignment operator
	friend ostream& operator<<(ostream& ostrm, DblLinkedList& dll); //output the data to the ostream (separate each string with a blank space)
	bool insert(const JJString& str); //insert the string argument into the list in the proper place
	bool remove(const JJString & str); //if the string argument is found in the DLL remove it from the DLL object
	int getCount(); //returns the number of strings that are stored in the DLL.

  private:
	Node *head, *tail;
	mutable Node* it; // mutable Node * { used as the "iterator" to move through the list by using next( ), resetIteration( ), and hasMore( ) }
	int count;
};

#endif
