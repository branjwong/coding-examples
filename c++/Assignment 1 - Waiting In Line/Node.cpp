/*
 * Node.cpp
 *
 */

#include "Node.h"

Node::Node()
{
	data = 0;
	next = 0;
}

Node::Node(Customer *c)
{
	data = c;
	next = 0;
}

Node::Node(Customer *c, Node *nd)
{
	data = c;
	next = nd;
}

Node::~Node()
{
}
