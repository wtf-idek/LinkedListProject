#include<iostream>
#include<fstream>
#include<cctype>
#include "JJStringList.h"

using namespace std;

//default constructor
JJString::JJString() { //creates an empty string
	cap = 20;
	end = 0;
	str = new char[20];
	str[end] = '\0';

	++createdCount;
	++currentCount;
}


//creates a string that contains the information from the argument.
JJString::JJString(const char* cstr) { 
	cap = 20;
	end = 0;


	while (cstr[end] != '\0') {
		++end;
		if (end % 20 == 0) {
			cap += 20;
		}
	}

	str = new char[cap];

	for (int i = 0; i <= end; ++i) {
		str[i] = cstr[i];
	}

	++createdCount;
	++currentCount;
}

//copy constructor
JJString::JJString(const JJString& cstr) {
	end = 0;

	for (int i = 0; cstr.str[i] != '\0'; ++i) {
		end++;
	}

	cap = ((end + 20) / 20) * 20;
	
	str = new char[cap];

	int i=0;
	
	if (end > 0 && i < cap) {
		for (i = 0; i <= cstr.length(); ++i) {
			str[i] = cstr.str[i]; //VS give me a warning for this so it's probably the cause of my problems
		}
	}

	++createdCount;
	++currentCount;
}

//destructor
JJString::~JJString() {
	delete [] str; // give back dynamic mem
	--currentCount;
}

//the length of the string
int JJString::length() const { 
		return this->end;
}

//the total amount of memory available for use
int JJString::capacity(){

	return this->cap;
}

//returns the character at a certain location
char JJString::at(int index) const {

	if ((index >= end) || (index < 0)) { //If the index is not inside the string(negative or too large) then return '\0'
		return '\0';
	}
	else {
		return this->str[index];
	}

}

//return a pointer to a constant cstring version of the JJString object.
char* JJString::c_str() const {

	return str;
}

//assignment operator function
JJString& JJString::operator=(const JJString& cstr) {
	
	if (this != &cstr) {
		delete[] str;
		str = new char[cstr.cap];
		this->end = cstr.end;
		this->cap = cstr.cap;

		for (int i = 0; i <= this-> end; ++i) {
			str[i] = cstr.str[i];
		}
		
	}
	return *this;
}

//[] operator returns the character at a certain location.  No Error checking.  Fast but dangerous
char JJString::operator[](int i) const {
	return str[i];
}

//ostream << overload function using friend
ostream& operator <<(ostream& ostrm, const JJString& cstr) {
	for (int i = 0; i < cstr.end; ++i) {
		ostrm << cstr.str[i];
	}
	return ostrm;
}

//istream >> overload function using friend
istream& operator>>(istream& istrm, JJString& jjs) { 
	char inputWords[100];
	int punct = 0;
	if (istrm >> inputWords) { 
		jjs.end = 0; 
		while (inputWords[jjs.end] != '\0' && jjs.end < 99) { 
			jjs.end++;
			if (jjs.end % 20 == 0) {
				jjs.cap += 20;
			}

		} 
	}


	int tempCap = jjs.cap;
	int tempEnd = jjs.end;

	//could not get this to work as a stand alone if  statement so I'll take what I can get
	for (int i = 0; i < tempEnd; ++i) { //looking for trailing punctuation
		if (inputWords[i + 1] == '\0') { //only if the next thing is the end marker
			if (ispunct(inputWords[i])) { //if last char is a punctuation
				inputWords[i] = '\0'; //set it to the end
				tempEnd = tempEnd - 1; //end of the array updated
			}
		}
	}

	delete[] jjs.str;
	jjs.str = new char[tempCap];
	jjs.cap = tempCap;
	jjs.end = tempEnd;

	for (int i = 0; i <= tempEnd; ++i) {
		jjs.str[i] = inputWords[i];
	}

	return istrm; 
}

//+ operator overload function
JJString JJString::operator+(const JJString& rstr) {
	
	int newEnd = this->length() + rstr.length();
	int newCap;

	newCap = ((newEnd+20)/ 20) * 20; 

	JJString newString;
	delete[] newString.str;

	newString.str = new char[newCap];
	newString.cap = newCap;
	newString.end = newEnd;

	for (int i = 0; i < this->end; ++i) {
		newString.str[i] = this->str[i];
	}

	for (int i = this->end; i <= newEnd; ++i) {
		newString.str[i] = rstr.str[i- this->end];
	}

	return newString;
}

