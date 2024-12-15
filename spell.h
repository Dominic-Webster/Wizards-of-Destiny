#ifndef SPELL
#define SPELL

#include <iostream>
using namespace std;

class Spell{
    public:
        Spell();
        Spell(string nm, string tp, int eff);
        string getName();
        string getType();
        int getEffect();
    private:
        string name, type;
        int effect;
};

#endif