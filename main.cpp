#include "first_fit.hpp"

int main()
{
    int mn;
    string actualname=fileselection();
    std::string fn="./datasets/"+actualname;
    input in(number_of_vertices(actualname));
    in.openfile(fn);
    Graph m(in);
    while (true)
    {
        mn = menu();
        switch (mn)
        {
        case 1:
         in.stats();
           break;
        case 2:
         m.greedyColoring();
         break;
        case 3:
         m.DSatur(); 
        break;
        case 4:
           exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
}