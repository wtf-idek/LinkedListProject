//main code for project and source for revealing all my problems

	
#include <iostream>
#include "JJStringList.h"
#include "DblLinkedList.h"
#include <fstream>
#include <cctype>

using namespace std;

void readFromFile(fstream& file, JJString& str, DblLinkedList& list); //reads from the file and puts into list
void changer(DblLinkedList list); //changes list while testing copy constructor
void stringRemover(DblLinkedList& editList, DblLinkedList compList); //removes like strings from lists

int main() {
	DblLinkedList list1; //lists that will have the strings read into
	DblLinkedList list2;
	DblLinkedList modList1; //lists that will be edited
	DblLinkedList modList2;

	fstream fileIn;
	JJString readFile;

	fileIn.open("infile1.txt"); //creating list 1
	readFromFile(fileIn, readFile, list1);
	fileIn.close();

	fileIn.open("infile2.txt"); //creating list 2
	readFromFile(fileIn, readFile, list2);
	fileIn.close();

	cout << endl;
	cout << "There are " << list1.getCount() << " words on List 1." << endl;
	cout << "There are " << list2.getCount() << " words on list 2." << endl;
	cout << "There are " << modList1.getCount() << " words on Modified List 1." << endl;
	cout << "There are " << modList2.getCount() << " words on Modified list 2." << endl;

	modList1 = list1; //copying list one to be modified
	modList2 = list2; //copying list two to be modified

	cout << endl;
	cout << "There are " << list1.getCount() << " words on List 1." << endl;
	cout << "There are " << list2.getCount() << " words on list 2." << endl;
	cout << "There are " << modList1.getCount() << " words on Modified List 1 after copying List 1." << endl;
	cout << "There are " << modList2.getCount() << " words on Modified list 2 after copying List 2." << endl;

	/*stringRemover(modList1, list2); //breaks my code, gives a "throw_bad_alloc"
	stringRemover(modList2, list1); //which I think means I have a memory leak that I can't find
	                               //I'm pretty sure it's in the JJString class, the bane of my existence.*/

	cout << endl;
	cout << "There are " << list1.getCount() << " words on List 1." << endl;
	cout << "There are " << list2.getCount() << " words on list 2." << endl;
	cout << "There are " << modList1.getCount() << " words on Modified List 1 after removing List 2 strings." << endl;
	cout << "There are " << modList2.getCount() << " words on Modified List 1 after removing List 2 strings." << endl;

	ofstream fout; 
	fout.open("outfile1.txt"); //outputing modified list 1 into a file
	fout << modList1;
	fout.close();

	fout.open("outfile2.txt"); //ouputing modified list 2 into a file
	fout << modList2;
	fout.close();

	changer(modList1); //function to use copy constructor

	system("pause");
	return 0;
}

void readFromFile(fstream& file, JJString& str, DblLinkedList& list) {
	if (file) {
		while (!file.eof()) {
			file >> str;
			list.push_back(str);
		}
	}

}

void stringRemover(DblLinkedList& editList, DblLinkedList compList) {
	editList.resetIterator();
	compList.resetIterator();

	JJString check1 = editList.next();
	JJString check2 = compList.next();

	while (editList.hasMore()) {

		for (int i = 0; i < compList.getCount(); ++i) {
			
			editList.remove(check2); //removes string if it's on the list

			check2 = compList.next(); //gets next string to check
		}

		compList.resetIterator(); //resets first string to start over again

		check1 = editList.next();
		check2 = compList.next();
	}
}

void changer(DblLinkedList list) { 
	JJString zap = "ZAP";
	JJString zip = "ZIP";
	list.insert(zip);
	list.insert(zap);

	cout << endl << "The list is now: " << list.getCount() << " words long in the changer function." << endl;
}
