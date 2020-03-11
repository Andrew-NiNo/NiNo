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
                                                    ///Create two objects of class Metro and Counter
    Metro City;
    Counter Log;
                                            ///We expect the desired argument from cmd with the specified file path for parsing
    ifstream inf(argv[1]);                          ///And create a stream with data from a file

    if (!inf)
    {
        cerr << "Whoops..,file could not be opened." << endl;
        exit(1);
    }

    string svg, temp;

    while(inf)
    {
        getline(inf, temp);                         ///Create string from stream
        svg+=temp;
    };
                                                                ///We look for the desired name in the string
    auto start = City.search_block(Metro::START,svg);           ///and create outgoing files with this name

    ofstream outf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".svg");
    ofstream logf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".log");

    City.send_to_file(outf,start.first);

    do
    {
        auto line = City.search_block(Metro::LINE,svg);           ///We are looking for possible ways (metro lines)

        City.send_to_file(outf,line.first);
        Log.calculator1("Line: ",line.second);                      ///Counting the way

        auto coord = City.find_coordinates(svg, line.second,Metro::COORDINATES); ///We are looking for the coordinates of the stations

        auto stat = City.find_station(svg, coord.second,Metro::STATION);            ///We are looking for stations

        City.print(station,line_coord,outf);                                ///We send the results to a file
        Log.calculator2("Station: ",stat.second);                       ///Counting the stations

        svg = stat.first;                                               ///Override string for next loop iteration
    }
    while(ac_dc);

    Log.show(logf);                                             ///We print in the log file the values of the counters

    return 0;
};

