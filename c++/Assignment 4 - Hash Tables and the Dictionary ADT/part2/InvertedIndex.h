#pragma once

#include <iostream>
#include <string>
#include <set>
using namespace std;

// An inverted index class for mapping strings to sets of strings.
// Underlying data structure is a hash table.

class InvertedIndex {
 public:
	// Lookup a key in index.  Copies values to values if found and returns true, returns false if key not in index
	bool lookup(string key, set<string>& value);

	// Add a <key,value> pair to the index.  If the key has not previously been stored, create an entry.  Add the value to it.
	bool add(string key, string value);

	// Create a default sized index.
	InvertedIndex();

	// Create an index that can store nkeys keys (allocates 4x space).
	InvertedIndex(int nkeys);
	~InvertedIndex();

	// Print the contents of the index.
	void printIndex();

	// Returns the number of keys stored.
	int numStored();

 private:
	int tsize;  // size of hash table arrays
	int nstored;  // number of keys stored in table
	string *keys;
	set<string> *values;
	int *sentinels; // 0 if never used, 1 if currently used, -1 if previously used.
	static const int curr_used = 1;
	static const int never_used = 0;
	static const int prev_used = -1;

	static const int default_size = 10000;  // Default size of hash table.


	// Probing function, returns location to check on iteration iter starting from initial value val.
	int probeFunction(int val, int iter);  
	void init(int tsizei);

	// Hash functions.
	int hash(string key);
	int smarterHash(string key);
	int char26(char);

};


