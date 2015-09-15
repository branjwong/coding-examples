// Implement InvertedIndex methods
#include "InvertedIndex.h"
using namespace std;

bool InvertedIndex::add(string key, string value) {
	// Either find the key or find an empty bucket in the table.
	int hval = hash(key);
	int pval = hval;

	for (int iter=0; iter<tsize; iter++) {
		if (sentinels[pval] == curr_used && keys[pval]==key) {
			// Found the key, add the value to the set (it checks for duplicates).
			values[pval].insert(value);
			
			return true;
		} else if (sentinels[pval] != curr_used) {
			// The key wasn't previously inserted and we've found an empty spot.
			// Insert the (key,value) pair here.
			sentinels[pval] = curr_used;
			keys[pval] = key;
			values[pval].insert(value);
			nstored++;
			return true;
		}
		pval = probeFunction(hval,iter);
	}

	// TO DO:: Grow if trouble.

	return false;
}

// Print all the values in the index.
void InvertedIndex::printIndex() {
	for (int i=0; i < tsize; i++) {
		// If this entry is used, print the key and its set of values.
		if (sentinels[i] == curr_used) {
			cout << keys[i] << " maps to {";
			for (set<string>::iterator it = values[i].begin(); it != values[i].end(); it++) {
				cout << *it << ", ";
			}
			cout << "}" << endl;
		}
	}
}



bool InvertedIndex::lookup(string key, set<string>& value) {
	// Start search at pval, increment by probe function until found or unused spot encountered.
	int hval = hash(key);
	int pval = hval;

	for (int iter=0; iter<tsize; iter++) {
		if (keys[pval] == key && sentinels[pval] == curr_used) {
			value = values[pval];
			return true;
		} else if (sentinels[pval] == never_used) {
			return false;
		}

		pval = probeFunction(hval,iter);
	}
	return false;
}




int InvertedIndex::hash(string key) {
	return smarterHash(key);
}


int InvertedIndex::probeFunction(int val, int iter) {
	// Linear probing.
	return (val + iter) % tsize;
}


int InvertedIndex::smarterHash(string key) {
	// Return hash function value for str.
	// Use base 32 representation mod table size as hash function.
	// Compute using Horner's rule to avoid overflow.

	// Handle empty strings.
	if (key.length() == 0) {
		return 0;
	} else {
		int base = 32;
		int sum = char26(key.at(0));
		for (int i=1; i<key.length(); i++) {
			sum = (base*sum + char26(key.at(i))) % tsize;
		}
		return sum;
	}
}

int InvertedIndex::char26(char c) {
	// Return the character c as a number in 1-26.
	// Case-insensitive, returns 0 if c is outside of A-Z.
	int diffa = 0;
	if (c >= 'A' && c <= 'Z') {
		diffa = c - 'A' + 1;
	} else if (c >= 'a' && c <= 'z') {
		diffa = c - 'a' + 1;
	} else {
		diffa = 0;
	}
		
	return diffa;
}



InvertedIndex::InvertedIndex() {
	init(default_size);
}


InvertedIndex::InvertedIndex(int nkeys) {
	init(4*nkeys);
}


void InvertedIndex::init(int tsizei) {
	tsize = tsizei;
	nstored = 0;

	keys = new string[tsize];
	values = new set<string>[tsize];
	sentinels = new int[tsize];

	// Initialize all sentinels to 0.
	for (int i=0; i<tsize; i++)
		sentinels[i]=0;
}



InvertedIndex::~InvertedIndex() {
	delete[] keys;
	delete[] values;
	delete[] sentinels;
}


int InvertedIndex::numStored() {
	return nstored;
}
