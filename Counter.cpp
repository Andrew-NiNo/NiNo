#include "Counter.h"

Counter::Counter() {}

void Counter::calculator1(string str, int y)
{
    str1 = str;
    if(y)
        x++;
}

void Counter::calculator2(string str, int x)
{
    str2 = str;
    y += x;
}

void Counter::show(ofstream &of)
{
    of<<str1<<x<<endl;
    of<<str2<<y<<endl;
}
