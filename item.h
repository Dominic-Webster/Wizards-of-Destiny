#ifndef ITEM
#define ITEM

#include <iostream>
using namespace std;

class Item{
    public:
        Item();
        Item(string nm, string eff, int stt, int lvl);
        void print();
        bool operator ==(Item x);
        void setName(string nm){name = nm;};
        void setEffect(string eff){effect = eff;};
        void setStat(int stt){stat = stt;};
        void setLevel(int lvl){level = lvl;};
        string getName(){return name;};
        string getEffect(){return effect;};
        int getStat(){return stat;};
        int getLevel(){return level;}
    private:
        string name, effect;
        int stat, level;
};

string get_item(int num);
string extra_item(int num, int list[]);

#endif