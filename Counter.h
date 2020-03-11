#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED


class Counter
{
private:
    int x = 0;
    int y = 0;
    string str1;
    string str2;

public:

    Counter();

    void calculator1(string,int);
    void calculator2(string,int);
    void show(ofstream &);

    ~Counter() {};
};

#endif // COUNTER_H_INCLUDED
