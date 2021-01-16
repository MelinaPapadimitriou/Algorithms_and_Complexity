#include <iostream>
#include <list>
#include "insert.hpp"
#include "dsa.hpp"

using namespace std;

// A class that represents an undirected graph
class Graph
{
    int V;          // No. of vertices
    list<int> *adj; // A dynamic array of adjacency lists

    //Γεμισμα λίστας γειτνίασης(Σύνδεσης κορυφών)
    void fill_Graph(const input &in);

public:
    // Constructor and destructor
    Graph(const input &in);
    ~Graph() {}

    // Prints first_fit coloring of the vertices
    void greedyColoring();
    void DSatur();                        // Execution of DSatur algorithm

};