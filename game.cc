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
void player(string factor); void item_shop();
void enemy(string factor); void reset_items();
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
int items[6]; //keeps track of which items player is using

Spell CARD1, CARD2, CARD3;
string X, eTYPE, store1, eName, ownRoD, ownCoP;
int HP, DMG, COINS, FIRE, ICE, POISON, HEAL, PROGRESS, eHP, eTempHP, eDMG, TURN, level,
eFIRE, eICE, ePOISON, eHEAL, health, tempHP, damage, fire, ice, poison, heal, game_speed, 
DIAMONDS, CRITC, CRITD, critc, critd, eCRITC, eCRITD, DODGE, dodge, eDODGE;

int main(int argc, char const *argv[]){
    srand(time(0));
    string temp, waste;

    ifstream infile;
    infile.open("player.txt"); //get player info
    if(infile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    infile >> waste >> temp; HP = stoi(temp); infile >> waste >> temp; DMG = stoi(temp);
    infile >> waste >> temp; FIRE = stoi(temp); infile >> waste >> temp; ICE = stoi(temp);
    infile >> waste >> temp; POISON = stoi(temp); infile >> waste >> temp; HEAL = stoi(temp);
    infile >> waste >> temp; CRITC = stoi(temp); infile >> waste >> temp; CRITD = stoi(temp);
    infile >> waste >> temp; DODGE = stoi(temp);
    infile >> waste >> temp; COINS = stoi(temp); infile >> waste >> temp; PROGRESS = stoi(temp);
    infile >> waste >> temp; game_speed = stoi(temp); infile >> waste >> temp; store1 = temp; 
    infile >> waste >> temp; DIAMONDS = stoi(temp); infile >> waste >> temp; ownRoD = temp; 
    infile >> waste >> temp; ownCoP = temp;
    infile.close();

    infile.open("item.txt"); //get item info
    if(infile.fail()){cout << "FILE ERROR\n"; exit(0);}
    infile>>waste>>temp>>waste; AoU.setStat(stoi(temp)); AoU.setLevel(stoi(waste)); //Amulet of Undying
    infile>>waste>>temp>>waste; RoL.setStat(stoi(temp)); RoL.setLevel(stoi(waste)); //Ring of Life
    infile>>waste>>temp>>waste; SoP.setStat(stoi(temp)); SoP.setLevel(stoi(waste)); //Staff of Power
    infile>>waste>>temp>>waste; GoS.setStat(stoi(temp)); GoS.setLevel(stoi(waste)); //Gauntlets of Strength
    infile>>waste>>temp>>waste; RoD.setStat(stoi(temp)); RoD.setLevel(stoi(waste)); //Rune of Death
    infile>>waste>>temp>>waste; CoP.setStat(stoi(temp)); CoP.setLevel(stoi(waste)); //Cloak of Protection
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
    }while(X < "0" || X > "5");

    if(X == "1"){battle();} //play the game
    else if(X == "2"){level_up();} //go to level up menu
    else if(X == "3"){store();} //go to store
    else if(X == "4"){how_to();} //how to play
    else if(X == "5"){settings();} //go to settings
    else{update(); update_items(); exit(0);} //save and exit
}

void battle(){ //adventure menu
    do{
        system("clear");
        cout << "    - PLAY -" << endl << endl;
        cout << " Select Adventure" << endl << endl;
        cout << " (1): Misty Dungeon" << endl;
        if(PROGRESS > 0){cout << " (2): Ruined Castle" << endl;} //only show after misty dungeon completed
        if(PROGRESS > 1){cout << " (3): Mountain of Despair" << endl;} //only show after ruined castle completed
        cout << " (0): [Menu]" << endl << endl << " -> ";
        cin >> X;
    }while(X < "0" || X > "3");
    if(X == "0"){menu();}
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    if(X == "1"){fight(X);} //misty dungeon
    else if(X == "2" && PROGRESS > 0){fight(X);} //ruined castle
    else if(X == "3" && PROGRESS > 1){fight(X);} //mountain of despair
}

