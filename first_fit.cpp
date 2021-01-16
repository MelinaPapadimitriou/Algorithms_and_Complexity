#include "first_fit.hpp"
using namespace std;

void Graph::fill_Graph(const input &in)
{
    const int size=in.size();
    this->V=size;
    this->adj=new list<int>[size];
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(i==j) continue;
            if(in.is_adjacence(i,j))
            {
                this->adj[i].push_back(j);
            }
        }
    }
}

Graph::Graph(const input &in)
{
    this->fill_Graph(in);
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    int *result=new int[this->V];
    bool *available=new bool[this->V];

    // Assign the first color to first vertex
    result[0] = 0;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1; // no color is assigned to u

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices;
    for (int cr = 0; cr < V; cr++)
        available[cr] = true;

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        

        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr])
                break;

        result[u] = cr; // Assign the found color

        // Reset the values back to true for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;
    }

    // print the result
    for (int u = 0; u < V; u++)
        cout << "*** Vertex:" << u << " -> *** Color:"<< result[u] << endl;

    delete[] result;
    delete[] available;
}

void Graph::DSatur()                    
{
    vector<a_data> coloring;
    vector<int> saturationlevel;
    vector<int> saturcolors;
    vector<int> todo;
    int maxvertex = 0;
    int degree = this->adj[0].size();
    for (int i = 1; i < this->V; i++)
    {
        if (this->adj[i].size() > degree)
        {
            maxvertex = i;
            degree = this->adj[i].size();
        }
    }
    coloring.push_back(a_data{maxvertex, 0});
    for (int i = 0; i < this->V; i++)
    {
        saturationlevel.push_back(0);
        if (i != maxvertex)
        {
            todo.push_back(i);
        }
    }
    saturationlevel[maxvertex] = INT_MIN;
    for (auto itr = this->adj[maxvertex].begin(); itr != this->adj[maxvertex].end(); itr++)
    {
        saturationlevel[*itr]++;
    }
    while (!todo.empty())
    {
        int saturvertex = -1;
        int saturation = -1;
        for (int i = 0; i < this->V; i++)
        {
            if (saturationlevel.at(i) > saturation)
            {
                saturation = saturationlevel.at(i);
                saturvertex = i;
            }
        }
        saturcolors.clear();
        for (auto itr = this->adj[saturvertex].begin(); itr != this->adj[saturvertex].end(); itr++)
        {
            for (int i = 0; i < coloring.size(); i++)
            {
                if (coloring.at(i).vertex == *itr)
                {
                    saturcolors.push_back(coloring.at(i).color);
                }
            }
        }
        auto itr = todo.begin();
        auto end = todo.end();
        while (itr != end)
        {
            if (*itr == saturvertex)
            {
                todo.erase(itr);
                break;
            }
            itr++;
        }
        int lc = 0;
        bool fin = false;
        while (!fin)
        {
            fin = true;
            for (auto &x : saturcolors)
            {
                if (x == lc)
                {
                    lc++;
                    fin = false;
                }
            }
        }
        coloring.push_back(a_data{saturvertex, lc});
        saturationlevel[saturvertex] = INT_MIN;
        for (auto i = this->adj[saturvertex].begin(); i != this->adj[saturvertex].end(); i++)
        {
            if (saturationlevel[*i] != INT_MIN)
            {
                saturationlevel[*i]++;
            }
        }
    }
    std::cout<<"***DSATUR RESULTS::***"<<coloring.size()<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;
    for(auto &x:coloring)
    {
        x.print();
    }
    std::cout<<"***colors :"<<std::max_element(coloring.begin(),coloring.end())->color+1<<std::endl;
}