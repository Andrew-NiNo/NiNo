#include <iostream> //
#include <fstream>  //
#include <string>   //
#include <vector>   //
#include <sstream>  //
#include <istream>     //

#define PAIR pair<string,string::size_type>

using namespace std;

vector<string> station;
vector<string> line_coord;

ofstream outf("Dubai_Test.txt");


PAIR find_city(const string & s){

    string::size_type n;
    string search_word ="docname=\"";
    string city;

    n = s.find(search_word);
    city = s.substr(n+search_word.size());
    n = city.find_first_of(".");
    city = city.substr(0,n);

    outf<<"City:  "<<city<<'\n';

return make_pair(city,n);
}

PAIR find_line( string & s){

    string::size_type n;
    string search_word ="label=\"path";
    string line;

    n = s.find(search_word);

    if (string::npos == n){
        line.clear();
    }
    else{
    line=s.substr(n+search_word.size(),2);

    outf<<'\n'<<"Line:   "<<line<<'\n'<<'\n';
    }

return make_pair(line,n);
}

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

    string tmp, word,tmp_c;
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
return make_pair(s_sub,n);
}

void print(const vector<string> &s,const vector<string> &p){

    for(int i=0; i<s.size();i++){

        outf<<s.operator[](i)<<" "<<p.operator[](i)<<'\n';
    };
}

int main() {

    ifstream inf("dubai2.svg");

	if (!inf){
		cerr << "Whoops..,file could not be opened." << endl;
		exit(1);
	}

    string svg, temp;

    while(inf){
        getline(inf, temp);
        svg+=temp;
    };

        find_city(svg);

    do{

        auto p = find_line(svg);

        if(p.first.empty()) break;

        auto p1 = find_coordinates(svg, p.second);

        coord_vector(p1.first);

        auto p2 = station_vector(p1.first,p1.second);

        print(station,line_coord);

        station.clear();
        line_coord.clear();
        svg = p2.first;

    } while(1);

return 0;
}
