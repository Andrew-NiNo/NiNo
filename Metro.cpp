#include "Metro.h"

#include <iostream>
#include <string>


using namespace std;

unordered_map <Metro::Mode,unordered_map<string,string>> my_map;
vector<string>line_coord;
vector<string>station;


bool ac_dc = true;                                      ///We implement a boolean variable for working with a loop

Metro::Metro()                                          ///In the constructor, fill the unordered_map container with values
{

    my_map.insert({START,{{tags.start_begin,tags.start_stop}}});
    my_map.insert({LINE,{{tags.find_begin,tags.find_stop}}});
    my_map.insert({COORDINATES,{{tags.coordinates_begin,tags.coordinates_stop}}});
    my_map.insert({STATION,{{tags.station_begin,tags.station_stop}}});
    my_map.insert({METHOD_1,{{"",""}}});                                        ///It is possible to fill in new tags
    my_map.insert({METHOD_2,{{"",""}}});

}

void Metro::replacement(Mode form)                          ///This function member fills in additional tags
{
    string start, finish;
    MAP::const_iterator got = my_map.find(form);

    if ( got == my_map.end() )
        cout << "Not found ";
    else
    {
        cout<<"  Vvedite start..."<<'\n';
        cin>>start;
        cout<<"  Vvedite finish..."<<'\n';
        cin>>finish;
        my_map[form][start]=finish;
    }
}
                                                                ///This is the main member function for searching with checks.
PAIR Metro::search_block(Mode form,string &line,string::size_type indx)
{
    string start, finish, str;
    string::size_type tmp_indx;

    MAP::const_iterator got = my_map.find(form);              ///We search for the desired tag value using the enumerator value.

    if ( got == my_map.end() )
        cout << "not found ";
    else
        for(const auto& w : got->second)
        {
            start = w.first ;
            finish = w.second ;
        }

    if(indx)                                                ///Search options are under developed
    {
        line = line.substr(indx);
    }

    tmp_indx = line.find(start);

    if (string::npos == tmp_indx)                           ///If search is not possible, clear the contents of the string
    {
        line.clear();                                       ///Change the condition for the loop and print empty values
        ac_dc = false;
        return make_pair(line,0);
    }
    else
    {
        str = line.substr(tmp_indx+start.size());           ///Otherwise, it searches and returns the required substring
        indx = str.find(finish);
        str = str.substr(0,indx);
    }

    return make_pair(str,tmp_indx);
}

PAIR Metro::search_block(Mode form,string &line)
{
    auto out = search_block(form,line,0) ;
    return make_pair(out.first,out.second);
}

void Metro::send_to_file(ofstream &of,string line)                     ///Member function to fill the output
{

    of<<'\t'<<line<<endl;
}

PAIR Metro::find_coordinates(string &line,string::size_type indx,Mode form) ///Member function to search for coordinates
{
    if(line.empty())
        return make_pair(line,indx);                                    ///If the line is empty, pass it on

    auto output = search_block(form,line,indx);                         ///We are looking for the desired substring

    string tmp, word,tmp_c;
    int flag = 0;
    int flag_c = 0;

    stringstream s_str(output.first);
    while(s_str>>word)                                    ///We send it to the stream and work in it with conditional characters
    {

        if(word=="c"||flag_c>0 && flag_c<4)
        {

            word.push_back(' ');
            flag_c == 0? tmp_c = word: tmp_c += word;
            flag_c++;
            continue;
        }
        if(flag_c == 4)
        {
            tmp_c = " " + tmp_c;
            line_coord.back() += tmp_c;                     ///The result is sent to the vector
            flag_c = 0;
            tmp_c = "";
        }
        if(word=="M"||word=="m"||word=="L"||word=="l")
        {

            word.push_back(' ');
            tmp = word;
            continue;
        }
        word = tmp+word ;
        flag++;
        if (flag == 1)
        {
            flag = 0;
            line_coord.push_back(word);                     ///The result is sent to the vector
            tmp.clear();
        }
    }
    return make_pair(output.first,output.second);
}

PAIR Metro::find_station(string &line,string::size_type indx,Mode form)     ///Member function to search for stations
{
    if(line.empty())
        return make_pair(line,indx);                               ///If the line is empty, pass it on

    line = line.substr(indx);

    indx = line.find(tags.correct);                                ///Additional search is required here correct

    auto output = search_block(form,line,indx);                     ///We are looking for the desired substring

    stringstream s_str;
    s_str << output.first;                               ///Through the stream in the loop we send the found values to the vector

    string tmp_stream;

    while(s_str)
    {
        getline(s_str,tmp_stream,',');
        station.push_back(tmp_stream);
    }
    indx = station.size();

    return make_pair(line,indx);
}

void Metro::print(vector<string> &v1,vector<string> &v2, ofstream & fs)       ///Member function prints found values to file
{

    for(int i=0; i<v1.size(); i++)
    {

        fs<<"\t "<<v1.operator[](i)<<"   "<<v2.operator[](i)<<'\n';
    };
    v1.clear();                                                             ///With cleaning vectors
    v2.clear();
}



