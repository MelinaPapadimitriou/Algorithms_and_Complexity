#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

class input
{
    private:
        string filename;
        string statsstring;
        set <string> exams;
        vector<set<int>> exam_students;
        vector <vector <int>> adj;
        void fill_adjacency();
        double density();
    public:
        input(int number_of_exams);
        void openfile(string filename);
        int size()const;
        bool is_adjacence(int s,int t)const;
        void stats();
        void printexams();
        
};

int count_common_elements(set<int> s1, set<int> s2);
int menu();
void source();
string fileselection();
int number_of_vertices(string fn);

 

    