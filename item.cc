#include "item.h"

string Array1[4] = {"012", "103", "320", "132"};
string Array2[6] = {"014", "204", "340", "421", "134", "243"};

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

string get_item(string RoD, string CoP){ //sends three items for user to pick
    if(CoP == "no" && RoD == "no"){ //first four items
        return Array1[rand()%4];
    }
    else if(CoP == "no" && RoD == "yes"){ //first five items
        if(rand()%2 == 0){return Array1[rand()%4];}
        else{return Array2[rand()%6];}
    }
    return "302";
}
