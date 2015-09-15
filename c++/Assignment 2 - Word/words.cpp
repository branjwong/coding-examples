#include <iostream>
#include <fstream>
using namespace std;


string* readWords(string fname, int & arrSz);
int writeArray(string fname, float *arr, int arrSz);
int find_max_length (string *words, int& nwords);
int* find_length_arr (string *words, int& max_length, int& nwords);
float find_avg_length (int* length_arr, int& max_length, int &nwords);
int alpha(string s);
float find_avg_comp (string *words, int &nwords);
float* find_avg_comp_arr (string *words, int &max_length, int *length_arr, int &nwords);

int main (void) {
	int nwords;
	string wlfname = "wordlist";
	string outfname = "average_comps.txt";


	// This reads the words from wlfname.
	// nwords will be the number of words in the array words
	// words[i] will be the ith word
	string *words = readWords(wlfname,nwords);


	// TO DO:: You can remove/comment out this.
	// Print out the list.
	// for (int i=0; i<nwords; i++) {
	// 	cout << words[i] << endl;
	// }


	// TO DO:: You should compute these values.
	int max_length = find_max_length(words, nwords);  // maximum length of a word
	// cout << max_length << endl;
	int *length_arr = find_length_arr(words, max_length, nwords); // length_arr[i] gives the number of words with length i
	// cout << length_arr[6] << endl;
	float avg_length = find_avg_length(length_arr, max_length, nwords);
	cout << "avg_length = " << avg_length << endl;
	float avg_comp = find_avg_comp(words, nwords);
	cout << "avg_comp = " << avg_comp << endl;
	// cout << alpha(words[3]) << endl;


	float *avg_comps = find_avg_comp_arr (words, max_length, length_arr, nwords);  // avg_comps[i] should be the average number of comparisons for a word of length i.
	for (int i = 0; i <= max_length; i++){
		cout << "avg_comps[" << i << "] = " << avg_comps[i] << endl;
	}


	// TO DO:: Insert your code here.





	// Print output to a file for plotting.
	writeArray(outfname,avg_comps,max_length);


	// Clean up memory and return.
	delete[] words;
	delete[] length_arr;
	delete[] avg_comps;
	return 0;
}



// Writes the array arr to a file named fname.
// Returns 0 if successful, 1 otherwise.
int writeArray(string fname, float *arr, int arrSz) {
	ofstream out_stream;
	out_stream.open (fname.c_str());

	if (!out_stream.fail()) {
		for (int i=0; i<arrSz; i++) {
			out_stream << i << " " << arr[i] << endl;
		}
		out_stream.close();
		return 0;
	} else {
		cerr << "Error opening " << fname << endl;
		return 1;
	} 	
}



// Reads lines from a file named fname.
// Returns an array of strings, one per line of the file fname, the reference parameter arrSz contains the size
string* readWords(string fname, int & arrSz){
	string* result = NULL;
	string temp;
	arrSz = 0;
	
	// Create a file object and open the file
	ifstream in_stream;
	in_stream.open(fname.c_str());
	
	// Only process file if opening it is successful
	if (!in_stream.fail()) {
		// Find out how big the file is to make the result array
		// reads line into temp and moves to next line
		while (getline(in_stream,temp)) {
			arrSz++;
		}

		// Administrative stuff to refresh file
		in_stream.close();
		in_stream.clear();
		in_stream.open(fname.c_str());

		// Read file contents into result, now that size is known
		result = new string[arrSz]; //create results array
		for (int i=0; i < arrSz; i++){
			getline(in_stream,result[i]);
		}
		in_stream.close(); //don't forget to close file
	}else{
		cout << "... file not found ...";
	}
    return result;
}


// returns the length of the word with the largest length in words[]
int find_max_length (string *words, int& nwords){
	string largest = words[0];
	for (int i = 0; i < nwords; i++){
		if(largest.size() < words[i].size())
			largest = words[i];
	}
	return largest.size();
}


// returns an array giving the number of words with length i in words[]
int* find_length_arr (string *words, int& max_length, int& nwords){
	int *length_arr = new int[max_length + 1];
	for (int i = 0; i <= max_length; i++){
		length_arr[i] = 0;
	}
	for (int i = 0; i < nwords; i++){
		// cout << "words[" << i << "].size() = " << words[i].size() << endl;
		length_arr[words[i].size()]++;
	}
	// for (int i = 0; i <= max_length; i++){
	// 	cout << "length_arr[" << i << "] = " << length_arr[i] << endl;
	// }
	return length_arr;
}

// returns the average length of a word in words[]
float find_avg_length (int* length_arr, int& max_length, int &nwords){
	float result = 0;
	// cout << "result = " << result << endl;
	for (int i = 0; i <= max_length; i++){
		result += i*length_arr[i];
		// cout << "length_arr[" << i << "] = " << length_arr[i] << endl;
		// cout << "result = " << result << endl;
	}
	result = result/nwords;
	return result;
}

// returns the average number of comparisons made using alpha on words[]
float find_avg_comp (string *words, int &nwords){
	float result = 0;
	for (int i = 0; i < nwords; i++){
		result += alpha(words[i]);
		// cout << "alpha(words[" << i << "]) = " << alpha(words[i]) << endl;
	}
	result = result/nwords;
	return result;
}

// returns an array giving the average number of comparisons made using alpha on the words in words[] of length i
float* find_avg_comp_arr (string *words, int &max_length, int *length_arr, int &nwords){
	float *result = new float[max_length+1];
	for (int i = 0; i <= max_length; i++)
		result[i] = 0;
	for (int i = 0; i < nwords; i++)
		result[words[i].size()] += alpha(words[i]);
	for (int i = 0; i <= max_length; i++)
		result[i] = result[i]/length_arr[i];	
	return result;
}

int alpha(string s){
	int result = 0;
	int ln = s.size();
	for (int i = 0; i < ln - 1; ++i){
		if (s[i] > s[i+1]){
			result++;
			return result;
		}
		else
			result++;
	}
	return result;
}