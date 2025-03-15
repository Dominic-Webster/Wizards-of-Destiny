#include "item.h"

int factor;
string item_code, temp;

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

string get_item(int num){ //sends three items for user to pick
    item_code = "";
    item_code += to_string(rand()%(4+num)); //first item

    do{temp = to_string(rand()%(4+num));}while(temp == item_code);
    item_code += temp; //second item

    do{temp = to_string(rand()%(4+num));}while(temp.at(0) == item_code.at(0) || temp.at(0) == item_code.at(1));
    item_code += temp; //third item

    return item_code;
}
