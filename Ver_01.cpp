#include <iostream> //
#include <fstream>  //
#include <string>   //
#include <vector>   //
#include <sstream>  //
#include <istream>     //

#define PAIR pair<string,string::size_type>

using namespace std;


vector<string> station;


PAIR find_city(string const& s){

    string::size_type n;
    string search_word ="docname=\"";
    string str;

    n = s.find(search_word);
    str = s.substr(n+search_word.size());
    n = str.find_first_of(".");
    str = str.substr(0,n);

return make_pair(str,n);
}

PAIR find_line(string const& s){

    string::size_type n;
    string search_word ="label=\"path";
    string line;

    n = s.find(search_word);
    line=s.substr(n+search_word.size(),2);

return make_pair(line,n);
}

struct Line{

    string tag;
    Line(string tag): tag(tag){}
};

vector<Line> line_coord;

PAIR find_coordinates(string const& s,string::size_type p){


    string s_sub=s.substr(p);
    string::size_type n;
    string search_word ="d=\"";
    string str;

    n = s_sub.find(search_word);
    str=s_sub.substr(n+search_word.size());

return make_pair(str,n);
}

void coord_vector(string const& s){

    int fragm_length = s.find_first_of('"');
    string string_coord = s.substr(0,fragm_length);

    string tmp, word;
    int flag = 0;

    stringstream str(string_coord);
    while(str>>tmp){

        tmp += word ;
        flag++;

        if (flag == 1){
            flag = 0;
        line_coord.push_back(Line(tmp));
        tmp = "";
        }
    }
}

PAIR station_vector(string const& s,string::size_type p){

    string s_sub=s.substr(p);
    string::size_type n;
    string search_word ="<desc";
    string str;

    n = s_sub.find(search_word);
    str=s_sub.substr(n+search_word.size());
    search_word =">";
    n = str.find(search_word);
    str=str.substr(n+search_word.size());

    n = str.find_first_of("<");
    str=str.substr(0, n);

    stringstream ss;
    ss<<str;

    string str_stream;
    while(ss){
        getline(ss,str_stream,',');
        station.push_back(str_stream);
    }

return make_pair(str,n);
}

void print(string const &s,string::size_type p ){
    if (p == string::npos) {
        cout << "not found\n";
    } else {
        cout << "found: " << s.substr(p) << '\n';
    }
}

int main() {

   ifstream inf("dubai1.svg");

	if (!inf){
		cerr << "Whoops..,file could not be opened." << endl;
		exit(1);
	}

    string svg, temp;

    while(inf){
        getline(inf, temp);
        svg+=temp;
    };

    auto c = find_city(svg);
    cout<<"\n City:  "<<c.first<<'\n';

    auto p = find_line(svg);
    cout<<"\n Line:  "<<p.first<<'\n';

    auto p1 = find_coordinates(svg, p.second);

    coord_vector(p1.first);

        for(auto & ref: line_coord)
        cout<<ref.tag<<'\n';

    auto p2 = station_vector(p1.first,p1.second);

     for(auto &ref: station){
        cout<<ref<<" ";
     };


return 0;
}
