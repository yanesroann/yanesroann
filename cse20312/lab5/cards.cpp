/* Program: cards.cpp
 * Author: Roann Yanes
 * This program tests to see if a given binary tree is a binary search tree.
 */

#include <vector>
#include <iostream>
using namespace std;

bool BSTtest(vector<int>&, int, int, int, int); // prototype

int main(int argc, char *argv[])
{
  int treeNode, treeNum = 0; // declares nodes of the tree that need to be read in
  int numNodes;
  bool result;

  while ( != -1) // runs until user presses CTRL-D
  {
    vector<int> treeVector; // declares a new vector each time
    numNodes = treeNode; // size of the tree
    treeNum++; // keeps a count of the number of trees input
    for(int it = 0; it != numNodes; it++) // continues to add nodes to the tree until the user presses the "ENTER" key
    { 
      cin >> treeNode; // reads in the values for the tree
      treeVector.push_back(treeNode); // adds the node to a vector
    }
    result = BSTtest(treeVector, numNodes, 0, 0, 0); // returns a boolean value
    if (result) { cout << "Tree " << treeNum << " is a BST" << endl; } // if "result" is true
    else { cout << "Tree " << treeNum << " is not a BST" << endl; }
  }
  return 0;
}

bool BSTtest(vector<int> &treeVector, int numNodes, int root, int min, int max) // function to determine if the given tree is a binary search tree
{
  int leftchild, rightchild;
  if (root >= numNodes) { return true; } // base case
  if (treeVector[root] != -1) // if the node is not empty
  {
    if (max != 0 && (treeVector[root] > max)) { return false; } // if the node is greater than the maximum value
    if (min != 0 && (treeVector[root] <= min)) { return false; } // if the node is less than or equal to the minimum value
  }
  leftchild = (2*root + 1); // location of the left child node
  rightchild = (2*root + 2); // location of the right child node
  return (BSTtest(treeVector, numNodes, leftchild, min, treeVector[root]) && BSTtest(treeVector, numNodes, rightchild, treeVector[root], max)); // use of recursion
}
