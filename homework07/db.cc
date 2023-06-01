#include "db.h"
// ---------------------------------------------
// SNode class
// Default constructor
// BASIC function header is provided for so that the code will compile
// The actual function header may be different
// call the Node default constructor and increase numstudents
SNode::SNode() : Node(this->num_students++)
{
	// default constructor should never be called in the final program
	// but fill these out for safety
	first = "Default";
	last = "Constructor";
	age = 99;
}

// Constructor
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 
SNode::SNode(string f_, string l_, unsigned int a_) : Node(this->num_students++)
{
	first = f_;
	last = l_;
	age = a_;
}
// Destructor
SNode::~SNode()
{
	// no dynamic allocation here, empty destructor
}

unsigned int SNode::num_students = 0;

// Public interface
void SNode::change_first(string f_)
{
	first = f_;
}
void SNode::change_last(string l_)
{
	last = l_;
} 
string SNode::get_first()
{
	return first;
}
string SNode::get_last()
{
	return last;
}
unsigned int SNode::get_age()
{
	return age;
}
// Print information about the student
// do not change this
void SNode::print_info(ostream& to)
{
    to << "Student ID: " << this->get_key()
       << "\tFirst: " << this->first
       << "\tLast: " << this->last
       << "\tAge: " << this->age << endl;
}
// ---------------------------------------------
