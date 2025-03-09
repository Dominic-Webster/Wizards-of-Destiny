#include "spell.h"
#include <ctime>
#include <fstream>

void menu();
void battle();
void fight(string factor);
void level_up();
void update();

string X;
int HP, DMG, COINS, FIRE, ICE, POISON, HEAL, PROGRESS;

int main(int argc, char const *argv[]){
    srand(time(0));
    string temp, waste;

    ifstream infile;
    infile.open("player.txt");
    if(infile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    infile >> waste >> temp; HP = stoi(temp);
    infile >> waste >> temp; DMG = stoi(temp);
    infile >> waste >> temp; FIRE = stoi(temp);
    infile >> waste >> temp; ICE = stoi(temp);
    infile >> waste >> temp; POISON = stoi(temp);
    infile >> waste >> temp; HEAL = stoi(temp);
    infile >> waste >> temp; COINS = stoi(temp);
    infile >> waste >> temp; PROGRESS = stoi(temp);
    infile.close();

    string command = ""; //dev commands
    if(argc == 2){
        command = argv[1];
    }
    if(command == "-reset"){
        HP=10; DMG=1; FIRE=0; ICE=0; POISON=0; HEAL=0; COINS=0; PROGRESS = 0;
        update();
    }

    system("clear");
    menu();
}

void menu(){
    do{
        cout << "    - MENU -" << endl << endl;
        cout << " (1): Battle" << endl;
        cout << " (2): Level Up" << endl;
        cout << " (0): [Exit Game]" << endl << endl;
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

void battle(){
    cout << "    - BATTLE -" << endl << endl;
    cout << " Select Level" << endl << endl;
    cout << " (1): Misty Dungeon" << endl;
    if(PROGRESS > 0){cout << " (2): Ruined Castle" << endl;}
    if(PROGRESS > 1){cout << " (3): Mountain of Despair" << endl;}
    cout << " (0): [Menu]" << endl << endl << " -> ";
    cin >> X;
    system("clear");
    if(X == "1"){fight(X);}
    else if(X == "2" && PROGRESS > 0){fight(X);}
    else if(X == "3" && PROGRESS > 1){fight(X);}
    else if(X == "0"){menu();}
    else{battle();}
}

void fight(string factor){
    int health = HP, eHP, damage = DMG, eDMG, fire = FIRE, eFIRE, ice = ICE, eICE, poison = POISON, ePOISON, heal = HEAL, eHEAL;
    
}

void level_up(){
    do{
    cout << "    - LEVEL UP -" << endl << endl;
    cout << "Select stat to increase by 1 [50 coins]" << endl;
    cout << "COINS: " << COINS << endl << endl;
    cout << " (1): Health [" << HP << "]" << endl; 
    cout << " (2): Damage [" << DMG << "]" << endl; 
    cout << " (3): Fire [" << FIRE << "]" << endl; 
    cout << " (4): Ice [" << ICE << "]" << endl; 
    cout << " (5): Posion [" << POISON << "]" << endl;
    cout << " (6): Heal [" << HEAL << "]" << endl;
    cout << " (0): [Menu]" << endl << endl;
    cout << " -> "; 
    cin >> X;
    system("clear");
    }while(stoi(X) < 1 || stoi(X) > 6);

    if(X == "1"){
        if(COINS > 49){COINS -= 50; HP += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else if(X == "2"){
        if(COINS > 49){COINS -= 50; DMG += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else if(X == "3"){
        if(COINS > 49){COINS -= 50; FIRE += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else if(X == "4"){
        if(COINS > 49){COINS -= 50; ICE += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else if(X == "5"){
        if(COINS > 49){COINS -= 50; POISON += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else if(X == "6"){
        if(COINS > 49){COINS -= 50; HEAL += 1; update();}
        else{cout << "- Not Enough Coins" << endl << endl;}
    }
    else{menu();}

    level_up();
}

void update(){
    ofstream outfile;
    outfile.open("player.txt");
    if(outfile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    outfile << "Health: " << HP << endl << "Damage: " << DMG << endl <<
    "Fire: " << FIRE << endl << "Ice: " << ICE << endl << "Poison: " << POISON << endl <<
    "Heal: " << HEAL << endl << "Coins: " << COINS << endl << "Progress: " << PROGRESS << endl;
    outfile.close();
}
