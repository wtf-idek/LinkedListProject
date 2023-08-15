////
// Name: Jill Johnson
// Section: A
// Program Name: P3 MYString v2
//
// Description: This class creates cstring objects utalizing dymanic memory and pointers.
// This class has several member functions and overloaded operator funtions that allow programmers to retrieve and manipulate
// data.
////

#ifndef JJSTRING_H
#define JJSTRING_H

#include<iostream>
#include<fstream>
#include<cctype>

using std::istream;
using std::ostream;

class JJString{
public:
	JJString();//default constructor
	JJString(const char* cstr);//creates a string that contains the information from the argument.
	JJString(const JJString& mstr); //copy constructor
	~JJString(); //destructor
	int length() const;//the length of the string
	int capacity();//the total amount of memory available for use
	char at(int index) const;//returns the character at a certain location
	char* c_str() const;//return a pointer to a constant cstring version of the JJString object.
	JJString& operator=(const JJString& cstr); //=overload
	char operator[](int i) const; // [] overload
	friend istream& operator>>(istream& istrm, JJString& cstr); // >> overload
	friend ostream& operator<<(ostream& ostrm, const JJString& cstr); //<< overload
	JJString operator+(const JJString& rstr); //combines two class objects
	bool operator<(const JJString& argStr) const; // compares for less than
	bool operator>(const JJString& argStr) const; // compares for greater than
	bool operator==(const JJString& argStr) const; // compares for equals to
	bool operator!=(const JJString& argStr) const; //compares for not equals to
	static int getCurrentCount(); //static func returns how many class objects are in use
	static int getCreatedCount(); //static func returns how many class objects have been made
	

private:
	char* str; //pointer to dynamic memory for storing the string
	int cap; //size of the memory that is available to be used (start with 20 char's and then double it whenever this is not enough)
	int end; //	index of the end of the string(the '\0' char)
	static int currentCount; //tracks how many class objects are currently in use
	static int createdCount; //tracks how many class objects have been created
};

#endif
