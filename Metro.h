#ifndef METRO_H
#define METRO_H

#include <unordered_map>

using namespace std;

#define PAIR pair<string,string::size_type>
#define MAP unordered_map <Metro::Mode,unordered_map<string,string>>

class Metro
{
private:

    struct Tags                                     ///In the Metro class we assign the values of search tags
    {
        string start_begin = "docname=\"";
        string start_stop = ".";
        string find_begin = "label=\"path";
        string find_stop = "\">";
        string coordinates_begin = "d=\"";
        string coordinates_stop = "\"";
        string correct = "id=\"desc";
        string station_begin = "\">";
        string station_stop = "</desc";
    } tags;

public:
    Metro();

    enum Mode { START,LINE,COORDINATES,STATION,METHOD_1,METHOD_2 };     ///We enumerate the search modes of the desired values

    void replacement(Mode form);                                       ///Member functions

    PAIR search_block(Mode form,string &,string::size_type);
    PAIR search_block(Mode form,string &);
    PAIR find_coordinates(string &,string::size_type,Mode form);
    PAIR find_station(string &,string::size_type,Mode form);
    void print(vector<std::string> &,vector<std::string> &,ofstream &);

    void send_to_file(ofstream &,string);

    ~Metro() {}
};

#endif // METRO_H
