/*
 * ATMQueue.cpp
 *
 */

#include "ATMQueue.h"
#include "Node.h"
#include <iostream>
using namespace std;

ATMQueue::ATMQueue()
{
	head = 0;
	length = 0;
}

ATMQueue::~ATMQueue()
{
	Node* p;
	while (head != 0)
	{
		p = head;
		head = p->next;
		delete p;
	}
	delete head;
	head = 0;
}

void ATMQueue::add(Customer *c)
{
	Node *newNode = new Node(c); //new node with c
	// Check to see if list is empty
	if (head == 0)
	{
		//make the new node the new head
		head = newNode; 
	}
	else
	{
		//move to the end of the list
		Node *p = head;
		while (p->next != 0)
		{
			p = p->next;
		}
		p->next = newNode;
	}
	length++;
	//cout << "new customer added, length = " << length << endl;
}

void ATMQueue::rem()
{
	//need a pointer to the old customer's node

	//move head to next customer
	if(head != 0)
	{
		Node *oldNode = head;
		head = head->next;
		//delete old customer
		delete oldNode;
		//set oldNode to null pointer
		oldNode = 0;
		length--;
	}
}

int ATMQueue::get_atime()
{
	return head->data->get_atime();
}

int ATMQueue::get_ttime()
{
	return head->data->get_ttime();

}

// int *ATMQueue::get_head()
// {
// 	return head;
// }

int ATMQueue::get_length()
{
	return length;
}


