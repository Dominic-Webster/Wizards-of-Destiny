#include "spell.h"
#include "item.h"
#include <ctime>
#include <fstream>
#include <thread>

void menu(); void battle(); void store(); void how_to();
void fight(string factor);
void level_up(); void settings(); void update();
void make_enemy(string factor);
void output_level(string factor);
void show_card(Spell card);
void player(string factor);
void enemy(string factor);
void calculate(Spell card); void calculate_enemy();
void enemy_name(); void pick_item(); void update_items();

string FNAME[20] = {"Yarno", "Belloc", "Soma", "Yeen", "Marcuus", "Liol", "Quand", "Jurno", "Corsto", "Kaimo",
"Wernda", "Helena", "Astan", "Lucia", "Ferdinand", "Orp", "Oogga", "Ray", "Rendolf", "Portian"};
string LNAME[20] = {"Hellfire", "Wedlok", "Hona", "Perf", "Orelius", "The Slayer", "The Butcher", "Doombringer", "The Savage", "The Destroyer",
"Hogtie", "Far-Wanderer", "Oathbreaker", "Kindy", "Wok", "Erp", "King Killer", "Nightwalker", "Pain-Bringer", "Xondoloxa"};
string FNAME2[20] = {"Holga", "Waine", "Harkken", "Folda", "Swinn", "Varis", "Galdaf", "Halfdan", "Eldar", "Roirand",
"Germaine", "Zandar", "Kieran", "Noss", "Theoran", "Juju", "Yymigg", "Deathman", "Cildas", "Inhilla"};
string LNAME2[20] = {"Westbound", "The Dead", "The Lost", "The Old", "The Young", "Gillian", "The Fallen", "Bell", "Jund", "Ungundo",
"The Wise", "The Hopeless", "Hungerer", "Aaros", "Qi", "Theros", "Queen Lover", "Flesh Eater", "Swedle", "Zikolthu"};

Item AoU("Amulet of Undying", "Regain life after each battle", 0, 0), RoL("Ring of Life", "Boost starting health", 0, 0), 
SoP("Staff of Power", "Boost elements", 0, 0), GoS("Gauntlets of Strength", "Boost starting damage", 0, 0), 
RoD("Rune of Death", "Weaken enemy health", 0, 0), CoP("Cloak of Protection", "Reduce elemental damage", 0, 0); //0, 1, 2, 3, 4, 5
int items[6];

Spell CARD1, CARD2, CARD3;
string X, eTYPE, store1, eName, ownRoD, ownCoP;
int HP, DMG, COINS, FIRE, ICE, POISON, HEAL, PROGRESS, eHP, eTempHP, eDMG, TURN, level,
eFIRE, eICE, ePOISON, eHEAL, health, tempHP, damage, fire, ice, poison, heal, game_speed, DIAMONDS;

