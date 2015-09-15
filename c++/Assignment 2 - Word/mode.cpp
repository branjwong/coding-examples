#include <iostream>
#include <fstream>
using namespace std;



// Find the mode of an array.
//
// Parameters:
//  arr is an integer array with n elements
// Return value:
//  return the mode
//
long mode (long *arr, int n) {
	// TO DO:: Fill in this function.
	
	// uses 
	int *counter = new int[n]; // array corresponding to the count of the number
	long *value = new long[n]; // array corresponding to the number it's counting
	


	int index = 0; // keeps track of the array index for the next new value in arr[] to be counted
	bool match; // keeps track if the current value in question has a match in value[]
	
	int result_index;
	int result = -1;

	for (int i = 0; i < n; i++){
		counter[i] = 0;
		value[i] = 0;
	}

	for (int i = 0; i < n; i++){
		match = false;
		//if long[i] has a match with value[] (from 0 to index), increment the counter corresponding to that value
		for (int j = 0; j < index && match == false; j++){
			if (arr[i] == value[j]){
				counter[j]++;
				match = true;
			}
		}
		// if long[i] has no matches with value[] (from 0 to index), set value[index] = long[i], and increment the counter corresponding to that value
		if (!match){
			value[index] = arr[i];
			counter[index]++;
			index++;
		}
	}
	// return the value with the highest count
	result_index = 0;
	// cout << "The beginning result_index = " << result_index << endl;
	for (int i = 1; i < index; i++){
		// if (counter[i] > counter[result_index])
		if (counter[result_index] <= counter[i]){
			result_index = i;
			// cout << "result_index = " << result_index << endl;
		}		
	}

	// cout << "The ending result_index = " << result_index << " which corresponds to value = " << value[result_index] << endl;
	
	// for (int i = 0; i < index; i++){
	// 	cout << "value[" << i << "] = " << value[i] << ", counter[" << i << "] = " << counter[i] << endl;
	// }

	result = value[result_index];
	delete[] counter;
	delete[] value;
	return result;
}







// Input is the number of elements, followed by that many integers.
// Writes mode of elements to file specified as first command-line argument.
int main (int argc,  char* argv[]) {

	// ofstream for writing result.
	ofstream outputfile;

	// Parse command-line arguments.
	if (argc != 2) {
		// Note that the program name is the first argument, so argc==1 if there are no additional arguments.
		cerr << "Expected one argument." << endl;
		cerr << "  Usage: " << argv[0] << " output_filename" << endl;
		return 1;
	} else {
		// Open the filename specified for input.
		outputfile.open (argv[1]);
	}


	// Read a set of elements into an array (as in lab 1).
	int n;
	long *arr;

	// Get the number of elements
	cout << "Enter the number of elements:" << endl;
	cin >> n;

	// Create array in dynamic memory.
	arr = new long[n];

	for (int i=0; i<n; i++) {
		cout << "Enter a number:" << endl;
		cin >> arr[i];
	}

	long m = mode(arr,n);

	cout << "The mode is " << m << endl;

	outputfile << m << endl;
	outputfile.close();

	// Free up memory.  Note use of delete [], since this is an array.
	delete [] arr;

	return 0;
}
