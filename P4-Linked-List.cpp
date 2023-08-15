//main code for project and source for revealing all my problems
//things like using namespace std are because that's what my teacher has us do
//I see many comments about not liking this online but for school, I'm going to listen to the teacher

//#include "pch.h"   // may need this	
#include <iostream>
#include "JJStringList.h"
#include "DblLinkedList.h"
#include <fstream>

using namespace std;

void readFromFile(fstream& file, JJString& str, DblLinkedList& list);
void changer(DblLinkedList list);

int main() {
	DblLinkedList list1;
	DblLinkedList list2;
	DblLinkedList modList1;
	DblLinkedList modList2;

	fstream fileIn;
	JJString readFile;

	fileIn.open("infile1.txt");
	readFromFile(fileIn, readFile, list1);
	fileIn.close();

	fileIn.open("infile2.txt");
	readFromFile(fileIn, readFile, list2);
	fileIn.close();

	cout << "There are " << list1.getCount() << " words on List 1." << endl;
	cout << "There are " << list2.getCount() << " words on list 2." << endl;
	cout << "There are " << modList1.getCount() << " words on Modified List 1." << endl;
	cout << "There are " << modList2.getCount() << " words on Modified list 2." << endl;

	modList1 = list1;
	modList2 = list2;

	cout << endl;
	cout << "There are " << list1.getCount() << " words on List 1." << endl;
	cout << "There are " << list2.getCount() << " words on list 2." << endl;
	cout << "There are " << modList1.getCount() << " words on Modified List 1." << endl;
	cout << "There are " << modList2.getCount() << " words on Modified list 2." << endl;

	list1.resetIterator();
	list2.resetIterator();
	modList1.resetIterator();
	modList2.resetIterator();


	// Below here is where I start seeing problems. 
	//I'm trying to check each word in one list against the other 
	//and remove it from the mod list if it's there
	
	//JJString check1 = modList1.next();
	//JJString check2 = list2.next();

	//this throws an error in my JJString.cpp at the == overload or the != for the isupper
	//I think the problem is actually in the remove function of DbleLinkedList.cpp
	//I am also aware that it doesn't go through and remove every isntance of the word, I'm working on that
	//for (int i = 0; i <= list2.getCount(); ++i) {
	//	for (int j = 0; j <= modList1.getCount(); ++j) {
	//		if (check2 == check1) {
	//			modList1.remove(check2);
	//		}
	//		check1 = modList1.next();
	//	}
	//	check2 = list2.next();
	//	modList1.resetIterator();
	//}

	//cout << endl;
	//cout << "There are " << list1.getCount() << " words on List 1." << endl;
	//cout << "There are " << list2.getCount() << " words on list 2." << endl;
	//cout << "There are " << modList1.getCount() << " words on Modified List 1." << endl;
	//cout << "There are " << modList2.getCount() << " words on Modified list 2." << endl;

	//list1.resetIterator();
	//list2.resetIterator();
	//modList1.resetIterator();
	//modList2.resetIterator();

	//check1 = modList2.next();
	//check2 = list1.next();

	//I also tried this way. It actually seems to run but very slowly. I think there's a better way.
	//it also doesn't go through eact item
	//while (modList2.hasMore()) {
	//	while (list1.hasMore()) {
	//		modList2.remove(check2);
	//		check2 = list1.next();
	//	}
	//	check1 = modList2.next();
	//	list1.resetIterator();
	//}

	//cout << endl;
	//cout << "There are " << list1.getCount() << " words on List 1." << endl;
	//cout << "There are " << list2.getCount() << " words on list 2." << endl;
	//cout << "There are " << modList1.getCount() << " words on Modified List 1." << endl;
	//cout << "There are " << modList2.getCount() << " words on Modified list 2." << endl;


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

void changer(DblLinkedList list) {
	JJString zap = "ZAP";
	JJString zip = "ZIP";
	list.insert(zip);
	list.insert(zap);
}
