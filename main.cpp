/*************************************************************************************
* Project:
* Andrew M.
*************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Metro.h"
#include "Metro.cpp"
#include "Counter.h"
#include "Counter.cpp"

using namespace std;

int main(int argc, char *argv[])
{

    Metro City;
    Counter Log;

    ifstream inf(argv[1]);

    if (!inf)
    {
        cerr << "Whoops..,file could not be opened." << endl;
        exit(1);
    }

    string svg, temp;

    while(inf)
    {
        getline(inf, temp);
        svg+=temp;
    };

    auto n = City.start(svg,0);

    ofstream outf("C:\\Test\\Ver_02\\CREATED "+ n.first + ".svg");
    ofstream logf("C:\\Test\\Ver_02\\CREATED "+ n.first + ".log");
    City.send_to_stream(outf,n.first);

    do
    {

        auto p = City.find_or_stop(svg,logf);

        if(p.first.empty())
            break;

        else
        {
            City.send_to_stream(outf,p.first);
            Log.calculator1("Line: ",p.second);
        };

        auto p1 = City.find_coordinates(svg, p.second);

        auto p2 = City.find_station(p1.first, p1.second);

        City.print(station,line_coord,outf);
        Log.calculator2("Station: ",p2.second);

        station.clear();
        line_coord.clear();
        svg = p2.first;

    }
    while(1);

    Log.show(logf);

    return 0;
};

