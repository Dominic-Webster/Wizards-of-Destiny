#include "spell.h"
#include <ctime>

void menu();
void battle();
void level_up();

string X;

int main(int argc, char const *argv[]){
    srand(time(0));
    system("clear");
    menu();
}

void menu(){
    do{
        cout << "    - MENU -" << endl;
        cout << " (1): Battle" << endl;
        cout << " (2): Level Up" << endl;
        cout << " (3): [Exit Game]" << endl << endl;
        cout << " -> ";
        cin >> X;
        system("clear");
    }while(stoi(X) < 1 || stoi(X) > 3);

    if(X == "1"){
        battle();
    }
    else if(X == "2"){
        level_up();
    }
    else{exit(0);}
}
