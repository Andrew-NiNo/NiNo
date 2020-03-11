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

    Metro City;                                    ///������� ��� ������� ������� Metro � Counter(��� ������ ������� � log ����)
    Counter Log;

    ifstream inf(argv[1]);                         ///������� ������ �������� �� cmd � ��������� ����� � ����� ��� ��������
                                                   ///� ������� ����� � ������� �� �����
    if (!inf)
    {
        cerr << "Whoops..,file could not be opened." << endl;
        exit(1);
    }

    string svg, temp;

    while(inf)
    {
        getline(inf, temp);                         ///������� �� ������ ������
        svg+=temp;
    };
                                                    ///���� ������ �������� � ������ � ������� � ���� ������ ��������� �����
    auto start = City.search_block(svg,0,Metro::START);

    ofstream outf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".svg");
    ofstream logf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".log");

    City.send_to_file(outf,start.first);

    do
    {
        auto line = City.search_block(svg,0,Metro::LINE);           ///���� ��������� ����(����� �����)

        City.send_to_file(outf,line.first);
        Log.calculator1("Line: ",line.second);                      ///������� ����

        auto coord = City.find_coordinates(svg, line.second,Metro::COORDINATES);    ///���� ����������� �������

        auto stat = City.find_station(svg, coord.second,Metro::STATION);            ///���� �������

        City.print(station,line_coord,outf);                                ///���������� ���������� � ����
        Log.calculator2("Station: ",stat.second);                       ///������� �������

        svg = stat.first;                                               ///�������������� ������ ��� ��������� �������� �����
    }
    while(ac_dc);

    Log.show(logf);                                             ///�������� � log ���� ������� ���������

    return 0;
};

