/*
 * Node.h
 *
 *  Created on: Mar 5, 2010
 *      Author: Brandon J Wong
 */

#ifndef NODE_H_
#define NODE_H_

#include "Customer.h"

class Node {
public:
	Node();
	Node(Customer *c, Node *p);
	Node(Customer *c, Node *lc, Node *rc);
	~Node();

	Customer *data;
	Node *leftChild;
	Node *rightChild;
	Node *parent;
};

#endif /* NODE_H_ */
