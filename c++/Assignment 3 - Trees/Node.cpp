/*
 * Node.cpp
 *
 *  Created on: Mar 5, 2010
 *      Author: Brandon J Wong
 */

#include "Node.h"

Node::Node(){
	leftChild = 0;
	rightChild = 0;
	parent = 0;
	data = 0;
}

Node::Node(Customer *c, Node *p){
	leftChild = 0;
	rightChild = 0;
	parent = p;
	data = c;
}

Node::Node(Customer *c, Node* lc, Node* rc){
	leftChild = lc;
	rightChild = rc;
	// parent = 0;
	data = c;
}

Node::~Node(){
	delete data;
}

