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
	//~DblLinkedList(); //destructor
	bool push_back(const JJString& str);
	void resetIterator() const ;
	bool hasMore() const;
	JJString next() const;
	void testConnections();
	bool operator=(const DblLinkedList& dll);//assignment operator
	 
	//output the data to the ostream (separate each string with a blank space)
	friend ostream& operator<<(ostream& ostrm, DblLinkedList& dll);
	 
	//insert the string argument into the list in the proper 
	//place (smallest to largest). Do not insert the string if 
	//the DLL already has a string of that value. Return true 
	//if the string was inserted, otherwise return false
	bool insert(const JJString& str);
	 
	//if the string argument is found in the DLL remove it from the DLL object. Return true if a string was removed, otherwise return false.
	bool remove(const JJString & str); 
	
	//returns the number of strings that are stored in the DLL.
	int getCount();


  private:
	Node *head, *tail;
	mutable Node* it; // mutable Node * { used as the "iterator" to move through the list by using next( ), resetIteration( ), and hasMore( ) }
	int count;
};

#endif
