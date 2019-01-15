/* Program: mst.cpp
 * Author: Roann Yanes
 * This program, given an  undirected graph, determines the minimum spanning tree and the weight of the tree.
 */

#include <string>
#include <map>
#include <queue>
#include <iostream>
using namespace std;

struct Element // used for the priority queue 
{
    int source; // node as source
    int destination; // node as destination
    int location;

    bool operator < (const Element &entry) const { return entry.source < source; } // overloading the '<' operator
};

char number_to_letter(int); // prototype
void minimum_spanning_tree(int ad_m[26][26], int); // prototype

int main(int argc, char *argv[])
{
    size_t NVERTICES; // initializes number of vertices that are read in 
    bool new_line = true;

    while (cin >> NVERTICES) // runs until user presses CTRL-D
    {
        int adjacency_matrix[26][26]; // initializes adjacency matrix to represent the directed graph
        for(size_t it = 0; it < NVERTICES; it++) // reads in the source and destination for the number of vertices specified
        { 
            for(size_t j = 0; j < NVERTICES; j++) // reads in the source and destination for the number of vertices specified
            {
                cin >> adjacency_matrix[it][j]; // stores the source and destination in the adjacency matrix
            }
        }
        if (new_line) { new_line = false; } // prints out correct number of new lines
        else { cout << endl; } // prints new line
        minimum_spanning_tree(adjacency_matrix, NVERTICES); // calls the function that finds the minimum spanning tree
    }
    return 0;
}

char number_to_letter(int node_number) // converts the nodes given in lexicographical order
{
    if (node_number >= 0 && node_number < 26) { return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[node_number]; } // converts the nodes from ints to their respective chars
    else { return 0; }
}

void minimum_spanning_tree(int adjacency_matrix[][26], int NVERTICES) // function to return the weight and the minimum spanning tree using Prim's algorithm
{
    priority_queue<Element> min_tree; // priority queue of Element objects
    map<int, int> checked_nodes; // stores the nodes that are checked
    min_tree.push({0,0,0}); // pushes a zero for the source, destination, and location 
    int weight = 0; // stores total weight
    while(!min_tree.empty()) // while the priority is not empty
    {
        auto nodes = min_tree.top(); // element that compares higher in the queue
        min_tree.pop(); // pops off the element with the highest value
        if (checked_nodes.count(nodes.location)) { continue; }  // if the node is already marked
        weight += nodes.source; // adds to the weight
        checked_nodes[nodes.location] = nodes.destination; // visited equals previous
        for (auto it = 0; it < NVERTICES; it++)
        {
            if (adjacency_matrix[it][nodes.location] != -1) min_tree.push({adjacency_matrix[it][nodes.location], nodes.location, it}); // inserts a new element to the priority queue
        }
    }
    cout << weight << endl; // prints the total weight
    map<string, string> min_set; // stores the minimum spanning tree in pairs
    for (auto j = checked_nodes.begin(); j != checked_nodes.end(); j++)
    {
        char source = number_to_letter(j->first); // converts the numbers to letters
        char destination = number_to_letter(j->second); // converts the numbers to letters
        string temp_node = string() + source + destination; // concatenate strings to find if it is source-destination or destination-source
        string temp_node2 = string() + destination + source; // concatenate strings to find if it is source-destination or destination-source
        if(source > destination && source != destination) { min_set.insert(pair<string, string> (temp_node2, "1")); } // inserts the pair into the final solution set
        else if(source != destination) { min_set.insert(pair<string, string> (temp_node, "1")); } // inserts the pair into the final solution set
    }
    for(auto it = min_set.begin(); it != min_set.end(); it++) // goes through the map of minimum spanning sets
    {
        cout << it->first << endl; // prints out the pairs in the minimum spanning set
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp: 
