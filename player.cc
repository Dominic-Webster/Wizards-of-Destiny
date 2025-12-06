#include "player.h"
#include <fstream>
using namespace std;

Player::Player(){
    string temp, waste;

    ifstream infile;
    infile.open("player.txt"); //get player info
    if(infile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    infile >> waste >> temp; HP = stoi(temp); 
    infile >> waste >> temp; DMG = stoi(temp);
    infile >> waste >> temp; FIRE = stoi(temp); 
    infile >> waste >> temp; ICE = stoi(temp);
    infile >> waste >> temp; POISON = stoi(temp); 
    infile >> waste >> temp; ELECTRIC = stoi(temp);
    infile >> waste >> temp; HEAL = stoi(temp); 
    infile >> waste >> temp; CRITC = stoi(temp); 
    infile >> waste >> temp; CRITD = stoi(temp); 
    infile >> waste >> temp; DODGE = stoi(temp); 
    infile >> waste >> temp; SHIELD = stoi(temp); 
    infile >> waste >> temp; LUCK = stoi(temp);
    infile >> waste >> temp; COINS = stoi(temp); 
    infile >> waste >> temp; PROGRESS = stoi(temp);
    infile >> waste >> temp; game_speed = stoi(temp); 
    infile >> waste >> temp; store1 = temp; 
    infile >> waste >> temp; store2 = temp; 
    infile >> waste >> temp; DIAMONDS = stoi(temp); 
    infile >> waste >> temp; numItems = stoi(temp); 
    infile >> waste >> temp; ENDLESS = stoi(temp);
    infile >> waste >> temp; REBIRTH = stoi(temp); 
    infile >> waste >> temp; BOON = stoi(temp);
    infile >> waste >> temp; boon1 = temp; 
    infile >> waste >> temp; boon2 = temp;
    infile >> waste >> temp; boon3 = temp; 
    infile >> waste >> temp; boon4 = temp; 
    infile >> waste >> temp; COMPANION = stoi(temp); 
    infile >> waste >> temp; comp1 = temp; 
    infile >> waste >> temp; comp2 = temp; 
    infile >> waste >> temp; comp3 = temp; 
    infile >> waste >> temp; comp4 = temp; 
    infile >> waste >> temp; comp5 = temp;
    infile.close();
}

void Player::update(){
    ofstream outfile;
    outfile.open("player.txt");
    if(outfile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    outfile << "Health: " << HP << endl << "Damage: " << DMG << endl <<
    "Fire: " << FIRE << endl << "Ice: " << ICE << endl << "Poison: " << POISON << endl << "Electric: " <<
    ELECTRIC << endl << "Heal: " << HEAL << endl << "Crit-Chance: " << CRITC << endl << "Crit-Damage: " << 
    CRITD << endl << "Dodge: " << DODGE << endl << "Shield: " << SHIELD << endl << "Luck: " <<
    LUCK << endl << "Coins: " << COINS << endl << "Progress: " << PROGRESS << 
    endl << "Gamespeed: " << game_speed << endl << "store1: " << store1 << endl << "store2: " << store2 <<
    endl << "Diamonds: " << DIAMONDS << endl << "Items: " << numItems << endl << "Endless: " << ENDLESS << 
    endl << "Rebirth: " << REBIRTH << endl << "Boon: " << BOON << endl << "boon1: " << boon1 << 
    endl << "boon2: " << boon2 << endl << "boon3: " << boon3 << endl << "boon4: " << boon4 << endl << 
    "Companion: " << COMPANION << endl << "comp1: " << comp1 << endl << "comp2: " << comp2 << endl << 
    "comp3: " << comp3 << endl << "comp4: " << comp4 << endl << "comp5: " << comp5 << endl;
    outfile.close();
}
