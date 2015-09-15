/*
 * Customer.h
 *
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer 
{
public:
	Customer();
	Customer(int atime_para, int ttime_para);
	~Customer();
	void set_atime(int atime_para);
	void set_ttime(int ttime_para);
	int get_atime();
	int get_ttime();
	
private:
	
	//The time (in minutes since the start of the simulation) that the customer arrives - this is necessary to determine how long the customer has been waiting when he/she leaves the queue
	int atime;
	//Customer transaction time (determined when the customer arrives)
	int ttime;
	
};

#endif /* CUSTOMER_H_ */
