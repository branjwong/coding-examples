/*
 * BSTree.cpp
 *
 *  Created on: Mar 5, 2010
 *      Author: Brandon J Wong
 */

#include "BSTree.h"

BSTree::BSTree() {
	root = 0;
}

// Copy constructor
BSTree::BSTree(const BSTree & rbt){
	recBuild(rbt.root);
}

BSTree::~BSTree() {
	// recDestroy(root);
}



// inserts a customer into the tree
bool BSTree::insert(string x, char y, int z) {
	bool found = true; // evaluates to true if a duplicate is found
	int treeCase = -1; // used for removal, ignore for insertion
	Node *parent = 0;
	Customer *c = new Customer(x,y,z);

	// target points to the node pointer that will point to the newly inserted node
	Node **target = bstSearch(&root, c, found, treeCase, parent);
	

	if (found == false){
		// attach a node to the node pointer (e.g. root, or a left/rightChild pointer)
		*target = new Node(c, parent);
		return true;
	}
	else {
		// duplicates don't work
		return false;
	}	
}



bool BSTree::remove(string x, char y) {
	int treeCase = 0;
	bool found = false;
	Customer toRem(x,y);
	Node *parent;
	// target points to the node that will be deleted
	Node *target = *bstSearch(&root, &toRem, found, treeCase, parent);
	// set parent to the parent of the node to be deleted
	parent = target->parent;

	// only run removal if a match to (x,y) is found
	if (found == true){

		// Case 1: target is a leaf
		if (treeCase == 1){
			//compare target with parent
			if (*target->data < *parent->data){
				// set target's parent's left child to null
				target->parent->leftChild = 0;
				delete target;
				target = 0;
				return true;
			}
			else if (*target->data > *parent->data){
				// set target's parent's right child to null
				target->parent->rightChild = 0;
				delete target;
				target = 0;
				return true;
			}
		}
		// Case 2: target has a leftchild
		else if (treeCase == 2){
			//compare target with parent
			if (parent != 0 && *target->data < *parent->data){
				//replace parent's left child with *target's subtree
				parent->leftChild = target->leftChild;
				delete target;
				target = 0;
				return true;
			}
			else if (parent != 0 && *target->data > *parent->data){
				//replace parent's right child with *target's subtree
				parent->rightChild = target->leftChild;
				delete target;
				target = 0;
				return true;
			}
			else {
				root = target->leftChild;
				delete target;
				target = 0;
				return true;
			}
		}
		// Case 3: target has a rightchild
		else if (treeCase == 3){
			//compare target with parent
			if (parent != 0 && *target->data < *parent->data){
				//replace parent's left child with *target's subtree
				parent->leftChild = target->rightChild;
				delete target;
				target = 0;
				return true;
			}
			else if (parent != 0 && *target->data > *parent->data){
				//replace parent's right child with *target's subtree
				parent->rightChild = target->rightChild;
				delete target;
				target = 0;
				return true;
			}
			else {
				root = target->rightChild;
				delete target;
				target = 0;
				return true;
			}
		}
		// Case 4: target has 2 children
		else if (treeCase == 4){
			// find successor
			vector<Customer> vc = rangeSearch(target->data->get_name(), target->data->get_initial(), target->rightChild->data->get_name(), target->rightChild->data->get_initial());
			Customer successor(vc[1].get_name(), vc[1].get_initial());
			Node *tempParent;
			Node *temp = *bstSearch(&root, &successor, found, treeCase, tempParent);
			// detatch successor
			tempParent->leftChild = 0;
			// attach target node's children to successor
			temp->leftChild = target->leftChild;
			temp->rightChild = target->rightChild;
			// make successor child of target's parent

			// if target < target's parent, make successor left child of target's parent
			if (parent != 0 && *target->data < *parent->data){				
				parent->leftChild = temp;
				delete target;
				target = 0;
				return true;
			}
			// if target > target's parent, make successor right child of target's parent
			else if (parent != 0 && *target->data > *parent->data){
				parent->rightChild = temp;
				delete target;
				target = 0;
				return true;
			} else {
				root = temp;
				delete target;
				target = 0;
				return true;
			}
		}
	}
	// do not run removal if no match to (x,y) is found
	else {
		return false;
	}


}


