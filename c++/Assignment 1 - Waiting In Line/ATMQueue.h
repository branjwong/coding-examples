/*
 * ATMQueue.h
 *
 */

#ifndef ATMQUEUE_H_
#define ATMQUEUE_H_

#include "Customer.h"
#include "Node.h"

class ATMQueue 
{
public:
	ATMQueue();
	~ATMQueue();
	void add(Customer *c);
	void rem();
	void printList();
	int get_atime();
	int get_ttime();
	int get_length();
	//int *get_head();
	

private:
	//The queue should keep track of the number of people in the queue (so that you can determine the shortest queue) 
	int length;
	Node *head;

};

#endif /* ATMQUEUE_H_ */
