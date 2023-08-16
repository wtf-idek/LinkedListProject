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


	while (cstr[end] != '\0') { //finds the end
		++end;
		if (end % 20 == 0) { //adjusts the size of the capacity as needed
			cap += 20;
		}
	}

	str = new char[cap]; //creates a new array with the size of the adjusted capacity

	for (int i = 0; i <= end; ++i) { //copies over all the chars in the array including the '\0'
		str[i] = cstr[i];
	}

	++createdCount;
	++currentCount;
}

//copy constructor
JJString::JJString(const JJString& cstr) {
	
	end = cstr.end;
	cap = ((end + 20) / 20) * 20; //makes adjustment to the cap if needed
	
	str = new char[cap]; //creates an array of cap size

	int i = 0;
	if (end > 0 && i < cap) { //if not an empty string
		for (i = 0; i <= cstr.length(); ++i) { //copies over each item in string, including '\0'
			str[i] = cstr.str[i]; 
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
	
	if (this != &cstr) { //if not pointing at itself
		delete[] str; //delete default
		str = new char[cstr.cap]; //create a new array with the cap size of the previous
		this->end = cstr.end;
		this->cap = cstr.cap;

		for (int i = 0; i <= cstr.length(); ++i) { //copies over string, including '\0'
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

	if (istrm >> inputWords) { //reads in words
		jjs.end = 0; 
		while (inputWords[jjs.end] != '\0' && jjs.end < 99) { 
			jjs.end++;
			if (jjs.end % 20 == 0) { //ups the capacity as needed
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
	jjs.str = new char[tempCap]; //creates a string array with adjusted capacity
	jjs.cap = tempCap;
	jjs.end = tempEnd;

	for (int i = 0; i <= tempEnd; ++i) { //copies everything over including '\0'
		jjs.str[i] = inputWords[i];
	}

	return istrm; 
}

//+ operator overload function
JJString JJString::operator+(const JJString& rstr) {
	
	int newEnd = this->length() + rstr.length(); //new length of the two strings
	int newCap;

	newCap = ((newEnd+20)/ 20) * 20; //finds the right capacity

	JJString newString;
	delete[] newString.str; //deletes default

	newString.str = new char[newCap]; //creates a new array with adjusted cap size
	newString.cap = newCap;
	newString.end = newEnd;

	for (int i = 0; i < this->end; ++i) { //copies first string
		newString.str[i] = this->str[i];
	}

	for (int i = this->end; i <= newEnd; ++i) { //copies second string
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


	while ((temp1[i] == temp2[i]) && (temp1[i] != '\0') && (temp2[i] != '\0')) { //while matching and not at the end of either array

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

	if (temp2.str[i] < temp1.str[i]) { //if earlier in the alphabet
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

	if (temp2.str[i] > temp1.str[i]) { //if later in the alphabet
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

	if (temp1[i] == temp2[i]) { //if the same letter
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

	if (temp1[i] != temp2[i]) { //if not the same letter
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
