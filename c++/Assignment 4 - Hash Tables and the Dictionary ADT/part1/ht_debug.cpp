//============================================================================
// Name        : ht_debug.cpp
//============================================================================

// A driver program you can use to debug your hashtable and other algorithms.

#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

string int2letter(int i);

int main() {
	ostream *outputp = &cout;
	ofstream outputfile;
	ostream& output = *outputp;
	HashTable ht(25);
	string key = "a";
	int val = 0;
	for (int i=0; i<50; i++) {
		ht.insert(int2letter(i),i);
	}

	for (int j=0; j<6; j++) {
		// Remove 25
		for (int i=25*j; i < 25*j + 25; i++) {
			ht.remove(int2letter(i),i);
		}
		// Add another 25
		for (int i=25*(j+1) ; i < 25*(j+2); i++) {
			ht.insert(int2letter(i),i);
		}
	}



	key = "a";
	ht.insert(key,400);
	ht.lookup(key,val);

	output << val << endl;
	output << "Number of pairs stored in the table: " << ht.numStored() << endl;




	// HashTable ht(10);
	// int value;

	// ht.insert("a", 1);
	// ht.insert("b", 2);
	// ht.insert("c", 3);
	// ht.insert("abc", 4);
	// ht.remove("b", 2);
	// ht.modify("c", 9001);
	// ht.modify("b", 9001);

	// ht.printTable();

	// cout << ht.lookup("a", value) << endl;
	// cout << value << endl;
	// cout << ht.hashTest("a") << endl;
	// cout << ht.hashTest("b") << endl;
	// cout << ht.hashTest("c") << endl;

	// cout << ht.hashTest("abc") << endl;

}

string int2letter(int i) {
	char the_char = (char) (65 + i % 26);

	// Put it in a string to return.
	string rtn_string(1,the_char);
	return rtn_string;
}
