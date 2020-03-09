#ifndef METRO_H
#define METRO_H

#include <unordered_map>

using namespace std;

#define PAIR pair<string,string::size_type>
#define MAP unordered_map <string,unordered_map<string,string>>

class Metro
{
private:

    struct Tags
    {
        string start_begin = "docname=\"";
        string start_stop = ".";
        string find_begin = "label=\"path";
        string find_stop = "\">";
        string coordinates_begin = "d=\"";
        string coordinates_stop = "\"";
        string station_begin = "<desc";
        string station_stop = ">";
        string correct = "<";
    } tags;


public:
    Metro();

    void replacement(string &,MAP &);

    PAIR search_block(string &,string::size_type);
    PAIR start(string &,string::size_type);
    PAIR find_or_stop(string &,ofstream &);
    PAIR find_coordinates(string &,string::size_type);
    PAIR find_station(string &,string::size_type);
    void print(vector<std::string> &,vector<std::string> &,ofstream &);

    void send_to_stream(ofstream &,string);
    friend class Counter;


    ~Metro() {}
};

#endif // METRO_H
