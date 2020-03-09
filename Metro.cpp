#include "Metro.h"

#include <iostream> //
#include <string>


using namespace std;

unordered_map <string,unordered_map<string,string>> my_map;
vector<string>line_coord;
vector<string>station;

bool ac_dc ;

Metro::Metro() {}

void Metro::replacement(string & replace_string,MAP & my_map)
{
    my_map.insert({"start",{{tags.start_begin,tags.start_stop}}});

}

PAIR Metro::search_block(string &line,string::size_type n)
{

    string::size_type p;
    string str;

    if(n)
    {
        line=line.substr(n);
    }

    n = line.find(tags.coordinates_begin);
    line = line.substr(n+tags.coordinates_begin.size());
    n = line.find(tags.coordinates_stop);
    str = line.substr(0,n);

    return make_pair(line,n);
}

void Metro::send_to_stream(ofstream &of,string str)
{

    of<<'\t'<<str<<endl;
}

PAIR Metro::start(string &line, string::size_type n)
{
    string city;

    n = line.find(tags.start_begin);
    city = line.substr(n+tags.start_begin.size());
    n = city.find(tags.start_stop);
    city = city.substr(0,n);

    return make_pair(city,n);
}

PAIR Metro::find_or_stop(string &s,ofstream &logf)
{

    string::size_type n, p;
    string line;

    n = s.find(tags.find_begin);

    if (string::npos == n)
    {
        line.clear();
    }
    else
    {
        line=s.substr(n+tags.find_begin.size());
        p = line.find(tags.find_stop);
        line=line.substr(0,p);
    }
    return make_pair(line,n);
}

PAIR Metro::find_coordinates(string &line,string::size_type n)
{
    auto output = search_block(line,n);

    string tmp, word,tmp_c;
    int flag = 0;
    int flag_c = 0;

    stringstream s_str(output.first);
    while(s_str>>word)
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
            line_coord.back() += tmp_c;
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
            line_coord.push_back(word);
            tmp.clear();
        }
    }
    return make_pair(output.first,output.second);
}

PAIR Metro::find_station(string &s,string::size_type p)
{

    string s_sub=s.substr(p);
    string::size_type n;
    string str;

    n = s_sub.find(tags.station_begin);
    str=s_sub.substr(n+tags.station_begin.size());

    n = str.find(tags.station_stop);
    str=str.substr(n+tags.station_stop.size());

    n = str.find(tags.correct);
    str=str.substr(0, n);

    stringstream ss;
    ss<<str;

    string str_stream;

    while(ss)
    {
        getline(ss,str_stream,',');
        station.push_back(str_stream);
    }
    n = station.size();
    return make_pair(s_sub,n);
}

void Metro::print(vector<string> &s,vector<string> &p, ofstream & fs)
{

    for(int i=0; i<s.size(); i++)
    {

        fs<<"\t "<<s.operator[](i)<<"  "<<p.operator[](i)<<'\n';
    };
}



//void Metro::show()const{
//
//    cout<<" City: "<<this<<'\n';
//
////             for(string::size_type i =0; i < m_line.size(); i++) {
////                    cout<<m_line<<"   Height "<< m_line[i].height <<"  Width "<<m_line[i].width<<'\n';
//            };




//
//    bool City::operator[](const string& name){
//
//        for(auto &ref: m_line){
//            if(ref.first==name)
//                return true;
//            }
//            double height;
//            double width;
//            cin>>height;
//            cin>>width;
//
//        Subwey_Station temp{name,height,width};
//
//        m_line.emplace(pair<string,Subwey_Station>("",temp));
//
//         show();
//         return false;
//};


