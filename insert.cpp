#include "insert.hpp"
#include <thread>

vector<string> files;
vector <int> file_exams;
string menutab="\n\n";
string center="\t\t\t";

//-------------------------------------------------------------------------------------
//class functions
input::input(int number_of_exams)
{
   for(int i=0;i<number_of_exams;i++)
   {
       this->exam_students.push_back(set <int>());
       this->adj.push_back(vector <int>());
   }
}

void input::openfile(string filename)
{
    int i;
    // ανάγνωση δεδομένων
    stringstream  ss(filename);
    getline(ss,this->filename,'/');
    getline(ss,this->filename,'/');
    getline(ss,this->filename,'/');
    fstream fs;
    fs.open(filename,ios::in);
    if (!fs.is_open())
    {
        cerr << " Not open file " << filename << endl;
        exit(-1);
    }
    int student_id = 0;
    string line, word;
    while (getline(fs, line))
    {
        if (line.empty())
            continue;
        student_id++;
        istringstream iss(line);
        int exam_id;
        while (iss>>exam_id)
        {
            this->exam_students[exam_id-1].insert(student_id);
        }
    }
    fs.close();
    cout<<"Exams:"<<this->exam_students.size()<<endl;
    this->fill_adjacency();
}

void input::printexams()
{
    for(auto &x:this->exams)
    {
        cout<<x<<endl;
    }
}

int input::size()const
{
    return this->adj.size();
}

bool input::is_adjacence(int s,int t)const
{
    return this->adj[s][t]!=0;
}

void input::fill_adjacency()
{
    const int size=this->exam_students.size();
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(i==j)
            {
                adj[i].push_back(0);
                continue;
            }
            adj[i].push_back(count_common_elements(this->exam_students.at(i),this->exam_students.at(j)));
        }
    }
}

double input::density()
{
    int counter=0;
    const int size=this->exam_students.size();
    for(int i=0;i<size;i++)
    {
        counter+=count_if(this->adj[i].begin(),this->adj[i].end(),[](int &a) {return a!=0;});
    }
    return (double)counter/pow(size,2);
}

void input::stats()
{
    int max,min,median;
    double mean,cv,dens;
    int *sum;
    const int size=this->exam_students.size();
    sum=new int[size];
    for(int i=0;i<size;i++)
    {
        sum[i]=count_if(this->adj[i].begin(),this->adj[i].end(),[](int &a) {return a!=0;});
    }
    max=*max_element(sum,sum+size);
    min=*min_element(sum,sum+size);
    mean=accumulate(sum,sum+size,0)/(size*1.0);
    sort(sum,sum+size);
    median=sum[size/2];
    cv=0.0;
    for(int i=0;i<size;i++)
    {
        cv+=pow((double)sum[i]-mean,2);
    }
    cv/=size-1;
    cv=(sqrt(cv)/mean)*100.0;
    dens=this->density();
    cout<<endl<<"*****Statistics:*****"<<endl;
    cout<<" - Density:"<<dens<<endl;
    cout<<" - Max:"<<max<<endl;
    cout<<" - Min:"<<min<<endl;
    cout<<" - Median:"<<median<<endl;
    cout<<" - Mean:"<<mean<<endl;
    cout<<" - Coeffience of variation:"<<cv<<endl;
    
    delete []sum;
    cout<<endl<<endl;
}


//-------------------------------------------------------------------------
//functions 

int count_common_elements(set<int> s1, set<int> s2)
{
    int c = 0;
    for (int x : s1) // range based for
    {
        for (int y : s2)
        {
            if (x == y)
            {
                c++;
                break;
            }
        }
    }
    return c;
}

int menu()
{
    cout<<menutab;
    int option;
    cout << "1-Print Statistics" << endl;
    cout << "2-First Fit" << endl;
    cout << "3-Dsatur" << endl;
    cout<<"4-Exit"<<endl;
    cout << "Select an option:";
    cin >> option;
    return option;
}

void source()
{
    fstream fs;
    fs.open("input.txt",ios::in);
    string line,word;
    while (getline(fs, line))
    {
        stringstream ss(line);
        getline(ss,word,',');
        files.push_back(word);
        getline(ss,word,',');
        file_exams.push_back(stoi(word));
    }
    fs.close();
}

string fileselection()
{
    int a;
    if (files.empty())
    {
      source();
    }
    for (int i = 0; i < files.size(); i++)
    {
        cout << i + 1 << "." << files.at(i) << endl;
    }
    cout << "Select your input file:";
    cin >> a;
    return files.at(a-1);
}

int number_of_vertices(string fn)
{
    int i=0;
    for(auto &x:files)
    {
        if(x==fn)
        {
           return file_exams[i];
        }
        i++;
    }
    return -1;
}