// < opperator overload funtion
bool JJString::operator<(const JJString& argStr) const  {
	int i = 0;
	JJString temp1 = str; //temp strings to compare
	JJString temp2 = argStr.str;

	if ((isupper(temp1.str[0])) && (temp1.str[0] != '\0')) { //checks if the first char in each array is upper and changes if needed
		char tChar = tolower(temp1.str[0]);
		temp1.str[0] = tChar;
	}
	if (isupper(temp2.str[0]) && (temp2.str[0] != '\0')) {
		char tChar2 = tolower(temp2.str[0]);
		temp2.str[0] = tChar2;
	}


	while ((temp1[i] == temp2[i]) && (temp1[i] != '\0') && (temp2[i] != '\0')) {

		if ((isupper(temp1.str[i + 1])) && (temp1.str[i + 1] != '\0')) { //checks to see if the next char is upper
			char c = tolower(temp1.str[i + 1]); //changes to lower for comparison
			temp1.str[i + 1] = c;
		}
		if ((isupper(temp2.str[i + 1])) && (temp2.str[i + 1] != '\0')) {
			char s = tolower(temp2.str[i + 1]);
			temp2.str[i + 1] = s;
		}

		++i;
	}

	if (temp2.str[i] < temp1.str[i]) {
		return true;
	}
	else {
		return false;
	}
}

// > operator overload function
bool JJString::operator>(const JJString& argStr) const {
	int i = 0;
	JJString temp1 = this->str; //temporary strings to compare 
	JJString temp2 = argStr.str;


	if ((isupper(temp1.str[0])) && (temp1.str[0] != '\0')) { //checks if the first char in each array is upper and changes if needed
		char tChar = tolower(temp1.str[0]);
		temp1.str[0] = tChar;
	}
	if (isupper(temp2.str[0]) && (temp2.str[0] != '\0')) {
		char tChar2 = tolower(temp2.str[0]);
		temp2.str[0] = tChar2;
	}


	while ((temp1[i] == temp2[i]) && (temp1[i] != '\0') && (temp2[i] != '\0')) {

		if ((isupper(temp1.str[i + 1])) && (temp1.str[i + 1] != '\0')) { //checks to see if the next char is upper
			char c = tolower(temp1.str[i + 1]); //changes to lower for comparison
			temp1.str[i + 1] = c;
		}
		if ((isupper(temp2.str[i + 1])) && (temp2.str[i + 1] != '\0')) {
			char s = tolower(temp2.str[i + 1]);
			temp2.str[i + 1] = s;
		}

		++i;
	}

	if (temp2.str[i] > temp1.str[i]) {
		return true;
	}
	else {
		return false;
	}
}

// == operator overload function
bool JJString::operator==(const JJString& argStr) const {
	int i = 0;
	JJString temp1 = str; //temp strings to compare
	JJString temp2 = argStr.str;

	if ((temp1.str[0] != '\0') && (temp2.str[0] != '\0')) {

		if (isupper(temp1.str[0])) { //checks if the first char in each array is upper and changes if needed
			char tChar = tolower(temp1.str[0]);
			temp1.str[0] = tChar;
		}
		if (isupper(temp2.str[0])) {
			char tChar2 = tolower(temp2.str[0]);
			temp2.str[0] = tChar2;
		}


		while ((temp1[i] == temp2[i]) && (temp1[i] != '\0') && (temp2[i] != '\0')) {

			if ((isupper(temp1.str[i + 1])) && (temp1.str[i + 1] != '\0')) { //checks to see if the next char is upper
				char c = tolower(temp1.str[i + 1]); //changes to lower for comparison
				temp1.str[i + 1] = c;
			}
			if ((isupper(temp2.str[i + 1])) && (temp2.str[i + 1] != '\0')) {
				char s = tolower(temp2.str[i + 1]);
				temp2.str[i + 1] = s;
			}

			++i;
		}
	}

	if (temp1[i] == temp2[i]) {
		return true;
	}
	else {
		return false;
	}
}

bool JJString::operator!=(const JJString& argStr) const {
	int i = 0;
	JJString temp1 = str; //temp strings to compare
	JJString temp2 = argStr.str;

	if ((isupper(temp1.str[0])) && (temp1.str[0] != '\0')) { //checks if the first char in each array is upper and changes if needed
		char tChar = tolower(temp1.str[0]);
		temp1.str[0] = tChar;
	}
	if (isupper(temp2.str[0]) && (temp2.str[0] != '\0')) {
		char tChar2 = tolower(temp2.str[0]);
		temp2.str[0] = tChar2;
	}

	if (temp1[i] == temp2[i]) { //if they match at first
		while ((temp1[i] == temp2[i]) && (temp1[i] != '\0') && (temp2[i] != '\0')) { //while they match but before they don't

			if ((isupper(temp1.str[i + 1])) && (temp1.str[i + 1] != '\0')) { //checks to see if the next char is upper
				char c = tolower(temp1.str[i + 1]); //changes to lower for comparison
				temp1.str[i + 1] = c;
			}
			if ((isupper(temp2.str[i + 1])) && (temp2.str[i + 1] != '\0')) {
				char s = tolower(temp2.str[i + 1]);
				temp2.str[i + 1] = s;
			}

			++i;
		}
	}

	if (temp1[i] != temp2[i]) {
		return true;
	}
	else {
		return false;
	}
}

//static function to return currentCount static int
int JJString::getCurrentCount() {
	return currentCount;
}

//static function to retunr createdCount static int
int JJString::getCreatedCount() {
	return createdCount;
}

//static int definition
int JJString::currentCount = 0;
int JJString::createdCount = 0;
