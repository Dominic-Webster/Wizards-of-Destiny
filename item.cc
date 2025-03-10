#include "item.h"

Item::Item(){name = "item"; effect = "N/A"; level = 0; stat = 0;}

Item::Item(string nm, string eff, int stt, int lvl){
    name = nm;
    effect = eff;
    stat = stt;
    level = lvl;
}

void Item::print(){
    cout << name << ": " << effect << " (Level: " << level << ")";
}

bool Item::operator==(Item x){
    return (name == x.name);
}