void fight(string factor){ //fight function
    int random;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    health = tempHP = HP; damage = DMG; fire = FIRE; ice = ICE; poison = POISON; heal = HEAL; TURN = 0; level = 1;
    critc = CRITC; critd = CRITD; dodge = DODGE;
    
    pick_item(); //get starting item
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
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly

    //Misty Dungeon
    if(factor == "1"){
        while(level < 21){ //runs through dungeon
            make_enemy(factor); //create this level's enemy
            enemy_name(); //create the enemy name
            eTempHP = eHP; //set enemy temp health
            while(tempHP > 0 && eTempHP > 0){ //runs through battle
                if(TURN == 0){ //player turn
                    player(factor);
                    if(TURN == 2){TURN = 0;} //when enemy is stunned
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
                this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
                cout << " Reward: " << level*5 << " coins!\n" << endl; //give player reward
                COINS += (level*5);
                random = (rand() % 4); //player has chance to get a diamond
                if(random == 0){DIAMONDS++;
                cout << " You have found a diamond!\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
                update(); battle(); //back to play menu
            }
            else{ //proceed to next level
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;} //make sure doesn't go over max hp
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){ //level 5 cleared gives stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage++; cout << "\n Damage increased!\n\n";}
                    else{health++; tempHP+=2; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice++; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire++; cout << "\n Fire increased!\n\n";}
                    else{poison++; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 4; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //dungeon cleared
                    cout << "You've cleared the Misty Dungeon!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 250 Coins\n" << endl; //completion reward
                    COINS += 250;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS++;
                    cout << "You have found a diamond!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 0){ //if first time completing
                        cout << "Ruined Castle: unlocked!\n" << endl;
                        PROGRESS = 1; //unlock ruined castle
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    update(); battle(); //save and return to play menu
                }
                cout << " Descending further into the dungeon...\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0; //set turn to players, increase dungeon level
            }
        }
    }

    //Ruined Castle
    if(factor == "2"){
        while(level < 21){ //runs until reaches end
            make_enemy(factor); //create enemy for the level
            enemy_name(); //enemy name
            eTempHP = eHP; //set temp health
            while(tempHP > 0 && eTempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player(factor);
                    if(TURN == 2){TURN = 0;} //enemy stunned
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
                cout << " Reward: " << level*10 << " coins!\n" << endl; //give reward
                COINS += (level*10);
                random = (rand() % 4); //diamond chance
                if(random == 0){DIAMONDS++;
                cout << " You have found a diamond!\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;} //make sure health doesn't go over
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 4; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 2; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 2; cout << "\n Fire increased!\n\n";}
                    else{poison += 2; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 3; tempHP += 6; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 500 Coins\n" << endl; //player reward
                    COINS += 500;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS += 2;
                        cout << "You have found 2 diamonds!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 1){ //first time completed
                        cout << "Mountain of Despair: unlocked!\n" << endl;
                        PROGRESS = 2; //unlock mountain of despaiir
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    update(); battle(); //save and exit to menu
                }
                cout << " Descending further into the ruins...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0; //go to next level, set turn to player
            }
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        while(level < 21){ //runs to end of adventure
            make_enemy(factor); //create enemy for level
            enemy_name(); //enemy name
            eTempHP = eHP; //set enemy temp helth
            while(tempHP > 0 && eTempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player(factor);
                    if(TURN == 2){TURN = 0;} //enemy stunned
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
                cout << " Reward: " << level*20 << " coins!\n" << endl; //player reward
                COINS += (level*20);
                random = (rand() % 4); //diamond chance
                if(random == 0){DIAMONDS += 2;
                cout << " You have found 2 diamonds\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player defeated level
                system("clear");
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                if(items[0] == 1 && level != 20 && tempHP < health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    tempHP += AoU.getStat();
                    if(tempHP > health){tempHP = health;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 4; tempHP += 6; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost\n 2) Fire Boost\n 3) Poison Boost\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 4; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 4; cout << "\n Fire increased!\n\n";}
                    else{poison += 4; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost\n 2) Health Boost\n\n - >";
                    cin >> X;
                    if(X == "1"){damage += 6; cout << "\n Damage increased!\n\n";}
                    else{health += 6; tempHP += 9; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //mountain cleared
                    cout << "You've cleared the Mountain of Despair!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: 750 Coins\n" << endl; //player reward
                    COINS += 750;
                    random = (rand() % 2);
                    if(random == 0){DIAMONDS += 2;
                    cout << "You have found 2 diamonds!\n" << endl;}
                    if(PROGRESS == 2){PROGRESS = 3;} //if first time completed
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and go to menu
                }
                cout << " Descending further into the mountain...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                level++; TURN = 0; //level increase and turn set to player
            }
        }
    }

}

void player(string factor){ //player turn
    CARD1.get_card(health, damage, fire, ice, poison, heal); //generate first spell
    CARD2.get_card(health, damage, fire, ice, poison, heal); //generate second spell
    CARD3.get_card(health, damage, fire, ice, poison, heal); //generate third spell
    do{
    system("clear");
    output_level(factor); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    cout << " Your turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    cout << " 1) "; show_card(CARD1); //these show the spells
    cout << " 2) "; show_card(CARD2);
    cout << " 3) "; show_card(CARD3);
    cout << "\n -> ";
    cin >> X;
    }while(X < "1" || X > "3"); //until player selects spell
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    if(X == "1"){calculate(CARD1);} //calculate spell player chose
    else if(X == "2"){calculate(CARD2);}
    else{calculate(CARD3);}
    this_thread::sleep_for(chrono::milliseconds(game_speed));
}

void enemy(string factor){ //enemy turn
    system("clear");
    output_level(factor); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    cout << " Enemy's turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    calculate_enemy(); //calculate what spell enemy casts
    this_thread::sleep_for(chrono::milliseconds(game_speed));
}

void calculate(Spell card){ //calculate player spell results
    string t = card.getType(); int e = card.getEffect();
    if(t == "attack" || t == "fire" || t == "ice" || t == "poison"){ //attack spell
        if(t == "fire" && eTYPE == "Ice"){e+=fire;} //ice sorcerer is weak to fire
        if(t == "fire" && eTYPE == "Fire"){e-=fire;} //fire mage is fire resistant
        if(t == "ice" && eTYPE == "Fire"){e+=ice;} //fire mage is weak to ice
        if(t == "ice" && eTYPE == "Ice"){e-=ice;} //ice sorcerer is ice resistant
        if(t == "poison" && eTYPE == "Necro"){e-=poison;} //Necro is poison resistant
        if(t == "poison" && eTYPE == "Defend"){e+=poison;} //defender is weak to poison
        if(rand()%100 < eDODGE){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            eTempHP -= e; //decrease enemy health
            if(t == "attack"){cout << endl << " You deal " << e << " damage!\n";} //show results
            else{cout << endl << " You deal " << e << " " << t << " damage!\n";}} //show results
    }
    else if(t == "heal"){ //healing spell
        tempHP += e;
        if(tempHP > health){tempHP = health;} //can't go over max
        cout << endl << " You heal yourself for " << e << " health!\n";
    }
    else if(t == "atk-stun"){ //attack(stun) spell
        if(rand()%100 < eDODGE){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            eTempHP -= e; TURN = 2; //deal damage, trigger stun
            cout << endl << " You stun your enemy, dealing " << e << " damage!\n";}
    }
    else{ //drain spell
        eTempHP -= e; //damage
        tempHP += e; //heal
        if(tempHP > health){tempHP = health;} //can't go over max
        cout << endl << " You drain " << e << " life from the enemy!\n";
    }
}

void calculate_enemy(){ //calculate what spell enemy casts
    int factor = rand() % 10;
    if(eTYPE == "Wizard"){ //evil wizard
        if(factor < 6){ //attack
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";} //player dodges
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; 
                    cout << " " << eName << " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(factor < 7){ //fire
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " <<
                    eName << " deals " << eDMG + eCRITD + eFIRE << " *critiacl* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
        }
        else if(factor < 8){ //ice
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eICE << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
        }
        else if(factor < 9){ //poison
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + ePOISON);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + ePOISON + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}}
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
    }
    else if(eTYPE == "Fire"){ //fire mage
        if(factor < 3){ //attack
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(factor < 8){ //fire
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eFIRE << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself!\n";
        }
    }
    else if(eTYPE == "Ice"){ //ice sorcerer
        if(factor < 4){ //attack
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName << 
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else{ //ice
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eICE + eDMG + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
        }
    }
    else if(eTYPE == "Necro"){ //necromancer
        if(factor < 1){ //attack
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(factor < 5){ //poison
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + ePOISON);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << ePOISON + eDMG + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}}
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
    else if(eTYPE == "Defend"){ //defender
        if(factor < 1){ //attack
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(factor < 2){ //fire
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eFIRE + eCRITD << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
        }
        else if(factor < 3){ //ice
            if(rand()%100 < dodge){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eICE + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
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
    if(card.getType() == "attack"){ //attack spell
        cout << "Deal " << card.getEffect() << " damage\n";
    }
    else if(card.getType() == "atk-stun"){ //atack(stun) spell
        cout << "Deal " << card.getEffect() << " damage and stun the enemy\n";
    }
    else if(card.getType() == "fire"){ //fire spell
        cout << "Deal " << card.getEffect() << " fire damage\n";
    }
    else if(card.getType() == "ice"){ //ice spell
        cout << "Deal " << card.getEffect() << " ice damage\n";
    }
    else if(card.getType() == "poison"){ //poison spell
        cout << "Deal " << card.getEffect() << " poison damage\n";
    }
    else if(card.getType() == "heal"){ //healing spell
        cout << "Gain " << card.getEffect() << " health\n";
    } 
    else{ //drain spell
        cout << "Drain " << card.getEffect() << " health from enemy\n";
    }
}

void output_level(string factor){ //show level player is on
    if(factor == "1"){ //misty dungeon
        cout << "    - MISTY DUNGEON: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Guardian of the Tomb -\n";}
        if(level == 20){cout << "  - Master of the Dungeon -\n";}
    }
    else if(factor == "2"){ //ruined castle
        cout << "    - RUINED CASTLE: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Upholder of Justice -\n";}
        if(level == 20){cout << "  - Lord of the Tower -\n";}
    }
    else{ //mountain of despair
        cout << "    - MOUNTAIN OF DESPAIR: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Watcher of the Pass -\n";}
        if(level == 20){cout << "  - Dweller in the Deep -\n";}
    }
    cout << "  " << eName; //show enemy name
    if(eTYPE == "Wizard"){cout << " - Evil Wizard: ";} //these show enemy type
    else if(eTYPE == "Fire"){cout << " - Fire Mage: ";}
    else if(eTYPE == "Ice"){cout << " - Ice Sorcerer: ";}
    else if(eTYPE == "Necro"){cout << " - Necromancer: ";}
    else{cout << " - Defender: ";}
    cout << "[Health: " << eTempHP << "]" << endl << endl; //show enemy health
    cout << "  You: [Health: " << tempHP << "] [Damage: " << damage << "] [Fire: " << fire << "] [Ice: " <<
    ice << "] [Poison: " << poison << "]" << endl <<"       [Heal: " << heal <<
    "] [Crit Chance: " << critc << "%] [Crit Damage: " << critd << "] [Dodge: " <<
    DODGE << "%]\n" << endl; //player info
}

void make_enemy(string factor){ //generate enemy stats
    //Misty Dungeon
    if(factor == "1"){
        //get enemy type
        int type = (rand() % 4);
        if(type < 2){eTYPE = "Wizard";} //evil wizard
        else if(type == 2){eTYPE = "Fire";} //fire mage 
        else{eTYPE = "Ice";} //ice sorcerer
        eCRITC = 10; //crit chance
        eDODGE = 5; //dodge chance

        //set stats based on adventure level
        if(level < 5){ //levels 1-4
            eHP = 4 + (rand() % 5); eDMG = 1 + (rand() % 2);
            eICE = 0; eFIRE = 0; ePOISON = 0; eHEAL = 1; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE = 1;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 1;} //ice sorcerer buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 8 + (rand() % 6); eDMG = 1 + (rand() % 3);
            eICE = (rand() % 2); eFIRE = (rand() % 2); 
            ePOISON = 1; eHEAL = 2; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE += 1;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 1;} //ice sorcerer buff
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 15 + (rand() % 6); eDMG = 3 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eHEAL = 5; eCRITD = 2; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 2;} //ice sorcerer buff
        }
        else if(level < 15){ //levels 11-14
            eHP = 12 + (rand() % 6); eDMG = 2 + (rand() % 3);
            eICE = 1 + (rand() % 2); eFIRE = 1 + (rand() % 2); 
            ePOISON = 2; eHEAL = 4; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE += 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 2;} //ice sorcerer buff
        }
        else if(level < 20){ //levels 15-19
            eHP = 15 + (rand() % 7); eDMG = 3 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eHEAL = 5; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 3;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 3;} //ice sorcerer buff
        }
        else{ //level 20 final boss
            eHP = 22 + (rand() % 10); eDMG = 4 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eHEAL = 7; eCRITD = 4; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 3;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 3;} //ice sorcerer buff
        }
    }

    //Ruined Castle
    if(factor == "2"){
        //get enemy type
        int type = (rand() % 20);
        if(type < 8){eTYPE = "Wizard";} //evil wizard
        else if(type < 13){eTYPE = "Fire";} //fire mage
        else if(type < 18){eTYPE = "Ice";} //ice sorcerer
        else{eTYPE = "Necro";} //necromancer

        if(eTYPE == "Wizard"){eCRITC = 15;} //crit chance
        else{eCRITC = 10;}
        eDODGE = 7; //dodge chance

        //set stats
        if(level < 5){ //levels 1-4
            eHP = 8 + (rand() % 5); eDMG = 2 + (rand() % 3);
            eICE = 1; eFIRE = 1; ePOISON = 1; eHEAL = 4; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE = 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 2;} //ice sorcerer buff
            if(eTYPE == "Necro"){ePOISON = 2;} //necromancer buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 12 + (rand() % 8); eDMG = 3 + (rand() % 3);
            eICE = (rand() % 3); eFIRE = (rand() % 3); 
            ePOISON = (rand() % 3); eHEAL = 5; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE += 1;}
            if(eTYPE == "Ice"){eICE += 1;}
            if(eTYPE == "Necro"){ePOISON += 1;}
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 20 + (rand() % 8); eDMG = 3 + (rand() % 4);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 8; eCRITD = 3; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 15){ //levels 11-14
            eHP = 16 + (rand() % 6); eDMG = 3 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 6; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 20){ //levels 15-19
            eHP = 20 + (rand() % 7); eDMG = 4 + (rand() % 3);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eHEAL = 7; eCRITD = 4;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else{ //level 20 final boss
            eHP = 30 + (rand() % 10); eDMG = 4 + (rand() % 5);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eHEAL = 9; eCRITD = 5; eCRITC += 3;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Ice"){eICE += 3;}
            if(eTYPE == "Necro"){ePOISON += 3;}
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        //get enemy type
        int type = (rand() % 20);
        if(type < 2){eTYPE = "Wizard";} //evil wizard
        else if(type < 6){eTYPE = "Fire";} //fire mage
        else if(type < 10){eTYPE = "Ice";} //ice sorcerer
        else if(type < 15){eTYPE = "Necro";} //necromancer
        else{eTYPE = "Defend";} //defender

        if(eTYPE == "Wizard"){eCRITC = 20;} //crit chance
        else{eCRITC = 12;}
        if(eTYPE == "Defend"){eDODGE = 15;} //dodge chance
        else{eDODGE = 10;}

        //set stats
        if(level < 5){ //levels 1-4
            eHP = 20 + (rand() % 6); eDMG = 3 + (rand() % 4);
            eICE = 2; eFIRE = 2; ePOISON = 2; eHEAL = 4; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE = 3;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 3;} //ice sorcerer buff
            if(eTYPE == "Necro"){ePOISON = 3;} //necromancer buff
            if(eTYPE == "Defend"){eHEAL = 8; eHP += 5; eDMG -= 2;} //defender buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 24 + (rand() % 7); eDMG = 4 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 6; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 1;}
            if(eTYPE == "Ice"){eICE += 1;}
            if(eTYPE == "Necro"){ePOISON += 1;}
            if(eTYPE == "Defend"){eHEAL = 10; eHP += 7; eDMG-= 2;}
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 35 + (rand() % 8); eDMG = 5 + (rand() % 5);
            eICE = 1 + (rand() % 4); eFIRE = 1 + (rand() % 4); 
            ePOISON = 1 + (rand() % 4); eHEAL = 10; eCRITD = 4; eCRITC += 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 14; eHP += 8; eDMG -= 1;}
        }
        else if(level < 15){ //levels 11-14
            eHP = 28 + (rand() % 6); eDMG = 4 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eHEAL = 8; eCRITD = 4;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 10; eHP += 9; eDMG -= 1;}
        }
        else if(level < 20){ //levels 15-19
            eHP = 32 + (rand() % 7); eDMG = 4 + (rand() % 4);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eHEAL = 10; eCRITD = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 12; eHP += 10; eDMG -= 1;}
        }
        else{ //level 20 final boss
            eHP = 45 + (rand() % 11); eDMG = 4 + (rand() % 5);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            ePOISON = 3 + (rand() % 3); eHEAL = 12; eCRITD = 6; eCRITC += 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 15; eHP += 15; eDMG -= 2;}
        }
    }

    if(items[4] == 1){eHP--;} //rune of death
}

