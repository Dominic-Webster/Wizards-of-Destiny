#include "item.h"

string Array1[4] = {"012", "103", "320", "132"};
string Array2[6] = {"014", "204", "340", "421", "134", "243"};
string Array3[6] = {"015", "250", "350", "521", "513", "235"};
string Array4[4] = {"540", "154", "245", "435"};
int factor;

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
    else if(CoP == "no" && RoD == "yes"){ //only RoD owned
        if(rand()%2 == 0){return Array1[rand()%4];}
        else{return Array2[rand()%6];}
    }
    else if(CoP == "yes" && RoD == "no"){ //only CoP owned
        if(rand()%2 == 0){return Array1[rand()%4];}
        else{return Array3[rand()%6];}
    }
    else{ //RoD and CoP owned
        factor = rand()%4;
        if(factor == 0){return Array1[rand()%4];}
        else if(factor == 1){return Array2[rand()%6];}
        else if(factor == 2){return Array3[rand()%6];}
        else{return Array4[rand()%4];}
    }
    return "302";
}
