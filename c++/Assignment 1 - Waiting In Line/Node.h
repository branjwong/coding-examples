/*
 * Node.h
 *
 */

#ifndef NODE_H_
#define NODE_H_
#include "Customer.h"

class Node 
{
public:
	Node();
	Node(Customer *c);
	Node(Customer *c, Node *nd);
	~Node();

	Customer *data;
	Node *next;
};

#endif /* NODE_H_ */
