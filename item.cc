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

string get_item(string RoD, string CoP){ //sends three items for user to pick
    int random;
    string result = "";
    if(CoP == "no" && RoD == "no"){ //first four items
        random = rand()%4;
        if(random < 2){result += "0";} else{result += "1";} //first item
        random = rand()%6;
        if(random < 3 && result == "0"){result += "1";} //second item
        else if(random < 3 && result == "1"){result += "0";}
        else{result += "2";}
        random = rand()%2;
        if(random == 0 && result.at(1) != '2'){result += "2";} //third item
        else if(random == 0 && result.at(1) == '2'){result += "3";}
        else if(random == 1 && result.at(1) == '1' && result.at(0) == '0'){result += "2";}
        else{result += "3";}
    }
    return result;
}