bool BSTree::search(string x, char y) {
	Customer *toFind = new Customer(x,y);
	bool found = false;
	int treeCase = -1;
	Node *parent;
	// treeCase, parent, and return value are unused
	// found is modified during bstSearch
	bstSearch(&root, toFind, found, treeCase, parent);
	delete toFind;
	if (found == true){
		return true;
	}
	else {
		return false;
	}

}


vector<Customer> BSTree::rangeSearch(string x, char y, string z, char a) {
	vector<Customer> result;
	// initialize two customers for use in bstSearch w/ (x,y) and (z,a)
	Customer leftTest(x,y);
	Customer rightTest(z,a);
	rangeHelper(root, result, leftTest, rightTest);
	return result;
}

// recursively adds to vector<Customer>
void BSTree::rangeHelper(Node *n, vector<Customer> &v, Customer &leftTest, Customer &rightTest){
	if (n != 0){
		// if (n->leftChild != 0 && *n->leftChild->data >= leftTest){
			rangeHelper(n->leftChild, v, leftTest, rightTest);
		// }
		if (leftTest <= *n->data && *n->data <= rightTest){
			v.push_back(*n->data);
		}
		// if (n->rightChild != 0 && *n->rightChild->data <= rightTest){
			rangeHelper(n->rightChild, v, leftTest, rightTest);
		// }
	}
}

void BSTree::inOrderPrint() {
	inOrderPrintRec(root);
}

// basic inOrder traversal
void BSTree::inOrderPrintRec(Node *n) {
	if (n != 0) {
		inOrderPrintRec(n->leftChild);
		cout << *n->data << endl; //visit
		inOrderPrintRec(n->rightChild);
	}
}

void BSTree::treePrint() {
        treePrintRec(root,0);
}

// basically, a reverse inOrder traversal
void BSTree::treePrintRec(Node *n, int depth) {
    if (n != 0) {
        treePrintRec(n->rightChild, depth+1);
        for (int i=0; i<2*depth; i++) {
                cout << " ";
        }
        cout << "-" << *n->data << endl;
        treePrintRec(n->leftChild, depth+1);
    }
}


// if c is in tree: 
	// returns the address of the node pointer that points to the node that has the data
// if c isn't in tree: 
	// returns the address of the node pointer that points to the node where the data should go
Node** BSTree::bstSearch(Node **n, Customer *c, bool &found, int &treeCase, Node *&parent){
	// If the node points to no data, return the node
	if (*n == 0){
		found = false;
		return n;
	}
	// If the target is less than the data in the node search its left subtree
	if (*c < *((*n)->data)){
		parent = *n;
		return bstSearch(&(*n)->leftChild, c, found, treeCase, parent);
	}
	// If the target is greater than the data in the node search its right subtree
	else if (*c > *((*n)->data)){
		parent = *n;
		return bstSearch(&(*n)->rightChild, c, found, treeCase, parent);
	}
	else {
		found = true;
		// has no children
		if ((*n)->leftChild == 0 && (*n)->rightChild == 0){
			treeCase = 1;
		}
		// has a left child
		else if ((*n)->leftChild != 0 && (*n)->rightChild == 0){
			treeCase = 2;
		}
		// has a right child
		else if ((*n)->leftChild == 0 && (*n)->rightChild != 0){
			treeCase = 3;
		}
		// has two children
		else if ((*n)->leftChild != 0 && (*n)->rightChild != 0){
			treeCase = 4;
		}
		return n;
	}
}

// preOrder traversal
void BSTree::recBuild(Node *n){
	if (n != 0){
		insert(n->data->get_name(), n->data->get_initial(), n->data->get_account());
		recBuild(n->leftChild);
		recBuild(n->rightChild);
	}
}

// postOrder traversal
void BSTree::recDestroy(Node *n){
	if (n != 0){
		recDestroy(n->leftChild);
		recDestroy(n->rightChild);
		remove(n->data->get_name(), n->data->get_initial());
	}
}