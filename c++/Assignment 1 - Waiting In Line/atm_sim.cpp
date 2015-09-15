#include "ATM.h"
#include "Customer.h"
#include "ATMQueue.h"
#include "Node.h"
#include <iostream>
using namespace std;

const int VERBOSE = 0;

int getSimParameters(int &simLength, int &atmCount, int &custCount, int *&atime_list, int *&ttime_list);
void displaySimResults(int wait, int custCount);
void printATMState(int &atmCount, ATM *&atm_arr);

int main () {
	// simLength: minutes to run simulation
	// atmCount: number of ATMs
	// custCount: number of customers
    int simLength,atmCount,custCount;
	// atime_list: array of customer arrival times
	// ttime_list: array of customer transaction times
	//        customer i arrives at time atime_list[i] and performs a transaction that takes ttime_list[i] minutes
    int *atime_list, *ttime_list;
    
    // total_wait_time: total wait time for all customers in the simulation.
    int total_wait_time = 0;
    // custInQueue: checks if there are any customers still waiting
	bool custInQueue = true;
    // current_time: keeps track of the current time
    int current_time = 0;
    // currCust: a counter for the last customer to be inserted into the queue
    int currCust = 0;
    // currCustIncomplete: used to check if the customers to be queued have been queued yet
    bool currCustIncomplete = true;

    // Input code to read simulation parameters
    int param_err = getSimParameters(simLength, atmCount, custCount, atime_list, ttime_list);
    if (param_err) {
        cerr << "Error in simulation parameters." << endl;
        return -1;
    }
	
	// Initialize ATMs
	ATM *atm_arr = new ATM[atmCount];

    // Initialize Customers, and give them their proper arrival and transaction times.
    Customer *cust_arr = new Customer[custCount];
    for (int i = 0; i<custCount; i++)
    {
        cust_arr[i].set_ttime(ttime_list[i]);
        cust_arr[i].set_atime(atime_list[i]);
	}

    //checks if the simulation should be done
	while (simLength >= current_time || custInQueue)
	{

        // incCust: keeps a tab on the next customer to be inserted into the queue
        int incCust = 0;
        // lastCurrCust: keeps a tab on the last customer to be inserted into the queue
        int lastCurrCust = 0;
        for(int i = currCust; i<custCount; i++)
        {
            //gives a count for the amount of incoming customers for t = current_time
            if(atime_list[i] == current_time)
                incCust++;
        }
        lastCurrCust = currCust + incCust;
        
        if (VERBOSE)
        {            
            cout << "The Current Time is: t=" << current_time << endl;
            cout << "incCust: " << incCust;
            cout << ", currCust: " << currCust;
            cout << ", lastCurrCust: " << lastCurrCust << endl;
            cout << "Before Process:" << endl;
            printATMState(atmCount, atm_arr);  
        }
              


        //check if there are any new customers
        if (simLength > current_time && incCust > 0)
        {
            //assign customers to atm queues, starting with low queue lengths first
            for(int i = currCust; i < lastCurrCust; i++)
            {
                currCustIncomplete = true;
                //cout << i <<  "<lastCurrCust" << endl;
                for(int j = 0; j<custCount && currCustIncomplete; j++)
                {
                    //cout << j << "<custCount && currCustIncomplete" << endl;
                    for(int k = 0; k<atmCount && currCustIncomplete; k++)
                    {
                        //cout << k << "<atmCount && currCustIncomplete" << endl;
                        if(atm_arr[k].getQueueLength() == j)
                        {
                            //cout << "cust[" << i << "] got inserted at ATM[" << k << "]"  << endl;
                            atm_arr[k].insertCust(&cust_arr[i]);
                            currCustIncomplete = false;
                        }
                    }
                }
                // cout << i << endl;
                // cout << lastCurrCust << endl;
            }
            currCust = lastCurrCust;
        }
        

        //process customers
        for(int i = 0; i<atmCount; i++)
        {
            //process each atm
            //cout << "process occuring..";
            atm_arr[i].processCust(current_time);
        }

        //check if there are any more customers left waiting in line
        custInQueue = false;
        for(int i = 0; i<atmCount; i++)
        {
            if(atm_arr[i].getQueueLength() > 0)
            {
                custInQueue = true;
            }
        }
        
        if (VERBOSE)
        {
            cout << "After Process: " << endl;
            printATMState(atmCount, atm_arr);
            cout << endl << "----------------------" << endl << endl;
        }

        //increment current_time
        current_time++;
	}

    for (int i = 0; i<atmCount; i++)
    {
        //sum up total wait time for all ATMS (instead of incrementing every single time) at end
        total_wait_time += atm_arr[i].get_timeSpent();
    }

    // Display statistics on the simulation.
    displaySimResults(total_wait_time, custCount);
    // Return total_wait_time, will be used by test script.

    delete[] atm_arr;
    delete[] cust_arr;

    return total_wait_time;
}




// Read the simulation parameters from standard input (cin).
// Parameters:



//
// All parameters are pass-by-reference (note & character).    This means assignments in this function will affect value from calling function
// 
// Return value:
// returns 0 if successful read of input
// non-zero values used to denote failure
//     1: simulation time < 1
//     2: number of ATMs < 1
//     3: number of customers < 1
//     4: a customer's transaction time < 1
//     5: customer list is not sorted by arrival time
//     6: customer arrival time later than simulation end time
int getSimParameters(int &simLength, int &atmCount, int &custCount, int *&atime_list, int *&ttime_list) {
    // Code to read simulation parameters.
    cout << "Run an ATM simulation" << endl;

    cout << "Enter the number of minutes" << endl;
    cin >> simLength;
    // Check input validity.
    if (simLength < 1) {
        cerr << "Simulation for invalid length of time." << endl;
        return 1;
    }

    
    cout << "Enter the number of ATMs" << endl;
    cin >> atmCount;
    // Check input validity.
    if (atmCount < 1) {
        cerr << "Simulation for invalid number of ATMs." << endl;
        return 2;
    }


    // Read customer list
    cout << "Enter the number of customers" << endl;
    cin >> custCount;
    if (custCount < 1) {
        cerr << "Simulation for invalid number of customers." << endl;
        return 3;
    }
    // Allocate memory for customer list.
    atime_list = new int [custCount];
    ttime_list = new int [custCount];

    // Read custCount customers
    int atime = -1;
    int prevatime = -1;
    int ttime = 0;
    for (int i=0; i<custCount; i++) {
        cout << "Enter customer arrival and transaction time." << endl;
        cin >> atime;
        cin >> ttime;

        // Check input validity.
        if (ttime < 1) {
            cerr << "Invalid transaction time." << endl;
            return 4;
        }
        if (atime < prevatime) {
            cerr << "Arrival times not sorted." << endl;
            return 5;
        }
        if (atime >= simLength) {
            cerr << "Arrival time later than simulation end time." << endl;
            return 6;
        }
        prevatime = atime;

        atime_list[i] = atime;
        ttime_list[i] = ttime;
    }

    // All went well, return 0.
    return 0;
}


// Display statistics on the simulation.
// wait: Total wait time of all customers in simulation.
// custCount: total number of customers in simulation.
void displaySimResults(int wait, int custCount) {
    cout << "Simulation results" << endl;
    cout << "Number of customers: " << custCount << endl;
    cout << "Total wait time: " << wait << endl;
    cout << "Average wait time: " << ((double) wait)/((double) custCount) << endl;
}

void printATMState(int &atmCount, ATM *&atm_arr) {
    for (int i = 0; i<atmCount; i++)
    {
        cout << "ATM[" << i << "] ";
        atm_arr[i].printState();
    }
}