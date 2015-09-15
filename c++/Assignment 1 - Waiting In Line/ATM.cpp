/*
 * ATM.cpp
 *
 */

#include "ATM.h"


ATM::ATM()
{
	timeRem = 0;
	avail = true;
	timeSpent = 0;
	qp = new ATMQueue();
}

ATM::~ATM()
{
	delete qp;
	qp = 0;
}

void ATM::insertCust(Customer *c)
{
	qp->add(c);
	if(getQueueLength() == 1)
	{
		set_timeRem();
	}		
}

void ATM::processCust(int current_time)
{

	if(avail == false)	
	{
		//decrement transaction time of its current customer by 1
		timeRem--;
		//cout << "decrement success" << endl;
	}
	//cout << "do i get here?" << endl;

	if(timeRem > 0)
		avail = false;

	// if (current customer is finished)
	if(timeRem == 0 && avail == false)
	{
		//remove the customer at the front of the queue
		qp->rem();			
		if(getQueueLength() > 0)
		{
			//set the ATM's remaining transaction time to that customer's transaction time
			set_timeRem();
			//increase the ATM's total wait time by the time that the customer waited (current time - arrival time)
			timeSpent += current_time - qp->get_atime();
		}
		else
		{
			avail = true;
		}
	}
	// }
}

int ATM::getQueueLength()
{
	return qp->get_length();
}

int ATM::get_timeRem()
{
	return timeRem;
}

void ATM::set_timeRem()
{
	timeRem = qp->get_ttime();
}

bool ATM::isFree()
{
	return avail;
}

void ATM::printState()
{
	cout << "avail = " << avail << ", timeRem = " << timeRem << ", timeSpent = " << timeSpent << ", length = " << getQueueLength() << "." << endl;
}

int ATM::get_timeSpent()
{
	return timeSpent;
}