void level_up(){ //level up menu
    system("clear");
    do{
    cout << "    - LEVEL UP -" << endl << endl;
    cout << "Select stat to increase by 1" << endl;
    cout << "COINS: " << COINS << endl << endl;
    cout << " (1): Health: " << HP << "        ["; //health and varied cost
    if(HP < 11){cout << "25 Coins]" << endl;}
    else if(HP < 15){cout << "50 Coins]" << endl;}
    else if(HP < 20){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (2): Damage: " << DMG << "        ["; //damage and varied cost
    if(DMG < 2){cout << "25 Coins]" << endl;}
    else if(DMG < 5){cout << "50 Coins]" << endl;}
    else if(DMG < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (3): Fire: " << FIRE << "          ["; //fire and varied cost
    if(FIRE < 5){cout << "50 Coins]" << endl;}
    else if(FIRE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (4): Ice: " << ICE << "           ["; //ice and varied cost
    if(ICE < 5){cout << "50 Coins]" << endl;}
    else if(ICE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (5): Posion: " << POISON << "        ["; //poison and varied cost
    if(POISON < 5){cout << "50 Coins]" << endl;}
    else if(POISON < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (6): Heal: " << HEAL << "          ["; //heal and varied cost
    if(HEAL < 5){cout << "50 Coins]" << endl;}
    else if(HEAL < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (7): Crit Chance: " << CRITC << "%  ["; //crit chance and varied cost
    if(CRITC < 11){cout << "50 Coins]" << endl;}
    else if(CRITC < 21){cout << "75 Coins]" << endl;}
    else{cout << "150 Coins]" << endl;}

    cout << " (8): Crit Damage: " << CRITD << "   ["; //crit damage and varied cost
    if(CRITD < 7){cout << "50 Coins]" << endl;}
    else if(CRITD < 11){cout << "150 Coins]" << endl;}
    else{cout << "300 Coins]" << endl;}

    cout << " (0): [Menu]" << endl << endl;
    cout << " -> "; 
    cin >> X;
    system("clear");
    }while(X < "0" || X > "8");
    if(X == "1"){ //health
        if(HP < 11){ 
            if(COINS > 24){COINS -= 25; HP += 1; update();}
            else{ //too poor
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(HP < 15){ 
            if(COINS > 49){COINS -= 50; HP += 1; update();}
            else{ //too poor
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(HP < 20){
            if(COINS > 99){COINS -= 100; HP += 1; update();}
            else{ //too poor
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 199){COINS -= 200; HP += 1; update();}
            else{ //too poor
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
    }
    else if(X == "2"){ //damage
        if(DMG < 2){
            if(COINS > 24){COINS -= 25; DMG += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(DMG < 5){
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
    else if(X == "3"){ //fire
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
    else if(X == "4"){ //ice
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
    else if(X == "5"){ //poison
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
    else if(X == "6"){ //heal
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
    else if(X == "7"){ //crit chance
        if(CRITC < 11){
            if(COINS > 49){COINS -= 50; CRITC += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(CRITC < 21){
            if(COINS > 74){COINS -= 75; CRITC += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(CRITC < 60){
            if(COINS > 149){COINS -= 150; CRITC += 1; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up();
        }
    }
    else if(X == "8"){ //crit damage
        if(CRITD < 7){
            if(COINS > 49){COINS -= 50; CRITD += 2; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else if(CRITD < 11){
            if(COINS > 149){COINS -= 150; CRITD += 2; update();}
            else{
                system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); level_up();
            }
        }
        else{
            if(COINS > 299){COINS -= 300; CRITD += 2; update();}
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
    cout << "* You may select an item to give you an advantage on your run\n";
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
        if(store1 == "no"){cout << " [20 Diamonds]\n";} //can be bought
        else{cout << "*Already Purchased*\n";} //already bought
        cout << " (2): Stat Boost  [5 Diamonds]\n";
        cout << " (3): Buy Items\n";
        cout << " (0): Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "3");
    if(X == "1"){
        if(store1 == "yes"){ //already own game speed upgrade
            system("clear"); cout << "You already own this item\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{
            if(DIAMONDS > 19){ //buy game speed upgrade
                DIAMONDS -= 20; store1 = "yes"; game_speed = 500;
                update(); store();
            }
            else{ //too poor
                system("clear"); cout << "You don't have enough diamonds\n";
                this_thread::sleep_for(chrono::seconds(1)); store();
            }
        }
    }
    else if(X == "2"){
        if(DIAMONDS > 4){ //buy stat boost
            DIAMONDS -= 5; HP += 2; DMG += 2; FIRE += 2; ICE +=2; POISON += 2; HEAL += 2;
            update(); system("clear"); cout << " Stats have been boosted\n"; 
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{ //too poor
            system("clear"); cout << "You don't have enough diamonds\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
    }
    else if(X == "3"){item_shop();}
    else{menu();}
}

void settings(){ //settings menu
    do{
        system("clear");
        cout << "  - SETTINGS -\n" << endl;
        cout << " (1): Change Game Speed [";
        if(game_speed == 1000){cout << "normal]";}
        else{cout << "fast]";}
        if(store1 == "no"){cout << " *Unlock in store*";} //shows if setting needs bought
        cout << endl << " (2): Reset Save *Permanent*";
        cout << endl << " (0): Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "2");
    if(X == "1"){
        if(store1 == "yes"){ //if game speed has been bought
            if(game_speed == 1000){game_speed = 500;}
            else{game_speed = 1000;}
            update(); settings();
        }
        else{ //setting needs bought
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
        }while(X < "0" || X > "1");
        if(X == "1"){ //reset save
            HP=10; DMG=1; FIRE=0; ICE=0; POISON=0; HEAL=0; COINS=0; PROGRESS = 0; CRITC = 5; CRITD = 2;
            game_speed = 1000; store1 = "no"; DIAMONDS = 0; ownRoD = "no"; ownCoP = "no"; DODGE = 5;
            update(); reset_items(); settings();
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
    "Heal: " << HEAL << endl << "Crit-Chance: " << CRITC << endl << "Crit-Damage: " << 
    CRITD << endl << "Dodge: " << DODGE << endl << "Coins: " << COINS << endl << "Progress: " << PROGRESS << 
    endl << "Gamespeed: " << game_speed << endl << "store1: " << store1 << endl << 
    "Diamonds: " << DIAMONDS << endl << "RoD: " << ownRoD << endl << "CoP: " << ownCoP << endl;
    outfile.close();
}

void update_items(){ //send item data to text file
    ofstream outfile;
    outfile.open("item.txt");
    if(outfile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    outfile << "AoU " << AoU.getStat() << " " << AoU.getLevel() << endl; //Amulet of Undying
    outfile << "RoL " << RoL.getStat() << " " << RoL.getLevel() << endl; //Ring of Life
    outfile << "SoP " << SoP.getStat() << " " << SoP.getLevel() << endl; //Staff of Power
    outfile << "GoS " << GoS.getStat() << " " << GoS.getLevel() << endl; //Gauntlets of Strength
    outfile << "RoD " << RoD.getStat() << " " << RoD.getLevel() << endl; //Rune of Death
    outfile << "CoP " << CoP.getStat() << " " << CoP.getLevel() << endl; //Cloak of Protection
    outfile.close();
}

void reset_items(){
    AoU.setStat(1); AoU.setLevel(1);
    RoL.setStat(2); RoL.setLevel(1);
    SoP.setStat(1); SoP.setLevel(1);
    GoS.setStat(2); GoS.setLevel(1);
    RoD.setStat(1); RoD.setLevel(1);
    CoP.setStat(1); CoP.setLevel(1);
    update_items();
}

void enemy_name(){ //generate enemy name
    eName = "";
    int random;
    random = (rand() % 2);
    if(random == 0){ //first first name list
        random = (rand() % 20);
        eName += FNAME[random];
    }
    else{ //second first name list
        random = (rand() % 20);
        eName += FNAME2[random];
    }
    eName += " ";
    random = (rand() % 2);
    if(random == 0){ //first last name list
        random = (rand() % 20);
        eName += LNAME[random];
    }
    else{ //second last name list
        random = (rand() % 20);
        eName += LNAME2[random];
    }
}

void pick_item(){ //get new item
    for(int i = 0; i < 6; i++){ //reset items
        items[i] = 0;
    }
    Item x, y, z; int a, b, c; string d, e, f;
    string info = get_item(ownRoD, ownCoP); //return three items
    d = info.at(0); e = info.at(1); f = info.at(2);
    a = stoi(d); b = stoi(e); c = stoi(f);
    if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
    else if(a == 3){x = GoS;} else{x = RoD;}
    if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
    else if(b == 3){y = GoS;} else{y = RoD;}
    if(c == 0){z = AoU;} else if(c == 1){z = RoL;} else if(c == 2){z = SoP;} 
    else if(c == 3){z = GoS;} else{z = RoD;}
    do{
        system("clear");
        cout << " Select Starting Item\n" << endl;
        cout << " (1): "; x.print();
        cout << "\n (2): "; y.print();
        cout << "\n (3): "; z.print();
        cout << "\n\n -> ";
        cin >> X;
    }while(X < "1" || X > "3");
    if(X == "1"){items[a] = 1;}
    else if(X == "2"){items[b] = 1;}
    else{items[c] = 1;}
}

void item_shop(){
    do{
        system("clear");
        cout << "  - ITEM SHOP -\n" << endl;
        cout << "DIAMONDS: " << DIAMONDS << endl << endl;
        cout << " (1): Rune of Death ";
        if(ownRoD == "no"){cout << " [5 Diamonds]\n";} //can be bought
        else{cout << "*Already Owned*\n";} //already bought
        cout << " (0): Back to Store\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "1"){
        if(ownRoD == "yes"){ //already own item
            system("clear"); cout << "You already own this item\n";
            this_thread::sleep_for(chrono::seconds(1)); item_shop();
        }
        else{
            if(DIAMONDS > 4){ //buy game speed upgrade
                DIAMONDS -= 5; ownRoD = "yes";;
                update(); item_shop();
            }
            else{ //too poor
                system("clear"); cout << "You don't have enough diamonds\n";
                this_thread::sleep_for(chrono::seconds(1)); item_shop();
            }
        }
    }
    else{store();}
}
