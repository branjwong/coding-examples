/*
 * ATM.h
 *
 */


#ifndef ATM_H_
#define ATM_H_

#include <iostream>
#include "Customer.h"
#include "ATMQueue.h"

using namespace std;

class ATM 
{
public:
	ATM();
	~ATM();
	//Insert customer (if the ATM is not in use the customer's transaction time should be assigned to the ATM's transaction time, otherwise the customer should be inserted in the ATM's queue).
	void insertCust(Customer *c);
	//Process customer (which will call the ATMQueue's remove method, and also set the ATM's remaining transaction time), this method updates the ATM's variables for the passage of time and is further described below.
	void processCust(int current_time);
	//Return the length of the ATM's queue
	int getQueueLength();
	//Return the remaining transaction time for the current customer
	int get_timeRem();
	void set_timeRem();
	int get_timeSpent();
	bool isFree();
	int *get_head();
	//prints the state of the ATM
	void printState();
	
private:
	//Remaining transaction time for the current customer
	int timeRem;
	//Availability (a boolean value, or a method that returns a boolean value based on the remaining transaction time, i.e. true if it is zero)
	bool avail;
	//Time spent by customers waiting at the ATM, updated as each customer starts to use the ATM (leaves its queue) 
	int timeSpent;
	ATMQueue *qp;
};

#endif /* ATM_H_ */
