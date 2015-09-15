// Implement HashTable methods.
#include "HashTable.h"
using namespace std;

bool HashTable::insert(string key, int value) {
	// Try to insert key,value pair at pval, increment by probe function.
	int hval = hash(key);
	int pval = hval;

	for (int iter=0; iter<tsize; iter++) {
		if (sentinels[pval] != curr_used) {
			// Found an empty spot, insert the (key,value) pair here.
			sentinels[pval] = curr_used;
			keys[pval] = key;
			values[pval] = value;
			nstored++;
			return true;
		}
		pval = probeFunction(hval,iter);
	}
	return false;
}


bool HashTable::remove(string key, int value) {
	// TO DO:: Write this.
	
	int hval = hash(key);
	int pval = hval;
	// Search for key using linear probing.
	for (int i=0; i<tsize; i++){
		if (sentinels[pval] == 0){
		// if sentinels[pval] == 0, key is not found
		// if key is not found, return false.
			return false;
		}
		else if (keys[pval] == key && values[pval] == value && sentinels[pval] == 1){
		// if keys[pval] == key, key is found, values[pval] == values, value matches
		// if key is found and its value matches, set its sentinal to prev_used, return true
			sentinels[pval] = prev_used;
			nstored--;
			return true;
		}
		else {
		// incr pval and test the next spot
			pval++;
		}
	}	

	// if the whole table is circled, return false
	return false;
}


bool HashTable::lookup(string key, int& value) {
	// TO DO:: Write this.
	
	int hval = hash(key);
	int pval = hval;
	// Search for key using linear probing.
	for (int i=0; i<tsize; i++){
		if (sentinels[pval] == 0){
		// if sentinels[pval] == 0, key is not found
		// if key is not found, (set &value = -1?,) return false
			value = 0;
			return false;
		}
		else if (keys[pval] == key && sentinels[pval] == 1){
		// if keys[pval] == key, key is found
		// if key is found, set &value and return true
			value = values[pval];
			return true;
		}		 
		else {
		// incr pval and test the next spot
			pval++;
		}
	}	
	// if the whole table is circled, return false
	return false;
}


bool HashTable::modify(string key, int value) {
	// TO DO:: Write this.
	
	// Search for key using linear probing.
	
	
	
	int hval = hash(key);
	int pval = hval;
	// Search for key using linear probing.
	for (int i=0; i<tsize; i++){
		if (sentinels[pval] == 0){
		// if sentinels[pval] == 0, key is not found
		// if key is not found, return false
			return false;
		}
		else if (keys[pval] == key && sentinels[pval] == 1){
		// if keys[pval] == key, key is found
		// if key is found, change its value, return true
			values[pval] = value;
			return true;
		}
		else {
		// incr pval and test the next spot
			pval++;
		}
	}	
	// if the whole table is circled, return false	
	return false;
}


void HashTable::getKeys(string*& all_keys, int& nkeys) {
	// Allocate an array to hold all the keys in the table.
	all_keys = new string[nstored];
	nkeys = nstored;


	// Walk the table's array.
	int key_i=0;
	for (int i=0; i<tsize; i++) {
		if (sentinels[i]==curr_used) {
			// Debug check: there shouldn't be more sentinels at curr_used than nstored thinks.
			if (key_i > nkeys) {
				cerr << "Error: more keys in table than nstored reports." << endl;
			}

			all_keys[key_i] = keys[i];
			key_i++;
		}
	}
}

int HashTable::numStored() {
	return nstored;
}


int HashTable::hash(string key) {
	return smarterHash(key);
}


int HashTable::probeFunction(int val, int iter) {
	// Linear probing.
	return (val + iter) % tsize;
}


int HashTable::sillyHash(string key) {
	return tsize/2;
}

int HashTable::smarterHash(string key) {
	// TO DO:: Write this.

	// convert string to lowercase
	// convert key into an int value from 0 - tsize
	// value = str[0]*26^(n-1) + … + str[n-2]*26^(1) + str[n-1]*26^(0) 
	// value = (…(str[0]*32 + str[1]) * 32 + str[2]) * …) * 32 + str[n-1]

	// value%tsize = (…(str[0]*32 + str[1])%tsize * 32 + str[2])%tsize * …)%tsize * 32 + str[n-1]

	int result = 0;
	for (int i = 0; i < key.length(); i++){
		result = (result * 32 + tolower(key[i]))%tsize;
	}

	return result;

	// return 0;
}


HashTable::HashTable() {
	init(default_size);
}


HashTable::HashTable(int nkeys) {
	init(4*nkeys);
}


void HashTable::init(int tsizei) {
	tsize = tsizei;
	nstored = 0;

	keys = new string[tsize];
	values = new int[tsize];
	sentinels = new int[tsize];

	// Initialize all sentinels to 0.
	for (int i=0; i<tsize; i++)
		sentinels[i]=0;
}



HashTable::~HashTable() {
	delete[] keys;
	delete[] values;
	delete[] sentinels;
}


void HashTable::printTable() {
	// Print the current state of the hashtable.
	// Note, prints actual data structure contents, entry might not be "in" the table if sentinel not curr_used.
	// left, setw() are part of <iomanip>

	// Find longest string.
	const int indw = 5;
	int long_string = 3; // Length of "Key", nice magic number.
	const int intw = 10;
	const int sentw = 8;
	for (int i=0; i<tsize; i++) {
		if (keys[i].length() > long_string)
			long_string = keys[i].length();
	}

	// Print title
	cout << setw(indw) << left << "Index" << " | " << setw(long_string) << left << "Key" << " | " << setw(intw) << "Value" << " | " << "Sentinel" << endl;

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

	// Print each table row.
	for (int i=0; i<tsize; i++) {
		cout << setw(indw) << left << i << " | " << setw(long_string) << left << keys[i] << " | " << setw(intw) << values[i] << " | " << sentinels[i] << endl;
	}

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

}

int HashTable::hashTest(string key){
	return hash(key);

}
