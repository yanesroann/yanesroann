/* Program: LinkedList.cpp
 * Author: Roann Yanes
 * This program is a List class.
 */
#include <string>
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include <iostream>   // for using cout
using namespace std;

/// Node class interface ///
template<typename T> class List; // forward declaration

template<typename T> // templated node type
class Node 
{
  friend class List<T>; // make the main class a friend

  public:
    Node(const T &); // constructor
    T getData() const; // get function

  private:
    T data; // data for linked list node
    Node<T> *next; // pointer to next object
};

//// Node class implementation ////

  template<typename T>  // constructor, using member initialization list syntax
  Node<T>::Node(const T &info) : data(info),next(NULL) {}

  template<typename T> // simple get function
  T Node<T>::getData(void) const { return data; }

//// end of implementation ////

/// List class interface ///

template<typename T> // templated class
class List 
{
  public:
    List(); // constructor
    ~List(); // deconstructor
    int nodeCount(); // how many nodes are in the list
    bool empty(); // if the list is empty
    void pushBack(const T &); // add a node to end of list
    void pushFront(const T &);  // add node to the front of the list
    void print(); // display contents of the lisnt index)
    T getNode(int); 
    List<T> addNumberLists(List<T> &, List<T> &); // adds to lists together

  private:
    Node<T> *head; // first element in the list
    Node<T> *newNode(const T &); // helper function; creates a new node  
};

/// List class implementation ///

  template<typename T>
  List<T>::List() : head(NULL) {} // constructor with empty body

  template<typename T> 
  List<T>::~List() // destructor
  {
    if (!empty()) // follow the links, deleting as it goes
    { 
      Node<T> *p = head;

      while (p != NULL) 
      {
        Node<T> *next = p->next; // retrieves this node's "next" before it deletes it
        delete p;
        p = next;
      }
    }
  }

  template<typename T> // utility function to create a node
  Node<T> *List<T>::newNode(const T &value) 
  {
    return new Node<T>(value);
  }

  template<typename T> // checks to see if the list is empty
  bool List<T>::empty() { return (head == NULL); }

  template<typename T> // add node to the front of the list
  void List<T>::pushFront(const T &value) 
  {
    Node<T> *x = newNode(value);

    x->next = head;
    head = x;
  }

  template<typename T> // returns the number of nodes in the list
  int List<T>::nodeCount(void) 
  {
    int n = 0;

    for(Node<T> *p = head; p != NULL; p = p->next) { n++; } // increments the count

    return n;
  }

  template<typename T>
  void List<T>::print() // debug function for printing contents and pointer values
  {
    Node<T> *p = head;
    for( ; p != NULL; p = p->next) 
    {
      cout << p->getData();
    }
    cout << endl;
  }

  template<typename T>
  void List<T>::pushBack(const T &data) // adds a node to the end of the list
  {
    Node<T> *nn  = newNode(data);

    if (empty()) 
    { 
      head = nn;
    }
    else 
    { 
      Node<T> *p = head;
      while (p->next != NULL) { p = p->next; } // go to end of list
      p->next = nn;
    }
  }
  
  template<typename T>
  T List<T>::getNode(int index)  // returns the node specified
  {
    Node<T> *current = head;

    if (index == 0) { return head->data; } // returns the first node
    else
    {
      for(int i = 1; i <= index; i++)
      {
        current = current->next; // finds the node at the specified location
      }
    }
    return current->data;
  }      

  template<typename T>
  List<T> List<T>::addNumberLists(List<T> &l1, List<T> &l2)
  {
    List<T> newList;
    T number;
    int carry = 0;
    if ( l1.nodeCount() > l2.nodeCount() ) // if the first list is greater than the second list
    {
      while (l1.nodeCount() != l2.nodeCount()) // while the lists are not the same size
      {
        l2.pushBack(0); // adds zeros to make the linked lists equal
      }
      for (int i = 0; i <= l1.nodeCount() - 1; i++) // iterates through the nodes of the lists
      {
        T newElement = carry + l1.getNode(i) +  l2.getNode(i); // adds the nodes one-by-one
        if (newElement >= 10)
        {
          if (newElement % 10 == 0)
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
          else
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
        }
        else
        {
          newList.pushFront(newElement); // pushes only the ones digit
          carry = 0;
        }
      }
    }
    else if ( l1.nodeCount() < l2.nodeCount() ) // if the first list is smaller than the second list
    {
      while (l1.nodeCount() != l2.nodeCount()) // while the lists are not the same size
      {
        l1.pushBack(0); // adds zeros to make the linked lists equal
      }
      for (int i = 0; i <= l2.nodeCount() - 1; i++) // iterates through the nodes of the lists
      {
        T newElement = carry + l1.getNode(i) +  l2.getNode(i); // adds the nodes one-by-one
        if (newElement >= 10)
        {
          if (newElement % 10 == 0) 
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
          else
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
        }
        else
        {
          newList.pushFront(newElement); // pushes only the ones digit
          carry = 0;
        }
      }  
    }
    else if ( l1.nodeCount() == l2.nodeCount() ) // if the first list is equal to the second list
    {
      for (int i = 0; i <= l1.nodeCount() - 1; i++) // while the lists are not the same size
      {
        T newElement = carry + l1.getNode(i) +  l2.getNode(i); // adds the nodes one-by-one
        if (newElement >= 10)
        {
          if (newElement % 10 == 0) 
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
          else
          {
            number = newElement - 10; // adds only ones digit
            newList.pushFront(number); // pushes only the ones digit
            carry = 1; // carries a one to the next node
          }
        }
        else
        {
          newList.pushFront(newElement); // pushes only the ones digit
          carry = 0;
        }
      }
    }
    if (carry == 1) { newList.pushFront(1); } // adds a one to the front of the list
    return newList; // returns the sum
  }

/// end of List implementation ///

#endif

int main(int argc, char *argv[]) 
{
  string numString1, numString2; // declares two strings
  while (cin >> numString1 >> numString2) // runs until user EOF
  {

    List<int> ll;  // define templated list
    List<int> ll2;  // define templated list

    char str, str2; // declares two characters

    for(unsigned it = 0; it != numString1.length(); it++) // converts second number to nodes of a linked list
    { 
      str = numString1[it];  // stores specified character of string
      ll.pushFront(str - '0'); // converts the char to an int and adds it to the list
    }

    for (unsigned it = 0; it != numString2.length(); it++) // converts second number to nodes of a linked list
    { 
      str2 = numString2[it]; // stores specified character of string
      ll2.pushFront(str2 -'0'); // converts the char to an int and adds it to list
    }
    List<int> newList = newList.addNumberLists(ll, ll2); // calls the "add" function to add the nodes 
    newList.print(); // prints the sum
  }
}
