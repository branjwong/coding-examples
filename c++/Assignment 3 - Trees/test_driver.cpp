//============================================================================
// Name        : test_driver.cpp
//============================================================================

#include "Customer.h"
#include "BSTree.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

#define DEBUG 0
#define DEBUG2 0

void readCustomersFile(string fname, BSTree &);
void printCustVec(vector<Customer> vc);


// This program takes command-line arguments
// The single argument is the test case to run, an integer.
int main(int argc, char *argv[]) {

	// Parse command-line arguments.
	// Turn the argument into an integer.
	int tcase=0;
	if (argc > 1) {
		tcase = atoi(argv[1]);
	} else {
		// Print error message, need a test case number.
		cerr << "Error: no arguments" << endl;
		cerr << "  Usage:" << endl;
		cerr << "    test_driver case_no" << endl;

		return 1;
	}

	// cout << "Running case " << tcase << endl;
		
 


	BSTree bst;
	vector<Customer> vc;


	// Select test cases.
	switch (tcase) {
	case 1: {
		// Case 1, test printing customer.
		Customer c("Mori",'G',1);
		cout << c << endl;
		break;
	} case 2: 
		// Case 2, insert one customer, print out tree.
		// if (DEBUG) cout << "test 1" << endl;
		bst.insert("Mori",'G',1);
		// if (DEBUG) cout << "test 2" << endl;
		if (DEBUG) bst.treePrint();
		bst.inOrderPrint();
		break;
	case 3: 
		// Case 3, insert two customers, print out tree.
		if (DEBUG){
			Customer B("Mori",'B',1);
			Customer C("Mori",'C',1);
			cout << (B < C) << endl; 
		}
		bst.insert("Mori",'G',1);
		bst.insert("Mori",'A',1);
		bst.inOrderPrint();
		break;
	case 4: 
		// Case 4, insert many customers, delete leaf, print out tree.
		readCustomersFile("small_names.txt", bst);
		if (DEBUG) bst.treePrint();
		bst.remove("Harrell",'O');
		if (DEBUG) bst.treePrint();
		bst.inOrderPrint();
		break;
	case 5: 
		// Case 5, insert many customers, delete root, print out tree.
		readCustomersFile("small_names.txt", bst);
		if (DEBUG2) cout << "wickedsick" << endl;
		bst.remove("Alexander",'G');
		bst.inOrderPrint();
		break;
	case 6: 
		// Case 6, check search, leaf
		readCustomersFile("small_names.txt", bst);
		cout << bst.search("Franco",'E') << endl;
		break;
	case 7: 
		// Case 7, check range, sub-tree
		readCustomersFile("small_names.txt", bst);
		vc = bst.rangeSearch("Berger",'U',"Harris",'Z');
		printCustVec(vc);
		break;
	case 8: 
		// Case 7, check range, sub-tree
		readCustomersFile("small_names.txt", bst);
		bst.treePrint();
		bst.remove("Garrison",'A');
		bst.treePrint();



		// bst.remove("Gray",'A');
		// bst.remove("Adams",'C');

		// bst.treePrint();
		// // bst.remove("Adams",'P');
		// // bst.remove("Evans",'J');
		// // // bst.remove("Hill",'O');
		// // // bst.remove("Hill",'B');
		// // // bst.remove("Hill",'D');
		// // bst.remove("Hill",'F');
		// bst.remove("Garcia",'R');
		// cout << endl << endl;
		// bst.treePrint();
		break;
	default:
		cerr << "Invalid test case number" << endl;
		return 2;
	}
	

	return 0;
}



void readCustomersFile(string fname, BSTree& bst) {
	// Read customer data from a file.
	// Create a file object and open the file
	ifstream inStream;
	inStream.open(fname.c_str());

	// Temporary variables for reading customers.
	string lname;
	char finit;
	int balance;

	// Only process file if opening it is successful
	if(!inStream.fail()){
		// Insert words in the vector
		while(!inStream.eof()){
			inStream >> lname >> finit >> balance; // Read customer.
			bst.insert(lname,finit,balance);
		}

		inStream.close(); //don't forget to close file
	}else{
		cout << "file not found ...";
	}
}


void printCustVec(vector<Customer> vc) {
	// Iterate over vc to print its contents.
	cout << "Customers in range:" << endl;
	for (int i=0; i < (int) vc.size(); i++) {
		cout << " " << vc[i] << endl;
	}
}