int main(int argc, char const *argv[]){
    srand(time(0));
    string temp, waste;

    ifstream infile;
    infile.open("player.txt"); //get player info
    if(infile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    infile >> waste >> temp; HP = stoi(temp); infile >> waste >> temp; DMG = stoi(temp);
    infile >> waste >> temp; FIRE = stoi(temp); infile >> waste >> temp; ICE = stoi(temp);
    infile >> waste >> temp; POISON = stoi(temp); infile >> waste >> temp; HEAL = stoi(temp);
    infile >> waste >> temp; COINS = stoi(temp); infile >> waste >> temp; PROGRESS = stoi(temp);
    infile >> waste >> temp; game_speed = stoi(temp); infile >> waste >> temp; store1 = temp; 
    infile >> waste >> temp; DIAMONDS = stoi(temp); infile >> waste >> temp; ownRoD = temp; 
    infile >> waste >> temp; ownCoP = temp;
    infile.close();

    infile.open("item.txt"); //get item info
    if(infile.fail()){cout << "FILE ERROR\n"; exit(0);}
    infile>>waste>>temp>>waste; AoU.setStat(stoi(temp)); AoU.setLevel(stoi(waste));
    infile>>waste>>temp>>waste; RoL.setStat(stoi(temp)); RoL.setLevel(stoi(waste));
    infile>>waste>>temp>>waste; SoP.setStat(stoi(temp)); SoP.setLevel(stoi(waste));
    infile>>waste>>temp>>waste; GoS.setStat(stoi(temp)); GoS.setLevel(stoi(waste));
    infile>>waste>>temp>>waste; RoD.setStat(stoi(temp)); RoD.setLevel(stoi(waste));
    infile>>waste>>temp>>waste; CoP.setStat(stoi(temp)); CoP.setLevel(stoi(waste));
    infile.close();

    string command = ""; //dev commands
    if(argc == 2){command = argv[1];}
    menu();
}

void menu(){ //game menu
    system("clear");
    do{
        cout << " WIZARDS OF DESTINY" << endl << endl;
        cout << "    - MENU -" << endl << endl;
        cout << " (1): Play Game" << endl;
        cout << " (2): Level Up" << endl;
        cout << " (3): Store" << endl;
        cout << " (4): How To Play" << endl;
        cout << " (5): Settings" << endl;
        cout << " (0): [Exit Game]" << endl << endl;
        cout << " -> ";
        cin >> X;
        system("clear");
    }while(stoi(X) < 0 || stoi(X) > 5);

    if(X == "1"){battle();}
    else if(X == "2"){level_up();}
    else if(X == "3"){store();}
    else if(X == "4"){how_to();}
    else if(X == "5"){settings();}
    else{update(); update_items(); exit(0);}
}

void battle(){ //adventure menu
    system("clear");
    cout << "    - PLAY -" << endl << endl;
    cout << " Select Adventure" << endl << endl;
    cout << " (1): Misty Dungeon" << endl;
    if(PROGRESS > 0){cout << " (2): Ruined Castle" << endl;}
    if(PROGRESS > 1){cout << " (3): Mountain of Despair" << endl;}
    cout << " (0): [Menu]" << endl << endl << " -> ";
    cin >> X;
    system("clear");
    if(X == "0"){menu();}
    this_thread::sleep_for(chrono::seconds(1));
    if(X == "1"){fight(X);}
    else if(X == "2" && PROGRESS > 0){fight(X);}
    else if(X == "3" && PROGRESS > 1){fight(X);}
    else{battle();}
}

void fight(string factor){ //fight function
    int random;
    health = tempHP = HP; damage = DMG; fire = FIRE; ice = ICE; poison = POISON; heal = HEAL; TURN = 0; level = 1;
    
    //get starting item
    pick_item();
    if(items[1] == 1){ //Ring of Life
        health += RoL.getStat();
        tempHP = health;
    }
    if(items[3] == 1){ //Gauntlets of Strength
        damage += GoS.getStat();
    }
    if(items[2] == 1){ //Staff of Power
        fire += SoP.getStat();
        ice += SoP.getStat();
        poison += SoP.getStat();
    }
    this_thread::sleep_for(chrono::milliseconds(game_speed));

    //Misty Dungeon
    if(factor == "1"){
        while(level < 21){ //runs through dungeon
            make_enemy(factor);
            enemy_name();
            eTempHP = eHP;
            while(tempHP > 0 && eTempHP > 0){ //runs through battle
                if(TURN == 0){ //player turn
                    player(factor);
                    if(TURN == 2){TURN = 0;} //stuns
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy(factor);
                    TURN = 0;
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << level*10 << " coins!\n" << endl;
                COINS += (level*10);
                random = (rand() % 10);
                if(random == 0){DIAMONDS++;
                cout << " You have found a diamond!\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                battle();
            }
            else{
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage++; cout << "\n Damage increased!\n\n";}
                    else{health++; tempHP++; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice++; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire++; cout << "\n Fire increased!\n\n";}
                    else{poison++; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 2; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){
                    cout << "You've cleared the Misty Dungeon!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 250 Coins\n" << endl;
                    COINS += 250;
                    random = (rand() % 5);
                    if(random == 0){DIAMONDS++;
                    cout << "You have found a diamond!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 0){
                        cout << "Ruined Castle: unlocked!\n" << endl;
                        PROGRESS = 1;
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    battle();
                }
                cout << " Descending further into the dungeon...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0;
            }
        }
    }

    //Ruined Castle
    if(factor == "2"){
        while(level < 21){
            make_enemy(factor);
            eTempHP = eHP;
            while(tempHP > 0 && eTempHP > 0){
                if(TURN == 0){
                    player(factor);
                    if(TURN == 2){TURN = 0;}
                    else{TURN = 1;}
                }
                else{
                    enemy(factor);
                    TURN = 0;
                }
            }
            if(tempHP < 1){
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << level*15 << " coins!\n" << endl;
                COINS += (level*15);
                random = (rand() % 9);
                if(random == 0){DIAMONDS++;
                cout << " You have found a diamond!\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                battle();
            }
            else{
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 2; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 2; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 2; cout << "\n Fire increased!\n\n";}
                    else{poison += 2; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 4; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 350 Coins\n" << endl;
                    COINS += 350;
                    random = (rand() % 4);
                    if(random == 0){DIAMONDS += 2;
                        cout << "You have found 2 diamonds!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 1){
                        cout << "Mountain of Despair: unlocked!\n" << endl;
                        PROGRESS = 2;
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    battle();
                }
                cout << " Descending further into the ruins...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0;
            }
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        while(level < 21){
            make_enemy(factor);
            eTempHP = eHP;
            while(tempHP > 0 && eTempHP > 0){
                if(TURN == 0){
                    player(factor);
                    if(TURN == 2){TURN = 0;}
                    else{TURN = 1;}
                }
                else{
                    enemy(factor);
                    TURN = 0;
                }
            }
            if(tempHP < 1){
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << level*20 << " coins!\n" << endl;
                COINS += (level*20);
                random = (rand() % 8);
                if(random == 0){DIAMONDS += 2;
                cout << " You have found 2 diamonds\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                battle();
            }
            else{
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 4; tempHP += 4; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 4; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 4; cout << "\n Fire increased!\n\n";}
                    else{poison += 4; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n - >";
                    cin >> X;
                    if(X == "1"){damage += 6; cout << "\n Damage increased!\n\n";}
                    else{health += 6; tempHP += 6; cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){
                    cout << "You've cleared the Mountain of Despair!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 500 Coins\n" << endl;
                    COINS += 500;
                    random = (rand() % 4);
                    if(random == 0){DIAMONDS += 2;
                    cout << "You have found 2 diamonds!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    battle();
                }
                cout << " Descending further into the mountain...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0;
            }
        }
    }

}

void player(string factor){ //player turn
    CARD1.get_card(health, damage, fire, ice, poison, heal);
    CARD2.get_card(health, damage, fire, ice, poison, heal);
    CARD3.get_card(health, damage, fire, ice, poison, heal);
    do{
    system("clear");
    output_level(factor);
    cout << "  " << eName;
    if(eTYPE == "Wizard"){cout << " - Evil Wizard: ";}
    else if(eTYPE == "Fire"){cout << " - Fire Mage: ";}
    else if(eTYPE == "Ice"){cout << " - Ice Sorcerer: ";}
    else if(eTYPE == "Necro"){cout << " - Necromancer: ";}
    else{cout << " - Defender: ";}
    cout << "[Health: " << eTempHP << "]" << endl << endl;
    cout << "  You: [Health: " << tempHP << "] [Damage: " << damage << "] [Fire: " << fire << "] [Ice: " <<
    ice << "] [Poison: " << poison << "] [Heal: " << heal << "]\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    cout << " Your turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    cout << " 1) "; show_card(CARD1);
    cout << " 2) "; show_card(CARD2);
    cout << " 3) "; show_card(CARD3);
    cout << "\n -> ";
    cin >> X;
    }while(stoi(X) < 1 || stoi(X) > 3);
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    if(X == "1"){calculate(CARD1);}
    else if(X == "2"){calculate(CARD2);}
    else{calculate(CARD3);}
    this_thread::sleep_for(chrono::milliseconds(game_speed));
}

void enemy(string factor){ //enemy turn
    system("clear");
    output_level(factor);
    cout << "  " << eName;
    if(eTYPE == "Wizard"){cout << " - Evil Wizard: ";}
    else if(eTYPE == "Fire"){cout << " - Fire Mage: ";}
    else if(eTYPE == "Ice"){cout << " - Ice Sorcerer: ";}
    else if(eTYPE == "Necro"){cout << " - Necromancer: ";}
    else{cout << " - Defender: ";}
    cout << "[Health: " << eTempHP << "]" << endl << endl;
    cout << "  You: [Health: " << tempHP << "] [Damage: " << damage << "] [Fire: " << fire << "] [Ice: " <<
    ice << "] [Poison: " << poison << "] [Heal: " << heal << "]\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    cout << " Enemy's turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    calculate_enemy();
    this_thread::sleep_for(chrono::milliseconds(game_speed));
}

void calculate(Spell card){ //calculate player spell results
    string t = card.getType(); int e = card.getEffect();
    if(t == "attack" || t == "fire" || t == "ice" || t == "poison"){
        if(t == "fire" && eTYPE == "Ice"){e++;} //fire defeats ice
        if(t == "fire" && eTYPE == "Fire"){e--;} //fire resistance
        if(t == "ice" && eTYPE == "Fire"){e++;} //ice defeats fire
        if(t == "ice" && eTYPE == "Ice"){e--;} //ice resistance
        if(t == "poison" && eTYPE == "Necro"){e--;} //Necro is poison resistant
        if(t == "poison" && eTYPE == "Defend"){e++;} //weak to poison
        eTempHP -= e;
        if(t == "attack"){cout << endl << " You deal " << e << " damage!\n";}
        else{cout << endl << " You deal " << e << " " << t << " damage!\n";}
    }
    else if(t == "heal"){
        tempHP += e;
        if(tempHP > health){tempHP = health;}
        cout << endl << " You heal yourself for " << e << " health!\n";
    }
    else if(t == "atk-stun"){
        eTempHP -= e; TURN = 2;
        cout << endl << " You stun your enemy, dealing " << e << " damage!\n";
    }
    else{
        eTempHP -= e;
        tempHP += e;
        if(tempHP > health){tempHP = health;}
        cout << endl << " You drain " << e << " life from the enemy!\n";
    }
}

void calculate_enemy(){ //calculate what spell enemy casts
    int factor = rand() % 10;
    if(eTYPE == "Wizard"){
        if(factor < 6){ //attack
            tempHP -= eDMG;
            cout << " " << eName << " deals " << eDMG << " damage!\n";
        }
        else if(factor < 7){ //fire
            tempHP -= (eDMG + eFIRE);
            cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";
        }
        else if(factor < 8){ //ice
            tempHP -= (eDMG + eICE);
            cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";
        }
        else if(factor < 9){ //poison
            tempHP -= (eDMG + ePOISON);
            cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
    }
    else if(eTYPE == "Fire"){
        if(factor < 3){ //attack
            tempHP -= eDMG;
            cout << " " << eName << " deals " << eDMG << " damage!\n";
        }
        else if(factor < 8){ //fire
            tempHP -= (eDMG + eFIRE);
            cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself!\n";
        }
    }
    else if(eTYPE == "Ice"){
        if(factor < 4){ //attack
            tempHP -= eDMG;
            cout << " " << eName << " deals " << eDMG << " damage!\n";
        }
        else{ //ice
            tempHP -= (eDMG + eICE);
            cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";
        }
    }
    else if(eTYPE == "Necro"){
        if(factor < 1){ //attack
            tempHP -= eDMG;
            cout << " " << eName << " deals " << eDMG << " damage!\n";
        }
        else if(factor < 5){ //poison
            tempHP -= (eDMG + ePOISON);
            cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";
        }
        else if(factor < 6){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself!\n";
        }
        else{ //drain
            tempHP -= (1 + ((eDMG + eHEAL) / 2));
            eTempHP += (1 + ((eDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
    else if(eTYPE == "Defend"){
        if(factor < 1){ //attack
            tempHP -= eDMG;
            cout << " " << eName << " deals " << eDMG << " damage!\n";
        }
        else if(factor < 2){ //fire
            tempHP -= (eDMG + eFIRE);
            cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";
        }
        else if(factor < 3){ //ice
            tempHP -= (eDMG + eICE);
            cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";
        }
        else if(factor < 7){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself!\n";
        }
        else{ //drain
            tempHP -= (1 + ((eDMG + eHEAL) / 2));
            eTempHP += (1 + ((eDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
}

void show_card(Spell card){ //display spell
    cout << card.getName() << ": ";
    if(card.getType() == "attack"){
        cout << "Deal " << card.getEffect() << " damage\n";
    }
    else if(card.getType() == "atk-stun"){
        cout << "Deal " << card.getEffect() << " damage and stun the enemy\n";
    }
    else if(card.getType() == "fire"){
        cout << "Deal " << card.getEffect() << " fire damage\n";
    }
    else if(card.getType() == "ice"){
        cout << "Deal " << card.getEffect() << " ice damage\n";
    }
    else if(card.getType() == "poison"){
        cout << "Deal " << card.getEffect() << " poison damage\n";
    }
    else if(card.getType() == "heal"){
        cout << "Gain " << card.getEffect() << " health\n";
    }
    else{
        cout << "Drain " << card.getEffect() << " health from enemy\n";
    }
}

void output_level(string factor){ //show level player is on
    if(factor == "1"){
        cout << "    - MISTY DUNGEON: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Guardian of the Tomb -\n";}
        if(level == 20){cout << "  - Master of the Dungeon -\n";}
    }
    else if(factor == "2"){
        cout << "    - RUINED CASTLE: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Upholder of Justice -\n";}
        if(level == 20){cout << "  - Lord of the Tower -\n";}
    }
    else{
        cout << "    - MOUNTAIN OF DESPAIR: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - GWatcher of the Pass -\n";}
        if(level == 20){cout << "  - Dweller in the Deep -\n";}
    }
}

void make_enemy(string factor){ //generate enemy stats
    //Misty Dungeon
    if(factor == "1"){
        //get enemy type
        int type = (rand() % 4);
        if(type < 2){eTYPE = "Wizard";}
        else if(type == 2){eTYPE = "Fire";}
        else{eTYPE = "Ice";}

        //set stats
        if(level < 5){
            eHP = 4 + (rand() % 5); eDMG = 1 + (rand() % 2);
            eICE = 0; eFIRE = 0; ePOISON = 0; eHEAL = 1;
            if(eTYPE == "Fire"){eFIRE = 1;}
            if(eTYPE == "Ice"){eICE = 1;}
        }
        else if(level < 10){
            eHP = 6 + (rand() % 6); eDMG = 2 + (rand() % 3);
            eICE = (rand() % 2); eFIRE = (rand() % 2); 
            ePOISON = 1; eHEAL = 2;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
        }
        else if(level == 10){ //mini boss
            eHP = 10 + (rand() % 6); eDMG = 4 + (rand() % 4);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eHEAL = 4;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
        }
        else if(level < 15){
            eHP = 8 + (rand() % 6); eDMG = 3 + (rand() % 3);
            eICE = 1 + (rand() % 2); eFIRE = 1 + (rand() % 2); 
            ePOISON = 2; eHEAL = 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
        }
        else if(level < 20){
            eHP = 9 + (rand() % 7); eDMG = 3 + (rand() % 5);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eHEAL = 4;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
        }
        else{ //level 20 final boss
            eHP = 14 + (rand() % 7); eDMG = 5 + (rand() % 5);
            eICE = 3 + (rand() % 2); eFIRE = 3 + (rand() % 2); 
            ePOISON = 3; eHEAL = 4;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
        }
    }

    //Ruined Castle
    if(factor == "2"){
        //get enemy type
        int type = (rand() % 20);
        if(type < 8){eTYPE = "Wizard";}
        else if(type < 13){eTYPE = "Fire";}
        else if(type < 18){eTYPE = "Ice";}
        else{eTYPE = "Necro";}

        //set stats
        if(level < 5){
            eHP = 6 + (rand() % 5); eDMG = 2 + (rand() % 4);
            eICE = 1; eFIRE = 1; ePOISON = 1; eHEAL = 2;
            if(eTYPE == "Fire"){eFIRE = 2;}
            if(eTYPE == "Ice"){eICE = 2;}
            if(eTYPE == "Necro"){ePOISON = 2;}
        }
        else if(level < 10){
            eHP = 6 + (rand() % 7); eDMG = 3 + (rand() % 4);
            eICE = (rand() % 3); eFIRE = (rand() % 3); 
            ePOISON = (rand() % 3); eHEAL = 2;
            if(eTYPE == "Fire"){eFIRE += 1;}
            if(eTYPE == "Ice"){eICE += 1;}
            if(eTYPE == "Necro"){ePOISON += 1;}
        }
        else if(level == 10){ //mini boss
            eHP = 15 + (rand() % 8); eDMG = 4 + (rand() % 4);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            ePOISON = 3 + (rand() % 3); eHEAL = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 15){
            eHP = 10 + (rand() % 6); eDMG = 4 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 20){
            eHP = 11 + (rand() % 7); eDMG = 4 + (rand() % 5);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eHEAL = 4;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
            if(eTYPE == "Necro"){ePOISON += 3;}
        }
        else{ //level 20 final boss
            eHP = 20 + (rand() % 7); eDMG = 7 + (rand() % 5);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            ePOISON = 3 + (rand() % 3); eHEAL = 6;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
            if(eTYPE == "Necro"){ePOISON += 3;}
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        //get enemy type
        int type = (rand() % 20);
        if(type < 2){eTYPE = "Wizard";}
        else if(type < 6){eTYPE = "Fire";}
        else if(type < 10){eTYPE = "Ice";}
        else if(type < 15){eTYPE = "Necro";}
        else{eTYPE = "Defend";}

        //set stats
        if(level < 5){
            eHP = 8 + (rand() % 6); eDMG = 4 + (rand() % 4);
            eICE = 2; eFIRE = 2; ePOISON = 2; eHEAL = 2;
            if(eTYPE == "Fire"){eFIRE = 3;}
            if(eTYPE == "Ice"){eICE = 3;}
            if(eTYPE == "Necro"){ePOISON = 3;}
            if(eTYPE == "Defend"){eHEAL = 4;}
        }
        else if(level < 10){
            eHP = 9 + (rand() % 7); eDMG = 5 + (rand() % 4);
            eICE = 1 + (rand() % 4); eFIRE = 1 + (rand() % 4); 
            ePOISON = 1 + (rand() % 4); eHEAL = 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 6;}
        }
        else if(level == 10){ //mini boss
            eHP = 17 + (rand() % 9); eDMG = 6 + (rand() % 5);
            eICE = 3 + (rand() % 4); eFIRE = 3 + (rand() % 4); 
            ePOISON = 3 + (rand() % 4); eHEAL = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 8;}
        }
        else if(level < 15){
            eHP = 13 + (rand() % 6); eDMG = 5 + (rand() % 5);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 7;}
        }
        else if(level < 20){
            eHP = 15 + (rand() % 7); eDMG = 6 + (rand() % 5);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eHEAL = 6;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
            if(eTYPE == "Necro"){ePOISON += 3;}
            if(eTYPE == "Defend"){eHEAL = 8;}
        }
        else{ //level 20 final boss
            eHP = 25 + (rand() % 8); eDMG = 8 + (rand() % 7);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            ePOISON = 3 + (rand() % 3); eHEAL = 7;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
            if(eTYPE == "Necro"){ePOISON += 3;}
            if(eTYPE == "Defend"){eHEAL = 10;}
        }
    }
}

void level_up(){ //levl up menu
    system("clear");
    do{
    cout << "    - LEVEL UP -" << endl << endl;
    cout << "Select stat to increase by 1" << endl;
    cout << "COINS: " << COINS << endl << endl;
    cout << " (1): Health: " << HP << "   [";
    if(HP < 15){cout << "50 Coins]" << endl;}
    else if(HP < 20){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (2): Damage: " << DMG << "   [";
    if(DMG < 5){cout << "50 Coins]" << endl;}
    else if(DMG < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (3): Fire: " << FIRE << "     [";
    if(FIRE < 5){cout << "50 Coins]" << endl;}
    else if(FIRE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (4): Ice: " << ICE << "      [";
    if(ICE < 5){cout << "50 Coins]" << endl;}
    else if(ICE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (5): Posion: " << POISON << "   [";
    if(POISON < 5){cout << "50 Coins]" << endl;}
    else if(POISON < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (6): Heal: " << HEAL << "     [";
    if(HEAL < 5){cout << "50 Coins]" << endl;}
    else if(HEAL < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}
    cout << " (0): [Menu]" << endl << endl;
    cout << " -> "; 
    cin >> X;
    system("clear");
    }while(stoi(X) < 0 || stoi(X) > 6);
    if(X == "1"){
        if(HP < 15){
            if(COINS > 49){COINS -= 50; HP += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(HP < 20){
            if(COINS > 99){COINS -= 100; HP += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; HP += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "2"){
        if(DMG < 5){
            if(COINS > 49){COINS -= 50; DMG += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(DMG < 10){
            if(COINS > 99){COINS -= 100; DMG += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; DMG += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "3"){
        if(FIRE < 5){
            if(COINS > 49){COINS -= 50; FIRE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(FIRE < 10){
            if(COINS > 99){COINS -= 100; FIRE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; FIRE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "4"){
        if(ICE < 5){
            if(COINS > 49){COINS -= 50; ICE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(ICE < 10){
            if(COINS > 99){COINS -= 100; ICE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; ICE += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "5"){
        if(POISON < 5){
            if(COINS > 49){COINS -= 50; POISON += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(POISON < 10){
            if(COINS > 99){COINS -= 100; POISON += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; POISON += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "6"){
        if(HEAL < 5){
            if(COINS > 49){COINS -= 50; HEAL += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(HEAL < 10){
            if(COINS > 99){COINS -= 100; HEAL += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; HEAL += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else{menu();}

    level_up();
}

void how_to(){ //game instructions
    system("clear");
    cout << " WIZARDS OF DESTINY\n" << endl;
    cout << "  - HOW TO PLAY -\n" << endl;
    cout << "* When you enter an adventure, you start with your base stats\n";
    cout << "* You'll encounter enemies on each level. Enemies grow stronger as levels progress\n";
    cout << "* You take turns casting spells, until you or the enemy are defeated\n";
    cout << "* You get a selection of 3 random spells, which are influenced by your stats\n";
    cout << "* At certain points in the adventure, you can gain upgrades for your stats\n";
    cout << "* When you die, you recieve coins based on your progress in the level\n";
    cout << "* Spend coins in the \"Level Up\" menu to increase your base stats\n";
    cout << "* Continue to battle and level up to become the greatest wizard of all time!\n" << endl;
    cout << "* Now go on an adventure, and find your destiny!\n" << endl;
    cout << " (0): Menu\n\n -> ";
    cin >> X;
    menu();
}

void store(){ //store menu
    do{
        system("clear");
        cout << "  - STORE -\n" << endl;
        cout << "COINS: " << COINS << endl << "DIAMONDS: " << DIAMONDS << endl << endl;
        cout << " (1): Game Speed Increase ";
        if(store1 == "no"){cout << " [20 Diamonds]\n";}
        else{cout << "*Already Purchased*\n";}
        cout << " (2): All Stats +3  [5 Diamonds]\n";
        cout << " (0): Back to Menu\n\n -> ";
        cin >> X;
    }while(stoi(X) < 0 || stoi(X) > 2);
    if(X == "1"){
        if(store1 == "yes"){
            system("clear"); cout << "You already own this item\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{
            if(DIAMONDS > 19){
                DIAMONDS -= 20; store1 = "yes"; game_speed = 500;
                update(); store();
            }
            else{
                system("clear"); cout << "You don't have enough diamonds\n";
                this_thread::sleep_for(chrono::seconds(1)); store();
            }
        }
    }
    else if(X == "2"){
        if(DIAMONDS > 4){
            DIAMONDS -= 5; HP += 3; DMG += 3; FIRE += 3; ICE +=3; POISON += 3; HEAL += 3;
            update(); store();
        }
        else{
            system("clear"); cout << "You don't have enough diamonds\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
    }
    else{menu();}
}

void settings(){ //settings menu
    do{
        system("clear");
        cout << "  - SETTINGS -\n" << endl;
        cout << " (1): Change Game Speed [";
        if(game_speed == 1000){cout << "normal]";}
        else{cout << "fast]";}
        if(store1 == "no"){cout << " *Unlock in store*";}
        cout << endl << " (2): Reset Save *Permanent*";
        cout << endl << " (0): Back to Menu\n\n -> ";
        cin >> X;
    }while(stoi(X) < 0 || stoi(X) > 2);
    if(X == "1"){
        if(store1 == "yes"){
            if(game_speed == 1000){game_speed = 500;}
            else{game_speed = 1000;}
            update(); settings();
        }
        else{
            system("clear"); cout << "Unlock this settting in store\n";
            this_thread::sleep_for(chrono::seconds(1)); settings();
        }
    }
    else if(X == "2"){
        do{
            system("clear");
            cout << " RESET SAVE\n" << endl;
            cout << "Are you sure you want to reset? All progress will be lost\n" << endl;
            cout << " (1): Reset\n (0): Back to Settings\n\n -> ";
            cin >> X;
        }while(stoi(X) < 0 || stoi(X) > 1);
        if(X == "1"){
            HP=10; DMG=1; FIRE=0; ICE=0; POISON=0; HEAL=0; COINS=0; PROGRESS = 0;
            game_speed = 1000; store1 = "no"; update(); settings(); DIAMONDS = 0;
        }
        else{settings();}
    }
    else{menu();}
}

void update(){ //send player data to text file
    ofstream outfile;
    outfile.open("player.txt");
    if(outfile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    outfile << "Health: " << HP << endl << "Damage: " << DMG << endl <<
    "Fire: " << FIRE << endl << "Ice: " << ICE << endl << "Poison: " << POISON << endl <<
    "Heal: " << HEAL << endl << "Coins: " << COINS << endl << "Progress: " << PROGRESS << 
    endl << "Gamespeed: " << game_speed << endl << "store1: " << store1 << endl << 
    "Diamonds: " << DIAMONDS << endl << "Rod: " << ownRoD << endl << "CoP: " << ownCoP << endl;
    outfile.close();
}

void update_items(){ //send item data to text file
    ofstream outfile;
    outfile.open("item.txt");
    if(outfile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    outfile << "AoU " << AoU.getStat() << " " << AoU.getLevel() << endl;
    outfile << "RoL " << RoL.getStat() << " " << RoL.getLevel() << endl;
    outfile << "SoP " << SoP.getStat() << " " << SoP.getLevel() << endl;
    outfile << "GoS " << GoS.getStat() << " " << GoS.getLevel() << endl;
    outfile << "RoD " << RoD.getStat() << " " << RoD.getLevel() << endl;
    outfile << "CoP " << CoP.getStat() << " " << CoP.getLevel() << endl;
    outfile.close();
}

void enemy_name(){ //generate enemy name
    eName = "";
    int random;
    random = (rand() % 2);
    if(random == 0){
        random = (rand() % 20);
        eName += FNAME[random];
    }
    else{
        random = (rand() % 20);
        eName += FNAME2[random];
    }
    eName += " ";
    random = (rand() % 2);
    if(random == 0){
        random = (rand() % 20);
        eName += LNAME[random];
    }
    else{
        random = (rand() % 20);
        eName += LNAME2[random];
    }
}

void pick_item(){ //get new item
    for(int i = 0; i < 6; i++){
        items[i] = 0;
    }
    Item x, y, z;
    int random, a, b, c;
    if(ownCoP == "no" && ownRoD == "no"){ //picks 3 items
        random = rand()%2;
        if(random == 0){a = 0; x = AoU;} else{a = 1; x = RoL;} //first item
        random = rand()%2;
        if(random == 0 && a == 0){b = 1; y = RoL;} //second item
        else if(random == 0 && a == 1){b = 0; y = AoU;}
        else{ b = 2; y = SoP;}
        random = rand()%2;
        if(random == 0 && b != 2){c = 2; z = SoP;} //third item
        else if(random == 0 && b == 2){c = 3; z = GoS;}
        else if(random == 1 && b == 1 && a == 0){c = 2; z = SoP;}
        else{c = 3; z = GoS;}
    }
    do{
        system("clear");
        cout << " Select Starting Item\n" << endl;
        cout << " (1): "; x.print();
        cout << "\n (2): "; y.print();
        cout << "\n (3): "; z.print();
        cout << "\n -> ";
        cin >> X;
    }while(stoi(X) < 1 || stoi(X) > 3);
    if(X == "1"){items[a] = 1;}
    else if(X == "2"){items[b] = 1;}
    else{items[c] = 1;}
}
