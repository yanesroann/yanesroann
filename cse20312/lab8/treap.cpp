// Program: treap.cpp: Treap Map
// Author: Roann Yanes
// This program is the implementation of the TreapMap class.

#include "map.h"

#include <climits>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>

using namespace std;

// Prototypes - helper functions ------------------------------------------------------------------

extern Node *search_r(Node *node, const string &key); // function from the binary search tree implementation
extern void dump_r(Node *node, std::ostream &os, DumpFlag flag); // function from the binary search tree implementation

static Node *insert_Treap(Node *node, const string &key, const string &value); // modified from insert_r to include priorities of treap
static int random_number_generator(); // function to generate random priorities
static int get_Max_Height(Node *root); // gets the maximum height of the treap
static int get_Min_Height(Node *root); // gets the minimum height of the treap
static Node *rotate_right(Node *p); // right rotate subtree
static Node *rotate_left(Node *p); // left rotate subtree
void pre_order(Node *root); // completes preorder traversal

// Methods ---------------------------------------------------------------------

void            TreapMap::insert(const string &key, const string &value) {
    root = insert_Treap(root, key, value); // inserts the new key and value of a node
}

const Entry     TreapMap::search(const string &key) {
    auto result = search_r(root, key); // searches from the root to the given key
    return (result == nullptr ? NONE : result->entry); // returns the result of the search
}

void            TreapMap::dump(ostream &os, DumpFlag flag) {
    dump_r(root, os, flag); // uses function from binary search tree implementation
}

int             TreapMap::getMaxTreeHeight(){
    return get_Max_Height(root); // gets the maximum height of the treap
}


int             TreapMap::getMinTreeHeight(){
    return get_Min_Height(root); // gets the minimum height of the treap
}

void            TreapMap::preOrderTraversal(){
    pre_order(root); // completes preorder traversal
}

// Internal Functions ----------------------------------------------------------

Node *insert_Treap(Node *node, const string &key, const string &value) // insertion in treap
{
    
    if (node == nullptr) // if the tree is empty, create and return a new node
    {
        return new Node{Entry(key, value), random_number_generator(), nullptr, nullptr};
    }

    if (node->entry.first == key) // checks if key is equal to key in treap
    {
        node->entry.second = value; // sets the value
        return node; // returns the node
    }

    if (node->entry.first > key) // if the key is smaller
    {
        node->left = insert_Treap(node->left, key, value); // insert in left subtree
        if (node->left->priority > node->priority) { node = rotate_right(node); } // fixes heap property if it is violated
    } 
    else // if key is greater
    {
        node->right = insert_Treap(node->right, key, value); // insert in right subtree
        if (node->right->priority > node->priority) { node = rotate_left(node); } // fixes heap property if it is violated
    }

    return node; // returns the node pointer
}

int random_number_generator() // random number generator
{
    static random_device rand_dev; // generates random number
    static default_random_engine rand_eng(rand_dev());
    static uniform_int_distribution<> dist(1, INT_MAX);
    return dist(rand_eng); // generates number in range
}

int get_Max_Height(Node *node) // returns the maximum height of the tree
{
    if (node == NULL) { return 0; } // if tree is empty, return zero
    
    else
    {
        int left_max = get_Max_Height(node->left); // get the maximum height of left subtree recursively
        int right_max = get_Max_Height(node->right); // get the maximum height of right subtree recursively
        if (left_max > right_max) { return (left_max + 1); } // checks for the larger height
        else { return (right_max + 1); }
    }
}

int get_Min_Height(Node *node) // returns the minimum height of the tree
{
    if (node == NULL) { return 0; } // if tree is empty, return zero
    
    if (node->left == NULL && node->right == NULL) { return 1; } // base case for when height of treap is equal to zero

    if (!node->left) { return (get_Min_Height(node->right) + 1); } // if left subtree is NULL, recurse right subtree
    if (!node->right) { return (get_Min_Height(node->left) + 1); } // if right subtree is NULL, recurse left subtree

    int right_min = get_Min_Height(node->right); // used for comparison
    int left_min = get_Min_Height(node->left);
    
    if (left_min > right_min) { return (right_min + 1); } // checks for the smaller height
    else { return (left_min + 1); }
}

Node *rotate_right(Node *point) // right rotate subtree rooted with point
{

    Node *node1 = point->left;
    Node *node2 = node1->right;

    node1->right = point; // performs the rotation
    point->left = node2;

    return node1; // returns the new root
}

Node *rotate_left(Node *point) // left rotate subtree rooted with point
{
    Node *node1 = point->right;
    Node *node2 = node1->left;

    node1->left = point; // performs the rotation
    point->right = node2;

    return node1; // returns the new root
}

void pre_order(Node *root) // completes preorder traversal
{
    if (root) // if the root does not equal NULL
    {
        cout << root->entry.first << " "; // prints the key
        pre_order(root->left); // calls the function on the left subtree
        pre_order(root->right); // calls the function on the right subtree
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
