/*
  index_directory.cpp

  * Load the contents of a directory into a hashtable, allow searches.
 */

#include <iostream>
// dirent.h is a library for reading directory entries.
// It defines DIR, the struct dirent, and other functions/constants used below.
#include <dirent.h>  
#include <vector>
#include <fstream>
#include <string.h>
#include "InvertedIndex.h"

using namespace std;

#define MAX_STRING_LEN 256
#define INDEX_SIZE 100000


void processDirectory (const char * dname, vector<string> valid_extensions, InvertedIndex& inverted_index, int& nfiles, int& ndirs);
bool validExtension (char *extension, vector<string> valid_extensions);
void processFile(const char *fname, InvertedIndex& inverted_index);



// This program processes all files in all subdirectories rooted at a directory.
// It builds an inverted index from these files.
// It then answers queries.
int main (int argc, char* argv[]) {

	// Parse command-line arguments.
	if (argc < 2) {
		// Note that the program name is the first argument, so argc==1 if there are no additional arguments.
		cerr << "Expected one argument." << endl;
		cerr << "  Usage: " << argv[0] << " input_dirname [list of .extensions]\n    e.g. " << argv[0] << " .  .cpp .h" << endl;
		cerr << "indexes all files if no extensions are provided." << endl;
		return 1;
	} else {
		vector<string> valid_extensions;
		for (int i=2; i<argc; i++) {
			string ext(argv[i]);
			valid_extensions.push_back(ext);
		}


		// Build an inverted index.
		InvertedIndex inverted_index(INDEX_SIZE);

		// Numbers of files and directories.
		int nfiles = 0;
		int ndirs = 0;

		// Open the directory name specified for input.
		processDirectory(argv[1], valid_extensions, inverted_index, nfiles, ndirs);

		// inverted_index.printIndex();
		cout << "Indexed " << argv[1] << endl;
		cout << "  found " << ndirs << " subdirectories and " << nfiles << " files" << endl;
		cout << "  built index with " << inverted_index.numStored() << " keys" << endl;


		// Allow a user to query the index.
		string terminate_str = "q";
		string input;
		set<string> results;
		while (1) {
			cout << "Enter a word to search for, " << terminate_str << " to terminate" << endl;
			cin >> input;
			
			// Clear results.
			results.clear();
			
			if (input == terminate_str) {
				break;
			} else {
				inverted_index.lookup(input,results);
				cout << "Searched for " << input << endl;
				cout << " found " << results.size() << " occurrences: " << endl;
				if (results.size() > 0) {
					cout << "{";
					for (set<string>::iterator it = results.begin(); it != results.end(); it++) {
						cout << *it << ", ";
					}
					cout << "}" << endl;
				}
			}
		}
		

		return 0;
	}
}




// Recursively process a directory.
// Find all files in all subdirectories that have an extension in valid_extensions.
// Runs processFile on each such file.
void processDirectory (const char *dname, vector<string> valid_extensions, InvertedIndex &inverted_index, int& nfiles, int& ndirs) {
	DIR *dir = opendir(dname);

	if (dir != 0) {
		// Iterate over each entry in the directory.
		for (struct dirent *ent = readdir(dir); ent != 0; ent=readdir(dir)) {
			// Check if it is a directory
			if (ent->d_type == DT_DIR) {
				// Make sure not the current (".") nor parent ("..") directory.
				if ((strcmp(ent->d_name,".") != 0) && (strcmp(ent->d_name,"..") != 0)) {
					// If so, do a recursive call to process that directory.
					string fulldname(dname);
					fulldname += "/";
					fulldname += ent->d_name;
					cout << "Found directory: " << fulldname << endl;
					ndirs++;
					
					processDirectory(fulldname.c_str(), valid_extensions, inverted_index, nfiles, ndirs);
				}
			} else {
				// Check to see if this file ends in a valid extension.
				// strrchr returns last occurrence of character, null if not found.
				char *extension = strrchr(ent->d_name,'.');
				// Compare to the set of valid extensions.
				if (validExtension(extension,valid_extensions)) {
					string fulldname(dname);
					fulldname += "/";
					fulldname += ent->d_name;
					cout << "Found a file: " << fulldname << endl;
					nfiles++;
					processFile(fulldname.c_str(), inverted_index);
				}
			}
		}

	}
}


// Checks whether extension is contained in the vector of valid extensions.
// Returns true if so, false if not.
// If valid_extensions is empty, everything is valid.
bool validExtension (char *extension, vector<string> valid_extensions) {
	if (valid_extensions.size()==0) {
		return true;
	} else {
		if (extension != 0) {
			for (int i=0; i < (int) valid_extensions.size(); i++) {
				// Compare extension to this valid extension.
				if (strcmp(extension, valid_extensions[i].c_str()) == 0) {
					return true;
				}
			}
		}
		return false;
	}
}


// Read every word in this file.
// Insert a pair into the hash table (word,fname)
void processFile (const char *fname, InvertedIndex& inverted_index) {

	ifstream inputfile;  // ifstream for reading from input file.
	inputfile.open (fname);
	string fnames(fname); // file name as a string object, not as a char * (c-style string, which is an array of characters with \0 at the end).

	// Tokenize the input.
	// Read one character at a time.
	// If the character is not in a-z or A-Z, terminate current string.
	char c;
	char curr_str[MAX_STRING_LEN];
	int str_i = 0;  // Index into curr_str.
	bool flush_it = false;  // Whether we have a complete string to flush.
	
	while (inputfile.good()) {
		// Read one character, convert it to lowercase.
		inputfile.get(c);
		c = tolower(c);

		if (c >= 'a' && c <= 'z') {
			// c is a letter.
			curr_str[str_i] = c;
			str_i++;
			
			// Check over-length string.
			if (str_i >= MAX_STRING_LEN) {
				flush_it = true;
			}
		} else {
			// c is not a letter.
			// Create a new string if curr_str is non-empty.
			if (str_i>0) {
				flush_it = true;
			}
		}

		if (flush_it) {
			// Create the new string from curr_str.
			string the_str(curr_str,str_i);
			// cout << the_str << endl;


			// Insert the string-file_name tuple into the inverted index.
			inverted_index.add(the_str,fnames);

			// cout << "Add " << the_str << "," << fname << endl;
			

			// Reset state variables.
			str_i = 0;
			flush_it = false;
		}
	}
}
