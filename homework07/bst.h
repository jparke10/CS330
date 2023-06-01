#ifndef BST_H_
#define BST_H_

#include <iostream>

using namespace std;

class Node {
private:
    int key;
    Node* parent;
    Node* left;
    Node* right;
public:
    // Default constructor
    Node();
    // Constructor
    Node(int in);
    // Destructor
    // a virtual constructor is required for inheritance
    virtual ~Node();

    // Add to parent of current node
    void add_parent(Node* in);
    // Add to left of current node
    void add_left(Node* in);
    // Add to right of current node
    void add_right(Node* in);

    // Get key
    int get_key();
    // Get parent node
    Node* get_parent();
    // Get left node
    Node* get_left();
    // Get right node
    Node* get_right();

    virtual void print_info(ostream& to);
};

class BST {
private:
    Node* root;

    // Walk the subtree from the given node
    void inorder_walk(Node* in, ostream& to);
    // Get the minimum node from the subtree of given node
    Node* get_min(Node* in);
    // Get the maximum node from the subtree of given node
    Node* get_max(Node* in);
public:
    // Constructor and Destructor
    BST();
    ~BST();

    // Modify tree
    void insert_node(Node* in);
    void delete_node(Node* out);

    // Find nodes in the tree
    Node* tree_min(); // minimum key value
    Node* tree_max(); // maximum key value
    Node* get_succ(Node* in); // successor for a given node
    Node* get_pred(Node* in); // predecessor for a given node
    void walk(ostream& to); // Traverse the tree from min to max recursively
    Node* tree_search(int search_key);
};
#endif
