#include "Metro.h"

#include <iostream> //
#include <string>


using namespace std;

unordered_map <Metro::Mode,unordered_map<string,string>> my_map;
vector<string>line_coord;
vector<string>station;


bool ac_dc = true;                                      ///Реализуем логическую переменную для работы с циклом

Metro::Metro()                                          ///В конструкторе заполняем контейнер unordered_map значениями
{

    my_map.insert({START,{{tags.start_begin,tags.start_stop}}});
    my_map.insert({LINE,{{tags.find_begin,tags.find_stop}}});
    my_map.insert({COORDINATES,{{tags.coordinates_begin,tags.coordinates_stop}}});
    my_map.insert({STATION,{{tags.station_begin,tags.station_stop}}});
    my_map.insert({METHOD_1,{{"",""}}});                                        ///Есть возможность заполнения новыми тегами
    my_map.insert({METHOD_2,{{"",""}}});

}

void Metro::replacement(Mode form)                          ///Этим членом-функцией происодит заполнение дополнительными тегами
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

PAIR Metro::search_block(string &line,string::size_type indx,Mode form)         ///Это основной блок для поиска с проверками
{
    string start, finish, str;
    string::size_type tmp_indx;

    MAP::const_iterator got = my_map.find(form);              ///Ищем по полученному значению перечислителя нужное значение тегов

    if ( got == my_map.end() )
        cout << "not found ";
    else
        for(const auto& w : got->second)
        {
            start = w.first ;
            finish = w.second ;
        }

    if(indx)                                                ///Прорабатываются варианты поиска
    {
        line = line.substr(indx);
    }

    tmp_indx = line.find(start);

    if (string::npos == tmp_indx)                           ///Если поиск невозможен, очищаем содержимое строки
    {                                                       ///меняем условие для цикла и выводим пустые значения
        line.clear();
        ac_dc = false;
        return make_pair(line,0);
    }
    else
    {
        str = line.substr(tmp_indx+start.size());           ///В обратном случае проходит поиск и возврат нужной подстроки
        indx = str.find(finish);
        str = str.substr(0,indx);
    }

    return make_pair(str,tmp_indx);
}

void Metro::send_to_file(ofstream &of,string line)          ///Метод для дозаполнения выходных данных
{

    of<<'\t'<<line<<endl;
}

PAIR Metro::find_coordinates(string &line,string::size_type indx,Mode form) ///Член-функция для поиска координат
{
    if(line.empty())
        return make_pair(line,indx);                                    ///Если строка пустая, передаем ее дальше

    auto output = search_block(line,indx,form);                         ///Ищем нужную подстроку

    string tmp, word,tmp_c;
    int flag = 0;
    int flag_c = 0;

    stringstream s_str(output.first);
    while(s_str>>word)                                      ///Отправляем ее в поток и работаем в нем с условными символами
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
            line_coord.back() += tmp_c;                     ///Результат отправляем в вектор
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
            line_coord.push_back(word);                     ///Результат отправляем в вектор
            tmp.clear();
        }
    }
    return make_pair(output.first,output.second);
}

PAIR Metro::find_station(string &line,string::size_type indx,Mode form)     ///Член-функция для поиска станций
{
    if(line.empty())
        return make_pair(line,indx);                               ///Проверка строки на 0

    line = line.substr(indx);

    indx = line.find(tags.correct);                                ///В этой реализации стоит доп. поиск correct

    auto output = search_block(line,indx,form);                     ///Ищем нужную подстроку

    stringstream s_str;
    s_str << output.first;                                         ///Через поток в цикле отправляем найденные значения в вектор

    string tmp_stream;

    while(s_str)
    {
        getline(s_str,tmp_stream,',');
        station.push_back(tmp_stream);
    }
    indx = station.size();

    return make_pair(line,indx);
}

void Metro::print(vector<string> &v1,vector<string> &v2, ofstream & fs)       /// Выводим в файл найденные значения
{

    for(int i=0; i<v1.size(); i++)
    {

        fs<<"\t "<<v1.operator[](i)<<"   "<<v2.operator[](i)<<'\n';
    };
    v1.clear();                                                             ///С очисткой векторов
    v2.clear();
}



