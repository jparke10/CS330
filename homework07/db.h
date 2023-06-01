#ifndef DB_H_
#define DB_H_
#include <iostream>
#include "bst.h"

using namespace std;


class SNode : public Node {
private:
    string first;
    string last;
    unsigned int age;
    static unsigned int num_students;
    
public:
    // Constructors and destructor
    SNode();
    SNode(string f_, string l_, unsigned int a_);
    ~SNode();

    // public interface
    void change_first(string f_);
    void change_last(string l_);

    string get_first();
    string get_last();
    unsigned int get_age();
  
    void print_info(ostream& to);
};
#endif
