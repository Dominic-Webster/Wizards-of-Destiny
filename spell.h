#ifndef SPELL
#define SPELL

#include <iostream>
using namespace std;

class Spell{
    public:
        Spell();
        Spell(string nm, string tp, int eff);
        string getName(){return name;};
        string getType(){return type;};
        int getEffect(){return effect;};
        void get_card(int hp, int dmg, int fire, int ice, int poison, int electric, int heal);
    private:
        string name, type;
        int effect;
};

#endif