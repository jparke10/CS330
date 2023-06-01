#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
	key = 0;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Constructor
Node::Node(int in) {
	key = in;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Destructor
Node::~Node() {
}

// Add parent 
void Node::add_parent(Node* in) {
	parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
	left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
	right = in;
}

// Get key
int Node::get_key()
{
	return key;
}
// Get parent node
Node* Node::get_parent()
{
	return parent;
}
// Get left node
Node* Node::get_left()
{
	return left;
}
// Get right node
Node* Node::get_right()
{
	return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
	if (in != nullptr) {
		// recursive call of each
		// covers all branches of tree
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	}
}
// Constructor
BST::BST()
{
	root = nullptr;
}
void destroy(Node* in) {
	if (in == nullptr) {
		return;
	} else {
		destroy(in->get_left());
		destroy(in->get_right());
		delete in;
	}
}
// Destructor
BST::~BST()
{
	// need to recurse through tree
	// to delete every node, so we call a helper func
	destroy(root);
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
	Node* y = nullptr;
	Node* x = root;
	while (x != nullptr) {
		y = x;
		if (in->get_key() < x->get_key()) {
			x = x->get_left();
		} else {
			x = x->get_right();
		}
	}
	in->add_parent(y);
	if (y == nullptr) {
		root = in;
	} else if (in->get_key() < y->get_key()) {
		y->add_left(in);
	} else {
		y->add_right(in);
	}
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
	Node* y = nullptr;
	Node* x = nullptr;
	// determine node y to splice out
	// out if 0 or 1 children
	// successor if 2 children
	if (out->get_left() == nullptr || out->get_right() == nullptr) {
		y = out;
	} else {
		y = this->get_succ(out);
	}

	// x is set to child of y, or nullptr if no child
	// if y is out, then <= 1 children
	// if y is succ, then it only has one child (and no left child)
	if (y->get_left() != nullptr) {
		x = y->get_left();
	} else {
		x = y->get_right();
	}

	// splice out y
	if (x != nullptr)
		x->add_parent(y->get_parent());
	if (y->get_parent() ==  nullptr) {
		root = x;
	} else if (y == y->get_parent()->get_left()) {
		y->get_parent()->add_left(x);
	} else {
		y->get_parent()->add_right(x);
	}
	
	// copy y's data into out, thus also copying the key
	// transform y into out by modifying its parents and children,
	// then modifying the children and parents themselves
	if (y != out) {
		y->add_parent(out->get_parent());
		if (y->get_parent() == nullptr) {
			root = y;
		} else if (out == out->get_parent()->get_left()) {
			y->get_parent()->add_left(y);
		} else {
			y->get_parent()->add_right(y);
		}
		y->add_left(out->get_left());
		y->add_right(out->get_right());
		if (y->get_left() != nullptr) {
			y->get_left()->add_parent(y);
		}
		if (y->get_right() != nullptr) {
			y->get_right()->add_parent(y);
		}
	}
	// remove out as it no longer exists in the tree
	delete out;
}
// minimum key in the BST
Node* BST::tree_min()
{
	return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
	return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	Node* min = in;
	while (min->get_left() != nullptr) {
		min = min->get_left();
	}
	return min;
		
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
	Node* max = in;
	while (max->get_right() != nullptr) {
		max = max->get_right();
	}
	return max;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
	Node* current = in;
	// handler for if no successor
	if (current == tree_max())
		return nullptr;

	if (current->get_right() != nullptr)
		return get_min(current->get_right());
	Node* succ = current->get_parent();
	while (succ != nullptr && current == succ->get_right()) {
		current = succ;
		succ = succ->get_parent();
	}
	return succ;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	// inverse of successor: left instead of right
	Node* current = in;
	if (current == tree_min())
		return nullptr;

	if (current->get_left() != nullptr)
		return get_max(current->get_left());
	Node* pred = current->get_parent();
	while (pred != nullptr && current == pred->get_left()) {
		current = pred;
		pred = pred->get_parent();
	}
	return pred;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
	inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	Node* current = root;
	// recursive action - if the search key is less than the current key
	// then we check the left node, otherwise check right
	while (current != nullptr && search_key != current->get_key()) {
		if (search_key < current->get_key()) {
			current = current->get_left();
		} else
			current = current->get_right();
	}
	return current;
}
// ---------------------------------------
