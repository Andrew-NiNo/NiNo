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

    Metro City;                                    ///Создаем два объекта классов Metro и Counter(для выводя зачений в log файл)
    Counter Log;

    ifstream inf(argv[1]);                         ///Ожидаем нужный аргумент из cmd с указанным путем к файлу для парсинга
                                                   ///И создаем поток с данными из файла
    if (!inf)
    {
        cerr << "Whoops..,file could not be opened." << endl;
        exit(1);
    }

    string svg, temp;

    while(inf)
    {
        getline(inf, temp);                         ///Создаем из потока строку
        svg+=temp;
    };
                                                    ///Ищем нужное название в строке и создаем с этим именем исходящие файлы
    auto start = City.search_block(svg,0,Metro::START);

    ofstream outf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".svg");
    ofstream logf("C:\\Users\\Hp\\Dropbox\\hello\\Work\\Test\\Ver_03\\CREATED "+ start.first + ".log");

    City.send_to_file(outf,start.first);

    do
    {
        auto line = City.search_block(svg,0,Metro::LINE);           ///Ищем возможные пути(линии метро)

        City.send_to_file(outf,line.first);
        Log.calculator1("Line: ",line.second);                      ///Считаем пути

        auto coord = City.find_coordinates(svg, line.second,Metro::COORDINATES);    ///Ищем коордиинаты станций

        auto stat = City.find_station(svg, coord.second,Metro::STATION);            ///Ищем станции

        City.print(station,line_coord,outf);                                ///Результаты отправляем в файл
        Log.calculator2("Station: ",stat.second);                       ///Считаем станции

        svg = stat.first;                                               ///Переопределяем строку для следующей итерации цикла
    }
    while(ac_dc);

    Log.show(logf);                                             ///Печатаем в log файл зачения счетчиков

    return 0;
};

