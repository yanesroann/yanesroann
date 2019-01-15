/* Program: traversals.cpp
 * Author: Roann Yanes
 * This program, given a directed graph, determines if there is a path between two nodes in the graph.
 */

#include <map>
#include <set>
#include <stack>
#include <iostream>
using namespace std;

bool is_there_a_path(map<char, set<char>> &, char, char); // prototype

int main(int argc, char *argv[])
{
  int NEDGES, NPATHS, graph_number = 0; // initializes number of edges, paths, and number of graphs that are read in 
  char source, destination; // initializes the source and destination of the path
  bool path_found;

  map<char, set<char>> adjacency_matrix; // initializes adjacency matrix to represent the directed graph

  while (cin >> NEDGES) // runs until user presses CTRL-D
  {
    graph_number++; // keeps a running count of the number of graphs the user enters
    for(int it = 0; it < NEDGES; it++) // reads in the source and detination for the number of edges specified
    { 
      cin >> source >> destination;
      adjacency_matrix[source].insert(destination); // stores the source and destination in the adjacency matrix
    }

    cin >> NPATHS; // reads in the number of paths
  
    for(int it = 0; it < NPATHS; it++) // reads in the source and destination for the number of paths the user specified
    {
      cin >> source >> destination;
      path_found = is_there_a_path(adjacency_matrix, source, destination); // calls the internal `is_there_a_path()` function to see if there is a path between to vertices and stores it in a boolean
      if (path_found) // checks if there is a path found between the two vertices and tells the user if the path exists
      {
        cout << "In Graph " << graph_number << " there is a path from " << source << " to " << destination << endl; 
      }
      else
      {
        cout << "In Graph " << graph_number << " there is no path from " << source << " to " << destination << endl;
      }
    }
    adjacency_matrix.clear(); // clears the adjacency matrix
    if (graph_number < 5) { cout << endl; } // makes sure there is not an extra white space at the end of input
  }
  return 0;
}

bool is_there_a_path(map<char, set<char>> &graph, char source, char destination) // depth-first search traversal of the directed graph
{
  bool path_found = false;
  stack<char> node_remaining; // unvisited nodes are in a stack
  set<char> node_complete; // visited nodes
  char value;
  node_remaining.push(source); // pushes the first vertex to the stack
  while (!node_remaining.empty()) // while the stack is not empty
  {
    value = node_remaining.top(); // gets value of the vertex at the top of the stack 
    node_remaining.pop(); // removes the element at the top of the stack
    if (node_complete.find(value) == node_complete.end())  // searches for the value from the stack in the set and compares it to the end
    {
      if (value == destination) // if node was found
      { 
        path_found = true; // a path was found
        break;
      } 
      else // no node was found
      {
        node_complete.insert(value); // inserts the value from the stack in the set
        auto map_iterator = graph.find(value); // starts an iterator at the value that was inserted in the set
        if (map_iterator != graph.end()) // if the iterator does not equal the end
        {
          for (auto set_iterator = map_iterator->second.begin(); set_iterator != map_iterator->second.end(); set_iterator++) // goes through the map 
          {
            node_remaining.push(*set_iterator); // pushes the nodes in the map to the stack
          }
        }
      }
    }
  }
  return path_found; // returns if there is a path or not
}
