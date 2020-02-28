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

vector<string> line_coord;

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

    string tmp="", word,tmp_c="";
    int flag = 0;
    int flag_c = 0;

    stringstream str(string_coord);
    while(str>>word){

        if(word=="c"||flag_c>0 && flag_c<4){

        word.push_back(' ');
        flag_c == 0? tmp_c = word: tmp_c += word;
            flag_c++; continue;
        }
        if(flag_c == 4){
            tmp_c = " " + tmp_c;
            line_coord.back() += tmp_c;
            flag_c = 0;
            tmp_c = "";
        }
        if(word=="M"||word=="m"||word=="L"||word=="l"){

            word.push_back(' ');
            tmp = word; continue;
        }
        word = tmp+word ;
        flag++;
        if (flag == 1){
            flag = 0;
        line_coord.push_back(word);
        tmp.clear();
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

    ofstream outf("Dubai_Test.txt");

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
    outf<<"\n City:  "<<c.first<<'\n';

    auto p = find_line(svg);
    outf<<"\n Line:  "<<p.first<<'\n';

    auto p1 = find_coordinates(svg, p.second);

    coord_vector(p1.first);

//        for(auto & ref: line_coord)
//        cout<<ref<<'\n';

    auto p2 = station_vector(p1.first,p1.second);

//     for(auto &ref: station){
//        outf<<ref<<'\n';

        for(int i=0; i<station.size();i++){

        outf<<station.operator[](i)<<" "<<line_coord.operator[](i)<<'\n';

        };

return 0;
}
