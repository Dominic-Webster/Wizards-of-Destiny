/**
 * WIZARDS OF DESTINY
 * @author: Dominic Webster
 * @version: 3.2.0
 * @brief: controls the main game
 */

#include "spell.h"
#include "colors.h"
#include "item.h"
#include <ctime>
#include <cmath>
#include <fstream>
#include <thread>

void menu(); void battle(); void store(); void how_to();
void fight(string factor); void database(); void endless_mode();
void level_up(); void settings(); void update(); void reset_enemy_status();
void make_enemy(string factor); void encounter();
void output_level(string factor); int itemCount();
void show_card(Spell card); void too_poor(); void boost_menu();
void player(string factor); void item_shop(); void calculate_comp();
void enemy(string factor); void reset_items(); void item_menu();
void calculate(Spell card); void calculate_enemy();
void enemy_name(); void pick_item(); void update_items();
void boon_menu(); void companion_menu(); void rebirth_menu();

string FNAME[25] = {"Yarno", "Belloc", "Soma", "Yeen", "Marcuus", "Liol", "Quand", "Jurno", "Corsto", "Kaimo", "Lord Denna", "Hubert",
"Wernda", "Helena", "Astan", "Lucia", "Ferdinand", "Orp", "Oogga", "Ray", "Rendolf", "Portian", "Billis", "Quamm", "Foxy"};
string LNAME[25] = {"Hellfire", "Wedlok", "Hona", "Perf", "Orelius", "The Slayer", "The Butcher", "Doombringer", "The Savage", "The Destroyer", "The Loser", "The Fox",
"Hogtie", "Far-Wanderer", "Oathbreaker", "Kindy", "Wok", "Erp", "King Killer", "Nightwalker", "Pain-Bringer", "Xondoloxa", "Of The Forest", "Of The Warlords", "The Annoying"};
string FNAME2[25] = {"Holga", "Waine", "Harkken", "Folda", "Swinn", "Varis", "Galdaf", "Halfdan", "Eldar", "Roirand", "Keet", "Wet Sod",
"Germaine", "Zandar", "Kieran", "Noss", "Theoran", "Juju", "Yymigg", "Deathman", "Cildas", "Inhilla", "Harper", "Jermalline", "Biggo"};
string LNAME2[25] = {"Westbound", "The Dead", "The Lost", "The Old", "The Young", "Gillian", "The Fallen", "Bell", "Jund", "Ungundo", "Jojo", "Kiwi",
"The Wise", "The Hopeless", "Hungerer", "Aaros", "Qi", "Theros", "Queen Lover", "Flesh Eater", "Swedle", "Zikolthu", "The Small", "The Chum", "Of The Wolves"};

//0, 1, 2, 3, 4, 5, 6, 7, 8
Item AoU("Amulet of Undying", "Regain life after each battle", 0, 0), RoL("Ring of Life", "Boost health", 0, 0), 
SoP("Staff of Power", "Boost elements", 0, 0), GoS("Gauntlets of Strength", "Boost damage", 0, 0), 
RoD("Rune of Death", "Weaken enemy health", 0, 0), CoP("Cloak of Protection", "Reduce elemental damage", 0, 0),
G_T("Golden Talisman", "Boost crit chance", 0, 0), BotE("Boots of the Elves", "Boost dodge chance", 0, 0),
WoH("Wand of Heroes", "Boost shield", 1, 1); 
int items[9]; //keeps track of which items player is using

//effects with * can have varying numbers
//status effects: *bleed:0, *shield:1, *heal:2, drained:3
int player_status[4]; //keeps track of status effects on player
//status effects: *bleed:0, *shield:1, *heal:2
int enemy_status[3]; //keeps track of status effects on enemy

Spell CARD1, CARD2, CARD3;
string X, eTYPE, store1, store2, eName, encounterType, t, boon1, boon2, boon3, boon4,
comp1, comp2, comp3, comp4, comp5;
int HP, DMG, COINS, FIRE, ICE, POISON, HEAL, PROGRESS, eHP, eTempHP, eDMG, TURN, level, SHIELD, shield,
eFIRE, eICE, ePOISON, eHEAL, health, tempHP, damage, fire, ice, poison, heal, game_speed, LUCK, luck, 
DIAMONDS, CRITC, CRITD, critc, critd, eCRITC, eCRITD, DODGE, dodge, eDODGE, numItems, ELECTRIC, electric,
eELECTRIC, e, efactor, ENDLESS, endlessNum, REBIRTH, BOON, COMPANION;

int main(int argc, char const *argv[]){
    srand(time(0)); //seeds random to time
    string temp, waste;

    ifstream infile;
    infile.open("player.txt"); //get player info
    if(infile.fail()){cout<<"FILE ERROR"<<endl; exit(0);}
    infile >> waste >> temp; HP = stoi(temp); infile >> waste >> temp; DMG = stoi(temp);
    infile >> waste >> temp; FIRE = stoi(temp); infile >> waste >> temp; ICE = stoi(temp);
    infile >> waste >> temp; POISON = stoi(temp); infile >> waste >> temp; ELECTRIC = stoi(temp);
    infile >> waste >> temp; HEAL = stoi(temp); infile >> waste >> temp; CRITC = stoi(temp); 
    infile >> waste >> temp; CRITD = stoi(temp); infile >> waste >> temp; DODGE = stoi(temp); 
    infile >> waste >> temp; SHIELD = stoi(temp); infile >> waste >> temp; LUCK = stoi(temp);
    infile >> waste >> temp; COINS = stoi(temp); infile >> waste >> temp; PROGRESS = stoi(temp);
    infile >> waste >> temp; game_speed = stoi(temp); infile >> waste >> temp; store1 = temp; 
    infile >> waste >> temp; store2 = temp; infile >> waste >> temp; DIAMONDS = stoi(temp); 
    infile >> waste >> temp; numItems = stoi(temp); infile >> waste >> temp; ENDLESS = stoi(temp);
    infile >> waste >> temp; REBIRTH = stoi(temp); infile >> waste >> temp; BOON = stoi(temp);
    infile >> waste >> temp; boon1 = temp; infile >> waste >> temp; boon2 = temp;
    infile >> waste >> temp; boon3 = temp; infile >> waste >> temp; boon4 = temp; 
    infile >> waste >> temp; COMPANION = stoi(temp); infile >> waste >> temp; comp1 = temp; 
    infile >> waste >> temp; comp2 = temp; infile >> waste >> temp; comp3 = temp; 
    infile >> waste >> temp; comp4 = temp; infile >> waste >> temp; comp5 = temp;
    infile.close();

    infile.open("item.txt"); //get item info
    if(infile.fail()){cout << "FILE ERROR\n"; exit(0);}
    infile>>waste>>temp>>waste; AoU.setStat(stoi(temp)); AoU.setLevel(stoi(waste)); //Amulet of Undying
    infile>>waste>>temp>>waste; RoL.setStat(stoi(temp)); RoL.setLevel(stoi(waste)); //Ring of Life
    infile>>waste>>temp>>waste; SoP.setStat(stoi(temp)); SoP.setLevel(stoi(waste)); //Staff of Power
    infile>>waste>>temp>>waste; GoS.setStat(stoi(temp)); GoS.setLevel(stoi(waste)); //Gauntlets of Strength
    infile>>waste>>temp>>waste; RoD.setStat(stoi(temp)); RoD.setLevel(stoi(waste)); //Rune of Death
    infile>>waste>>temp>>waste; CoP.setStat(stoi(temp)); CoP.setLevel(stoi(waste)); //Cloak of Protection
    infile>>waste>>temp>>waste; G_T.setStat(stoi(temp)); G_T.setLevel(stoi(waste)); //Golden Talisman
    infile>>waste>>temp>>waste; BotE.setStat(stoi(temp)); BotE.setLevel(stoi(waste)); //Boots of the Elves
    infile>>waste>>temp>>waste; WoH.setStat(stoi(temp)); WoH.setLevel(stoi(waste)); //Wand of Heroes
    infile.close();

    string command = ""; //dev commands
    if(argc == 2){command = argv[1];}
    menu();
}

void menu(){ //game menu
    system("clear");
    do{
        cout << BOLD << YELLOW << " WIZARDS OF DESTINY" << RESET << endl << endl;
        cout << BLUE << "    - MENU -" << RESET << endl << endl;
        cout << GREEN << " (1):" << RESET << " Play Game" << endl;
        cout << GREEN << " (2):" << RESET << " Level Up" << endl;
        cout << GREEN << " (3):" << RESET << " Additional Upgrades" << endl;
        cout << GREEN << " (4):" << RESET << " Store" << endl;
        cout << GREEN << " (5):" << RESET << " How To Play" << endl;
        cout << GREEN << " (6):" << RESET << " Settings" << endl;
        cout << GREEN << " (7):" << RESET << " Databases" << endl;
        cout << GREEN << " (0):" << RESET << " [Exit Game]" << endl << endl;
        cout << " -> ";
        cin >> X;
        system("clear");
    }while(X < "0" || X > "7");

    if(X == "1"){battle();} //play the game
    else if(X == "2"){level_up();} //go to level up menu
    else if(X == "3"){boost_menu();} //boons/companions/rebirth
    else if(X == "4"){store();} //go to store
    else if(X == "5"){how_to();} //how to play
    else if(X == "6"){settings();} //go to settings
    else if(X == "7"){database();} //go to enemy database
    else{update(); update_items(); exit(0);} //save and exit
}

void battle(){ //adventure menu
    do{
        system("clear");
        cout << BLUE << "    - PLAY -" << RESET << endl << endl;
        cout << " Select Adventure" << endl << endl;
        cout << GREEN << " (1):" << RESET << " ENDLESS MODE (Record: " << ENDLESS << ")\n"; 
        cout << GREEN << " (2):" << RESET << " Misty Dungeon" << endl;
        if(PROGRESS > 0){cout << GREEN << " (3):" << RESET << " Ruined Castle" << endl;} //only show after misty dungeon completed
        if(PROGRESS > 1){cout << GREEN << " (4):" << RESET << " Mountain of Despair" << endl;} //only show after ruined castle completed
        if(PROGRESS > 2){cout << GREEN << " (5):" << RESET << " Desolate Wastes" << endl;} //only show after mountain of despair completed
        if(PROGRESS > 3){cout << GREEN << " (6):" << RESET << " Cursed Mines" << endl;} //only show after desolate wastes completed
        cout << GREEN << " (0):" << RESET << " [Menu]" << endl << endl << " -> ";
        cin >> X;
    }while(X < "0" || X > "5");
    if(X == "0"){menu();}
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    if(X == "1"){endless_mode();} //endless
    else if(X == "2"){fight("1");} //misty dungeon
    else if(X == "3" && PROGRESS > 0){fight("2");} //ruined castle
    else if(X == "4" && PROGRESS > 1){fight("3");} //mountain of despair
    else if(X == "5" && PROGRESS > 2){fight("4");} //desolate wastes
    else if(X == "6" && PROGRESS > 3){fight("5");} //cursed mines
}

void fight(string factor){ //fight function
    int random;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    health = tempHP = HP; damage = DMG; fire = FIRE; ice = ICE; poison = POISON; heal = HEAL; TURN = 0; level = 1;
    critc = CRITC; critd = CRITD; dodge = DODGE; luck = LUCK; shield = SHIELD; electric = ELECTRIC;

    //sets all status effects to off
    for(int i = 0; i < 4; i++){player_status[i] = 0;}
    reset_enemy_status();
    
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
        electric += SoP.getStat();
    }
    if(items[6] == 1){ //Golden Talisman
        critc += G_T.getStat();
    }
    if(items[7] == 1){ //Boots of the Elves
        dodge += BotE.getStat();
    }
    if(items[8] == 1){ //Wand of Heroes
        shield += WoH.getStat();
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
                    if(TURN == 3){TURN = 1;} //when player is stunned
                    else{TURN = 0;}
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
                cout << " Reward: " << YELLOW << level*5*REBIRTH << " coins!\n" << RESET << endl; //give player reward
                COINS += (level*5*REBIRTH);
                random = (rand() % 3); //player has chance to get a diamond
                if(random == 0){DIAMONDS++;
                cout << CYAN << " You have found a diamond!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
                cout << GREEN << "[1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //back to play menu
            }
            else{ //proceed to next level
                system("clear");
                reset_enemy_status();
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage++; cout << "\n Damage increased!\n\n";}
                    else{health++; tempHP+=3; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                    " 2) Fire Boost (current: " << fire << ")\n" <<
                    " 3) Poison Boost (current: " << poison << ")\n" <<
                    " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice++; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire++; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){poison++; cout << "\n Poison increased!\n\n";}
                    else{electric++; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 5; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //dungeon cleared
                    cout << "You've cleared the Misty Dungeon!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: " << YELLOW << 250*REBIRTH << " Coins\n" << RESET << endl; //completion reward
                    COINS += 250*REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS++;
                    cout << CYAN << "You have found a diamond!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 0){ //if first time completing
                        cout << "Ruined Castle: unlocked!\n" << endl;
                        PROGRESS = 1; //unlock ruined castle
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and return to play menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter();}
                }
                if(tempHP > 0){cout << " Descending further into the dungeon...\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));}
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
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << YELLOW << level*10*REBIRTH << " coins!\n" << RESET << endl; //give reward
                COINS += (level*10*REBIRTH);
                random = (rand() % 4); //diamond chance
                if(random == 0){DIAMONDS++;
                cout << CYAN << " You have found a diamond!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                reset_enemy_status();
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 2; cout << "\n Damage increased!\n\n";}
                    else{health += 2; tempHP += 4; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                    " 2) Fire Boost (current: " << fire << ")\n" <<
                    " 3) Poison Boost (current: " << poison << ")\n" <<
                    " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 2; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 2; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){poison += 2; cout << "\n Poison increased!\n\n";}
                    else{electric += 2; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 3; tempHP += 6; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: " << YELLOW << 500*REBIRTH << " Coins\n" << RESET << endl; //player reward
                    COINS += 500*REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS += 2;
                        cout << CYAN << "You have found 2 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 1){ //first time completed
                        cout << "Mountain of Despair: unlocked!\n" << endl;
                        PROGRESS = 2; //unlock mountain of despaiir
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter();}
                }
                if(tempHP > 0){cout << " Descending further into the ruins...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));}
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
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << YELLOW << level*20*REBIRTH << " coins!\n" << RESET << endl; //player reward
                COINS += (level*20*REBIRTH);
                random = (rand() % 4); //diamond chance
                if(random == 0){DIAMONDS += 2;
                cout << CYAN << " You have found 2 diamonds\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player defeated level
                system("clear");
                reset_enemy_status();
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 4; cout << "\n Damage increased!\n\n";}
                    else{health += 4; tempHP += 6; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                    " 2) Fire Boost (current: " << fire << ")\n" <<
                    " 3) Poison Boost (current: " << poison << ")\n" <<
                    " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 4; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 4; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){poison += 4; cout << "\n Poison increased!\n\n";}
                    else{electric += 4; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 6; cout << "\n Damage increased!\n\n";}
                    else{health += 6; tempHP += 9; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //mountain cleared
                    cout << "You've cleared the Mountain of Despair!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: " << YELLOW << 750*REBIRTH << " Coins\n" << RESET << endl; //player reward
                    COINS += 750*REBIRTH;
                    random = (rand() % 2);
                    if(random == 0){DIAMONDS += 2;
                    cout << CYAN << "You have found 2 diamonds!\n" << RESET << endl;}
                    if(PROGRESS == 2){
                        cout << "Desolate Wastes: unlocked!\n" << endl;
                        PROGRESS = 3; //unlock desolate wastes
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    } //if first time completed
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and go to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter();}
                }
                if(tempHP > 0){cout << " Descending further into the mountain...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));}
                level++; TURN = 0; //level increase and turn set to player
            }
        }
    }

    //Desolate Wastes
    if(factor == "4"){
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
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << YELLOW << level*40*REBIRTH << " coins!\n" << RESET << endl; //give reward
                COINS += (level*40*REBIRTH);
                random = (rand() % 3); //diamond chance
                if(random == 0){DIAMONDS += 2;
                cout << CYAN << " You have found 2 diamonds!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << GREEN << " [1]: " << RESET << "Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                reset_enemy_status();
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 6; cout << "\n Damage increased!\n\n";}
                    else{health += 6; tempHP += 9; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                    " 2) Fire Boost (current: " << fire << ")\n" <<
                    " 3) Poison Boost (current: " << poison << ")\n" <<
                    " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 5; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 5; cout << "\n Fire increased!\n\n";}
                    else{poison += 5; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 7; cout << "\n Damage increased!\n\n";}
                    else{health += 8; tempHP += 10; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: " << YELLOW << 800*REBIRTH << " Coins\n" << RESET << endl; //player reward
                    COINS += 800*REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS += 3;
                        cout << CYAN << "You have found 3 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 3){ //first time completed
                        cout << "Cursed Mines: unlocked!\n" << endl;
                        PROGRESS = 4; //unlock cursed mines
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%6 == 0){encounter();}
                }
                if(tempHP > 0){cout << " Descending further into the wastes...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));}
                level++; TURN = 0; //go to next level, set turn to player
            }
        }
    }

    //Cursed Mines
    if(factor == "5"){
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
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << " Reward: " << YELLOW << level*50*REBIRTH << RESET << " coins!\n" << endl; //give reward
                COINS += (level*50*REBIRTH);
                random = (rand() % 3); //diamond chance
                if(random == 0){DIAMONDS += 2;
                cout << CYAN << " You have found 2 diamonds!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                update(); battle(); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                reset_enemy_status();
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 7; cout << "\n Damage increased!\n\n";}
                    else{health += 6; tempHP += 12; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                    " 2) Fire Boost (current: " << fire << ")\n" <<
                    " 3) Poison Boost (current: " << poison << ")\n" <<
                    " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){ice += 5; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){fire += 5; cout << "\n Fire increased!\n\n";}
                    else{poison += 5; cout << "\n Poison increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage += 7; cout << "\n Damage increased!\n\n";}
                    else{health += 8; tempHP += 14; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    cout << "Reward: " << YELLOW << 900*REBIRTH << " Coins\n" << RESET << endl; //player reward
                    COINS += 900*REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS += 3;
                        cout << CYAN << "You have found 3 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 4){ //first time completed
                        PROGRESS = 5; //unlock next?
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
                    update(); battle(); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter();}
                }
                if(tempHP > 0){cout << " Descending deeper into the mines...\n";
                this_thread::sleep_for(chrono::milliseconds(game_speed));}
                level++;//go to next level
                if(rand()%4 == 0){TURN = 1;} //25% chance enemy goes first
                else{TURN = 0;} //75% chance player goes first
            }
        }
    }

}

void player(string factor){ //player turn
    CARD1.get_card(health, damage, fire, ice, poison, electric, heal); //generate first spell
    CARD2.get_card(health, damage, fire, ice, poison, electric, heal); //generate second spell
    CARD3.get_card(health, damage, fire, ice, poison, electric, heal); //generate third spell

    //reset any neccesary status effects
    player_status[1] = 0; //shield

    system("clear");
    //start of turn status effects
    if(player_status[2] != 0){ //heal
        cout << ITALIC << GREEN << " You heal for " << player_status[2] << " health\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        tempHP += player_status[2];
        if(tempHP > health){tempHP = health;}
        player_status[2] = 0;
    }

    do{
    system("clear");
    output_level(factor); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    cout << " Your turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    cout << GREEN << " 1) " << RESET; show_card(CARD1); //these show the spells
    cout << GREEN << " 2) " << RESET; show_card(CARD2);
    if(player_status[3] == 0){cout << GREEN << " 3) " << RESET; show_card(CARD3);} //weakened
    cout << "\n -> ";
    cin >> X;
    }while(X < "1" || X > "3"); //until player selects spell
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
    if(X == "1"){calculate(CARD1);} //calculate spell player chose
    else if(X == "2"){calculate(CARD2);}
    else if(X == "3"){calculate(CARD3);}
    this_thread::sleep_for(chrono::milliseconds(game_speed));

    //end of turn status effects
    system("clear");
    if(player_status[0] != 0){ //bleed
        cout << ITALIC << RED << " You bleed for " << player_status[0] << " damage\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        tempHP -= player_status[0];
        if(tempHP < 1){
            cout << ITALIC << RED << " You succumb to your wounds\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        }
        player_status[0] = 0;
    }

    //reset any neccesary status effects
    player_status[3] = 0; //drained
}

void enemy(string factor){ //enemy turn
    //reset any neccesary status effects
    enemy_status[1] = 0; //shield

    system("clear");
    //start of turn status effects
    if(enemy_status[2] != 0){ //heal
        cout << ITALIC << GREEN << " " << eName << " heals for " << enemy_status[2] << " health\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        eTempHP += enemy_status[2];
        if(eTempHP > eHP){eTempHP = eHP;}
        enemy_status[2] = 0;
    }
    system("clear");
    output_level(factor); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    cout << " Enemy's turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(game_speed));
    calculate_enemy(); //calculate what spell enemy casts
    this_thread::sleep_for(chrono::milliseconds(game_speed));

    //end of turn status effects
    system("clear");
    if(enemy_status[0] != 0){ //bleed
        cout << ITALIC << RED << " " << eName << " bleeds for " << enemy_status[0] << " damage\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        eTempHP -= enemy_status[0];
        if(eTempHP < 1){
            cout << ITALIC << RED << " They succumb to their wounds\n\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait
        }
        enemy_status[0] = 0;
    }
}

void calculate(Spell card){ //calculate player spell results
    bool critted = false;
    t = card.getType(); e = card.getEffect();
    if(t == "attack" || t == "fire" || t == "ice" || t == "poison" || t == "electric" || t == "poison-heal" || t == "atk-bleed"){ //attack spell
        if(t == "fire" && eTYPE == "Ice"){e+=fire;} //ice sorcerer is weak to fire
        if(t == "fire" && eTYPE == "Fire"){e-=fire;} //fire mage is fire resistant
        if(t == "ice" && eTYPE == "Fire"){e+=ice;} //fire mage is weak to ice
        if(t == "ice-stun" && eTYPE == "Fire"){e+=ice;} //fire mage is weak to ice
        if(t == "ice" && eTYPE == "Ice"){e-=ice;} //ice sorcerer is ice resistant
        if(t == "ice-stun" && eTYPE == "Ice"){e-=ice;} //ice sorcerer is ice resistant
        if(t == "poison" && eTYPE == "Necro"){e-=poison;} //Necro is poison resistant
        if(t == "poison" && eTYPE == "Defend"){e+=poison;} //defender is weak to poison
        if(t == "electric" && eTYPE == "Wizard"){e-=electric;} //Wizard is electric resistant
        if(t == "electric" && eTYPE == "Necro"){e+=electric;} //Necro is weak to poison
        if(rand()%100 < eDODGE && BOON != 2){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            e -= enemy_status[1]; if(e < 0){e = 0;} //enemy shield status
            eTempHP -= e; //decrease enemy health
            if(t == "attack"){cout << endl << " You deal " << e << " damage!\n";} //show results
            else if(t == "atk-bleed"){cout << endl << " You deal " << e << " damage and apply bleed!\n";} //show results
            else if(t == "poison-heal"){cout << endl << " You deal " << e << " poison damage and gain heal!\n";} //show results
            else{cout << endl << " You deal " << e << " " << t << " damage!\n";}} //show results

            if(t == "poison-heal"){player_status[2] = poison; if(poison == 0){player_status[2] = 1;}} //poison/heal spell
            if(t == "atk-bleed"){enemy_status[0] = 1 + rand()%e;} //mystic slash
    }
    else if(t == "heal"){ //healing spell
        tempHP += e;
        if(tempHP > health){tempHP = health;} //can't go over max
        cout << endl << " You heal yourself for " << e << " health!\n";
        if(rand()%2 == 0){ //trigger stun
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << endl << " Enemy is stunned!\n"; TURN = 2;
        }
    }
    else if(t == "heal-shield"){ //protective barrier spell
        tempHP += e;
        if(tempHP > health){tempHP = health;} //can't go over max
        cout << endl << " You heal yourself for " << e << " health, and throw up a magic barrier!\n";
        player_status[1] = e-1; if(e == 1){player_status[1] = 1;}
    }
    else if(t == "atk-stun"){ //attack(stun) spell
        if(rand()%110 < eDODGE && BOON != 2){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            e -= enemy_status[1]; if(e < 0){e = 0;} //enemy shield status
            eTempHP -= e; TURN = 2; //deal damage, trigger stun
            cout << endl << " You stun your enemy, dealing " << e << " damage!\n";}
    }
    else if(t == "ice-stun"){ //ice(stun) spell
        if(rand()%105 < eDODGE && BOON != 2){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            e -= enemy_status[1]; if(e < 0){e = 0;} //enemy shield status
            eTempHP -= e; //deal damage
            cout << endl << " You deal " << e << " ice damage!\n";
            if(rand()%4 == 0){this_thread::sleep_for(chrono::milliseconds(game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else if(t == "electric-stun"){ //electric(stun) spell
        if(rand()%105 < eDODGE && BOON != 2){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;  
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            e -= enemy_status[1]; if(e < 0){e = 0;} //enemy shield status
            eTempHP -= e; //deal damage
            cout << endl << " You deal " << e << " electric damage!\n";
            if(rand()%10 < 3){this_thread::sleep_for(chrono::milliseconds(game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else if(t == "trick"){ //trickery spell
        cout << endl << " Magic washes over you and your enemy!\n";
        enemy_status[0] = e;
        player_status[1] = e;
        player_status[2] = e;
    }
    else{ //drain spell
        e -= enemy_status[1]; if(e < 1){e = 1;} //enemy shield status
        if(eTempHP < e){
            tempHP += eTempHP;
            eTempHP -= e;
            if(tempHP > health){tempHP = health;} //can't go over max
            cout << endl << " You drain the life from your enemy!\n";
        }
        else{
            eTempHP -= e; //damage
            tempHP += e; //heal
            if(tempHP > health){tempHP = health;} //can't go over max
            cout << endl << " You drain " << e << " life from the enemy!\n";
        }
    }

    if(critted == true){ //a critical hit happened
        if(BOON == 3 && tempHP < health){ //booon of the trickster
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << YELLOW << "\n The Trickster's blessing heals you\n" << RESET;
            if(heal < 6){tempHP += 3;}
            else{tempHP += heal/2;}
            if(tempHP > health){tempHP = health;}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    if(COMPANION != 0){calculate_comp();} //companions
}

void calculate_comp(){ //calculate companion effects
    if(COMPANION == 1){ //fairy
        if(tempHP < health){
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << "\n Fairy blesses you with health\n";
            if(heal < 4){tempHP += 2;}
            else{tempHP += heal/2;}
            if(tempHP > health){tempHP = health;}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }
    else if(COMPANION == 2){ //imp
        if(eTempHP > 0){
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << "\n Imp strikes at your enemy\n";
            eTempHP -= damage/2;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }
    else if(COMPANION == 3){ //pixie
        if(eTempHP > 0 && TURN != 2){
            if(rand()%5 == 0){
                this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Pixie stuns your enemy\n"; TURN = 2;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
            }
        }
    }
    else if(COMPANION == 4){ //gnome
        if(rand()%3 == 0){
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%8 == 0){
                cout << CYAN << "\n Gnome discovers a diamond!\n" << RESET; DIAMONDS++;
            }
            else{
                cout << "\n Gnome finds some treasure! +" << 25*REBIRTH << " Coins!\n"; COINS += 25*REBIRTH;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }
    else{ //lizard
        if(rand()%3 == 0){
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%2 == 0 && enemy_status[0] == 0){
                cout << CYAN << "\n Lizard bites at the enemy, applying bleed!\n" << RESET;
                enemy_status[0] = (rand()%damage) + 1;
            }
            else if(player_status[2] == 0){
                cout << "\n Lizard grants you heal\n";
                player_status[2] = (rand()%(heal + 1)) + 1;
            }
            else{
                cout << "\n Lizard scurries around your feet. +2 health\n";
                tempHP+=2; if(tempHP > health){tempHP = health;}
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }
}

void calculate_enemy(){ //calculate what spell enemy casts
    int tempDMG = eDMG - player_status[1]; if(tempDMG < 0){tempDMG = 0;} //player shield status
    if(eTYPE == "Wizard"){ //evil wizard
        efactor = rand()%11;
        if(efactor < 6){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";} //player dodges
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; 
                    cout << " " << eName << " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 7){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eFIRE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " <<
                    eName << " deals " << eDMG + eCRITD + eFIRE << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 8){ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eICE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eICE << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 9){ //poison
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + ePOISON);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + ePOISON + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 10 || eTempHP == eHP){ //electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eELECTRIC);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
    }
    else if(eTYPE == "Fire"){ //fire mage
        efactor = rand()%10;
        if(efactor < 3){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 9 || eTempHP == eHP){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eFIRE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eFIRE << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
    }
    else if(eTYPE == "Ice"){ //ice sorcerer
        efactor = rand()%10;
        if(efactor < 4){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName << 
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else{ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eICE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eICE + eDMG + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
    }
    else if(eTYPE == "Necro"){ //necromancer
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 5){ //poison
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + ePOISON);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << ePOISON + eDMG + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 6 || eTempHP == eHP){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
        else{ //drain
            tempHP -= (1 + ((tempDMG + eHEAL) / 2));
            eTempHP += (1 + ((tempDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
    else if(eTYPE == "Defend"){ //defender
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 2){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eFIRE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eFIRE + eCRITD << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                 cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 3){ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eICE);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eICE + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 7 && eTempHP < eHP){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
        else if(efactor < 8){ //electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eELECTRIC);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //drain
            tempHP -= (1 + ((tempDMG + eHEAL) / 2));
            eTempHP += (1 + ((tempDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
    else if(eTYPE == "Storm"){ //stormcaster
        efactor = rand()%10;
        if(efactor < 2){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= tempDMG;
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 9){//electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eELECTRIC);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{//stun
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (tempDMG + eELECTRIC);
                if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}
            if(items[5] == 1){tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << "\n The shock from the spell leaves you stunned...\n"; TURN = 3;
            this_thread::sleep_for(chrono::milliseconds(game_speed));}
        }    
    }
    else if(eTYPE == "Unstable"){ //unstable mage
        if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
        else{tempHP -= tempDMG;
            if(rand()%100 < eCRITC && BOON != 1){tempHP -= eCRITD; cout << " " << eName <<
                " deals " << eDMG + eCRITD << " *critical* damage!\n";}
            else{cout << " " << eName << " deals " << eDMG << " damage!\n";}
        }
        //mage takes damage
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        int unstable_damage = rand() % (eDMG + eCRITD) + 1;
        cout << "\n " << eName << " injuress themselves with their unstable magic!\n";
        cout << " They take " << unstable_damage << " damage\n";
        eTempHP -= unstable_damage;
    }

    //fix any cloak of protection overheals
    if(tempHP > health){tempHP = health;}

    //enemy apply status effects
    int stat_chance = 0;
    if(eTYPE == "Wizard"){stat_chance = 6;}
    else if(eTYPE == "Fire" || eTYPE == "Storm"){stat_chance = 2;}
    else if(eTYPE == "Ice" || eTYPE == "Defend"){stat_chance = 3;}
    else if(eTYPE == "Necro" || eTYPE == "Unstable"){stat_chance = 4;}

    if(rand()%10 < stat_chance){
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        int z = rand()%4;
        if(z == 0 && BOON != 4){ //enemy heal
            cout << "\n " << eName << " gains heal\n";
            enemy_status[2] = rand()%eHEAL + 1;
        }
        else if(z == 1 && BOON != 4){ //enemy shield
            cout << "\n " << eName << " gains shield\n";
            enemy_status[1] = rand()%eHEAL + 1;
        }
        else if(z == 2){ //player bleed
            cout << "\n " << eName << " applies bleed\n";
            player_status[0] = rand()%eDMG + 1;
        }
        else if(z == 3){ //player weakened
            cout << "\n " << eName << " applies drained\n";
            player_status[3] = 1;
        }
        else{ //fails to apply any stauts effects
            cout << "\n " << eName << " yells an insult at you\n";
        }
    }
}

void show_card(Spell card){ //display spell
    string t = card.getType(); int e = card.getEffect();
    cout << RESET;
    if(t == "fire"){cout << BOLD << RED;}
    else if(t == "ice" || t == "ice-stun"){cout << BLUE;}
    else if(t == "poison"){cout << BOLD << MAGENTA;}
    else if(t == "poison-heal"){cout << BOLD << ITALIC << MAGENTA;}
    else if(t == "electric" || t == "electric-stun"){cout << CYAN;}
    else if(t == "heal" || t == "heal-shield"){cout << BOLD << GREEN;}
    else if(t == "drain"){cout << YELLOW;}
    else if(t == "trick"){cout << ITALIC << YELLOW;}
    else if(t == "atk-bleed"){cout << ITALIC;}
    cout << card.getName() << RESET << ": ";
    if(t == "attack"){ //attack spell
        cout << "Deal " << e << " damage\n";
    }
    else if(t == "atk-stun"){ //atack(stun) spell
        cout << "Deal " << e << " damage and stun the enemy\n";
    }
    else if(t == "atk-bleed"){ //atack(stun) spell
        cout << "Deal " << e << " damage and apply bleed\n";
    }
    else if(t == "fire"){ //fire spell
        cout << "Deal " << e << " fire damage\n";
    }
    else if(t == "ice"){ //ice spell
        cout << "Deal " << e << " ice damage\n";
    }
    else if(t == "ice-stun"){ //ice stun spell
        cout << "Deal " << e << " ice damage. " << GREEN << "25%" << RESET << " chance to stun enemy\n";
    }
    else if(t == "poison"){ //poison spell
        cout << "Deal " << e << " poison damage\n";
    }
    else if(t == "poison-heal"){ //poison spell
        cout << "Deal " << e << " poison damage and gain heal\n";
    }
    else if(t == "electric"){ //electric spell
        cout << "Deal " << e << " electric damage\n";
    }
    else if(t == "electric-stun"){ //electric stun spell
        cout << "Deal " << e << " electric damage. " << GREEN << "30%" << RESET << " chance to stun enemy\n";
    }
    else if(t == "heal"){ //healing spell
        cout << "Gain " << e << " health. " << GREEN << "50%" << RESET << " chance to stun enemy\n";
    } 
    else if(t == "heal-shield"){ //protective barrier
        cout << "Gain " << e << " health and gain shield\n";
    }
    else if(t == "trick"){
        cout << "Gain and apply random status effects\n";
    }
    else{ //drain spell
        cout << "Drain " << e << " health from enemy\n";
    }
}

void output_level(string factor){ //show level player is on
    if(factor == "X"){ //endless mode
        cout << BOLD << BLUE << "    - ENDLESS MODE: LEVEL " << endlessNum << " (Record: " << ENDLESS << ") -\n" << RESET << endl;
        if(endlessNum%50 == 0){cout << "  - Demigod -\n";}
        else if(endlessNum%10 == 0){cout << "  - Archmage -\n";}
        else if(endlessNum%5 == 0){cout << "  - Great Wizard -\n";}
    }
    else if(factor == "1"){ //misty dungeon
        cout << BOLD << CYAN << "    - MISTY DUNGEON: LEVEL " << level << " -\n" << RESET << endl;
        if(level == 10){cout << "  - Guardian of the Tomb -\n";}
        if(level == 20){cout << "  - Master of the Dungeon -\n";}
    }
    else if(factor == "2"){ //ruined castle
        cout << MAGENTA << "    - RUINED CASTLE: LEVEL " << level << " -\n" << RESET << endl;
        if(level == 10){cout << "  - Upholder of Justice -\n";}
        if(level == 20){cout << "  - Lord of the Tower -\n";}
    }
    else if(factor == "3"){ //mountain of despair
        cout << RED << "    - MOUNTAIN OF DESPAIR: LEVEL " << level << " -\n" << RESET << endl;
        if(level == 10){cout << "  - Watcher of the Pass -\n";}
        if(level == 20){cout << "  - Dweller in the Deep -\n";}
    }
    else if(factor == "4"){ //desolate waste
        cout << BOLD << YELLOW << "    - DESOLATE WASTES: LEVEL " << level << " -\n" << RESET << endl;
        if(level == 10){cout << "  - Lord of the Dunes -\n";}
        if(level == 20){cout << "  - King of the Wastes -\n";}
    }
    else{ //cursed mines
        cout << BOLD << MAGENTA << "    - CURSED MINES: LEVEL " << level << " -\n" << RESET << endl;
        if(level == 10){cout << "  - Captain of the Depths -\n";}
        if(level == 20){cout << "  - Ruler of the Deep -\n";}
    }
    cout << BOLD << "  " << eName << RESET; //show enemy name
    if(eTYPE == "Wizard"){cout << " - Evil Wizard: ";} //these show enemy type
    else if(eTYPE == "Fire"){cout << RED << " - Fire Mage: " << RESET;}
    else if(eTYPE == "Ice"){cout << BLUE << " - Ice Sorcerer: " << RESET;}
    else if(eTYPE == "Necro"){cout << MAGENTA << " - Necromancer: " << RESET;}
    else if(eTYPE == "Storm"){cout << YELLOW << " - Stormcaster: " << RESET;}
    else if(eTYPE == "Unstable"){cout << BOLD << RED << " - Unstable Mage: " << RESET;}
    else{cout << " - Defender: ";}
    cout << "[Health: "; if(eTempHP < eHP){cout << RED;} else{cout << GREEN;}
    cout << eTempHP << RESET << "/" << GREEN << eHP << RESET << "]" << endl; //show enemy health
    cout << YELLOW << ITALIC << "  Status Effects:\n"; //enemy status effects
    if(enemy_status[0] != 0){cout << RED << "   - Bleed " << enemy_status[0] << endl;}
    if(enemy_status[1] != 0){cout << BLUE << "   - Shield " << enemy_status[1] << endl;}
    if(enemy_status[2] != 0){cout << GREEN << "   - Heal " << enemy_status[2] << endl;}

    cout << RESET << endl << BOLD << BLUE;
    if(items[0] == 1){ cout << "       - Equipped: Amulet of Undying -\n";}
    if(items[1] == 1){ cout << "       - Equipped: Ring of Life -\n";}
    if(items[2] == 1){ cout << "       - Equipped: Staff of Power -\n";}
    if(items[3] == 1){ cout << "       - Equipped: Gauntlets of Strength -\n";}
    if(items[4] == 1){ cout << "       - Equipped: Rune of Death -\n";}
    if(items[5] == 1){ cout << "       - Equipped: Cloak of Protection -\n";}
    if(items[6] == 1){ cout << "       - Equipped: Golden Talisman -\n";}
    if(items[7] == 1){ cout << "       - Equipped: Boots of the Elves -\n";}
    if(items[8] == 1){ cout << "       - Equipped: Wand of Heroes -\n";}
    if(COMPANION != 0){
        cout << CYAN;
        if(COMPANION == 1){cout << "       - Companion: Fairy -\n";}
        if(COMPANION == 2){cout << "       - Companion: Imp -\n";}
        if(COMPANION == 3){cout << "       - Companion: Pixie -\n";}
        if(COMPANION == 4){cout << "       - Companion: Gnome -\n";}
        if(COMPANION == 5){cout << "       - Companion: Lizard -\n";}
    }
    if(BOON != 0){
        cout << YELLOW;
        if(BOON == 1){cout << "       - Boon of the Guardian -\n";}
        if(BOON == 2){cout << "       - Boon of the Warrior -\n";}
        if(BOON == 3){cout << "       - Boon of the Trickster -\n";}
        if(BOON == 3){cout << "       - Boon of the Strategist -\n";}
    }
    cout << RESET;
    cout << "       [Health: "; if(tempHP < health){cout << RED;} else{cout << GREEN;}
    cout << tempHP << RESET << "/" << GREEN << health << RESET << "] [Damage: " << damage << "] [Fire: " << fire <<
    "] [Ice: " << ice << "] [Poison: " << poison << "]" << endl <<" You:  [Electric: " << electric <<
    "] [Heal: " << heal << "] [Crit Chance: " << critc << "%] [Crit Damage: " << critd << "]" << endl <<
    "       [Dodge: " << dodge << "%] [Shield: " << shield << "] [Luck: " << luck << "%]\n"; //player info
    cout << YELLOW << ITALIC << "       Status Effects:\n"; //player status effects
    if(player_status[0] != 0){cout << RED << "        - Bleed " << player_status[0] << endl;}
    if(player_status[1] != 0){cout << BLUE << "        - Shield " << player_status[1] << endl;}
    if(player_status[2] != 0){cout << GREEN << "        - Heal " << player_status[2] << endl;}
    if(player_status[3] != 0){cout << RED << "        - Drained" << endl;}
    cout << RESET << endl;
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
            eICE = 0; eFIRE = 0; ePOISON = 0; eELECTRIC = 0; eHEAL = 1; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE = 1;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 1;} //ice sorcerer buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 8 + (rand() % 6); eDMG = 1 + (rand() % 3);
            eICE = (rand() % 2); eFIRE = (rand() % 2); 
            ePOISON = 1; eELECTRIC = 1; eHEAL = 2; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE += 1;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 1;} //ice sorcerer buff
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 15 + (rand() % 6); eDMG = 3 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eELECTRIC = 3; eHEAL = 5; eCRITD = 2; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 2;} //ice sorcerer buff
        }
        else if(level < 15){ //levels 11-14
            eHP = 12 + (rand() % 6); eDMG = 2 + (rand() % 3);
            eICE = 1 + (rand() % 2); eFIRE = 1 + (rand() % 2); 
            ePOISON = 2; eELECTRIC = 2; eHEAL = 4; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE += 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 2;} //ice sorcerer buff
        }
        else if(level < 20){ //levels 15-19
            eHP = 15 + (rand() % 7); eDMG = 3 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eELECTRIC = 3; eHEAL = 5; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 3;} //fire mage buff
            if(eTYPE == "Ice"){eICE += 3;} //ice sorcerer buff
        }
        else{ //level 20 final boss
            eHP = 22 + (rand() % 10); eDMG = 4 + (rand() % 3);
            eICE = 2 + (rand() % 2); eFIRE = 2 + (rand() % 2); 
            ePOISON = 3; eELECTRIC = 3; eHEAL = 7; eCRITD = 4; eCRITC += 5;
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
            eICE = 1; eFIRE = 1; ePOISON = 1; eELECTRIC = 1; eHEAL = 4; eCRITD = 1;
            if(eTYPE == "Fire"){eFIRE = 2;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 2;} //ice sorcerer buff
            if(eTYPE == "Necro"){ePOISON = 2;} //necromancer buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 12 + (rand() % 8); eDMG = 3 + (rand() % 3);
            eICE = (rand() % 3); eFIRE = (rand() % 3); 
            ePOISON = (rand() % 3); eELECTRIC = 1; eHEAL = 5; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE += 1;}
            if(eTYPE == "Ice"){eICE += 1;}
            if(eTYPE == "Necro"){ePOISON += 1;}
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 20 + (rand() % 8); eDMG = 3 + (rand() % 4);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eELECTRIC = 3; eHEAL = 8; eCRITD = 3; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 15){ //levels 11-14
            eHP = 16 + (rand() % 6); eDMG = 3 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eELECTRIC = 2; eHEAL = 6; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else if(level < 20){ //levels 15-19
            eHP = 20 + (rand() % 7); eDMG = 4 + (rand() % 3);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eELECTRIC = 3; eHEAL = 7; eCRITD = 4;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
        }
        else{ //level 20 final boss
            eHP = 30 + (rand() % 10); eDMG = 4 + (rand() % 5);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eELECTRIC = 4; eHEAL = 9; eCRITD = 5; eCRITC += 3;
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
            eICE = 2; eFIRE = 2; ePOISON = 2; eELECTRIC = 2; eHEAL = 4; eCRITD = 2;
            if(eTYPE == "Fire"){eFIRE = 3;} //fire mage buff
            if(eTYPE == "Ice"){eICE = 3;} //ice sorcerer buff
            if(eTYPE == "Necro"){ePOISON = 3;} //necromancer buff
            if(eTYPE == "Defend"){eHEAL = 8; eHP += 5; eDMG -= 2;} //defender buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 24 + (rand() % 7); eDMG = 4 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eELECTRIC = 2; eHEAL = 6; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE += 1;}
            if(eTYPE == "Ice"){eICE += 1;}
            if(eTYPE == "Necro"){ePOISON += 1;}
            if(eTYPE == "Defend"){eHEAL = 10; eHP += 7; eDMG-= 2;}
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 35 + (rand() % 8); eDMG = 5 + (rand() % 5);
            eICE = 1 + (rand() % 4); eFIRE = 1 + (rand() % 4); 
            ePOISON = 1 + (rand() % 4); eELECTRIC = 3; eHEAL = 10; eCRITD = 4; eCRITC += 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 14; eHP += 8; eDMG -= 1;}
        }
        else if(level < 15){ //levels 11-14
            eHP = 28 + (rand() % 6); eDMG = 4 + (rand() % 3);
            eICE = 1 + (rand() % 3); eFIRE = 1 + (rand() % 3); 
            ePOISON = 1 + (rand() % 3); eELECTRIC = 3; eHEAL = 8; eCRITD = 4;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 10; eHP += 9; eDMG -= 1;}
        }
        else if(level < 20){ //levels 15-19
            eHP = 32 + (rand() % 7); eDMG = 4 + (rand() % 4);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 2 + (rand() % 3); eELECTRIC = 4; eHEAL = 10; eCRITD = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 12; eHP += 10; eDMG -= 1;}
        }
        else{ //level 20 final boss
            eHP = 45 + (rand() % 11); eDMG = 4 + (rand() % 5);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            ePOISON = 3 + (rand() % 3); eELECTRIC = 6; eHEAL = 12; eCRITD = 6; eCRITC += 3;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Ice"){eICE += 2;}
            if(eTYPE == "Necro"){ePOISON += 2;}
            if(eTYPE == "Defend"){eHEAL = 15; eHP += 15; eDMG -= 2;}
        }
    }

    //Desolate Wastes
    if(factor == "4"){
        //get enemy type
        int type = (rand() % 3);
        if(type == 0){eTYPE = "Fire";} //fire mage
        else if(type == 1){eTYPE = "Defend";} //defender
        else{eTYPE = "Storm";} //stormcaster

        eCRITC = 15; //crit chance
        if(eTYPE == "Defend"){eDODGE = 18;} //dodge chance
        else{eDODGE = 12;}

        //set stats
        if(level < 5){ //levels 1-4
            eHP = 25 + (rand() % 6); eDMG = 4 + (rand() % 4);
            eICE = 3; eFIRE = 3; ePOISON = 3; eELECTRIC = 3; eHEAL = 7; eCRITD = 3;
            if(eTYPE == "Fire"){eFIRE = 5;} //fire mage buff
            if(eTYPE == "Defend"){eHEAL = 9; eHP += 5; eDMG -= 2;} //defender buff
            if(eTYPE == "Storm"){eELECTRIC = 5;} //stormcaster buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 30 + (rand() % 7); eDMG = 4 + (rand() % 5);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            ePOISON = 4; eELECTRIC = 2 + (rand() % 3); eHEAL = 9; eCRITD = 5;
            if(eTYPE == "Fire"){eFIRE += 2;}
            if(eTYPE == "Storm"){eELECTRIC += 2;}
            if(eTYPE == "Defend"){eHEAL = 12; eHP += 8; eDMG-= 2;}
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 50 + (rand() % 11); eDMG = 5 + (rand() % 6);
            eICE = 2 + (rand() % 4); eFIRE = 2 + (rand() % 4); 
            eELECTRIC = 1 + (rand() % 4); ePOISON = 4; eHEAL = 12; eCRITD = 7; eCRITC += 5;
            if(eTYPE == "Fire"){eFIRE += 4;}
            if(eTYPE == "Storm"){eELECTRIC += 4;}
            if(eTYPE == "Defend"){eHEAL = 15; eHP += 10; eDMG -= 1;}
        }
        else if(level < 15){ //levels 11-14
            eHP = 40 + (rand() % 6); eDMG = 4 + (rand() % 6);
            eICE = 2 + (rand() % 3); eFIRE = 2 + (rand() % 3); 
            eELECTRIC = 2 + (rand() % 3); ePOISON = 4; eHEAL = 10; eCRITD = 5;
            if(eTYPE == "Fire"){eFIRE += 3;}
            if(eTYPE == "Storm"){eELECTRIC += 3;}
            if(eTYPE == "Defend"){eHEAL = 13; eHP += 9; eDMG -= 1;}
        }
        else if(level < 20){ //levels 15-19
            eHP = 50 + (rand() % 7); eDMG = 5 + (rand() % 6);
            eICE = 2 + (rand() % 4); eFIRE = 2 + (rand() % 4); 
            eELECTRIC = 2 + (rand() % 4); ePOISON = 4; eHEAL = 12; eCRITD = 6;
            if(eTYPE == "Fire"){eFIRE += 4;}
            if(eTYPE == "Storm"){eELECTRIC += 4;}
            if(eTYPE == "Defend"){eHEAL = 15; eHP += 10; eDMG -= 1;}
        }
        else{ //level 20 final boss
            eHP = 75 + (rand() % 11); eDMG = 6 + (rand() % 5);
            eICE = 3 + (rand() % 3); eFIRE = 3 + (rand() % 3); 
            eELECTRIC = 3 + (rand() % 3); ePOISON = 6; eHEAL = 20; eCRITD = 8; eCRITC += 10;
            if(eTYPE == "Fire"){eFIRE += 4;}
            if(eTYPE == "Storm"){eELECTRIC += 4;}
            if(eTYPE == "Defend"){eHEAL = 15; eHP += 15; eDMG -= 1;}
        }
    }

    //Cursed Mines
    if(factor == "5"){
        //get enemy type
        int type = (rand() % 4);
        if(type == 0){eTYPE = "Wizard";} //evil wizard
        else if(type == 1){eTYPE = "Ice";} //ice sorcerer
        else if(type == 2){eTYPE = "Unstable";} //unstable mage
        else{eTYPE = "Necro";} //necromancer

        if(eTYPE == "Wizard" || eTYPE == "Unstable"){eCRITC = 20;} //improved crit chance
        else{eCRITC = 15;} //basic crit chance
        eDODGE = 13; //dodge

        //set stats
        if(level < 5){ //levels 1-4
            eHP = 40 + (rand() % 10); eDMG = 5 + (rand() % 5);
            eICE = 3; eFIRE = 3; ePOISON = 3; eELECTRIC = 3; eHEAL = 8; eCRITD = 5;
            if(eTYPE == "Ice"){eICE = 5;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 5;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON = 5;} //necromancer buff
        }
        else if(level < 10){ //levels 5-9
            eHP = 50 + (rand() % 7); eDMG = 5 + (rand() % 5);
            eICE = 3 + (rand() % 3); eFIRE = 4; 
            ePOISON = 3 + (rand() % 3); eELECTRIC = 4; eHEAL = 9; eCRITD = 5;
            if(eTYPE == "Ice"){eICE += 2;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 5;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON += 2;} //necromancer buff
        }
        else if(level == 10){ //level 10 mini boss
            eHP = 65 + (rand() % 10); eDMG = 6 + (rand() % 6);
            eICE = 4 + (rand() % 4); eFIRE = 5; 
            eELECTRIC = 5; ePOISON = 4 + (rand() % 4); eHEAL = 15; eCRITD = 8; eCRITC += 5;
            if(eTYPE == "Ice"){eICE += 5;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 10;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON += 5;} //necromancer buff
        }
        else if(level < 15){ //levels 11-14
            eHP = 60 + (rand() % 6); eDMG = 6 + (rand() % 4);
            eICE = 4 + (rand() % 3); eFIRE = 5; 
            eELECTRIC = 5; ePOISON = 4 + (rand() % 3); eHEAL = 12; eCRITD = 7;
            if(eTYPE == "Ice"){eICE += 3;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 7;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON += 3;} //necromancer buff
        }
        else if(level < 20){ //levels 15-19
            eHP = 70 + (rand() % 5); eDMG = 6 + (rand() % 6);
            eICE = 4 + (rand() % 4); eFIRE = 5; 
            eELECTRIC = 5; ePOISON = 4 + (rand() % 4); eHEAL = 15; eCRITD = 8;
            if(eTYPE == "Ice"){eICE += 4;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 9;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON += 4;} //necromancer buff
        }
        else{ //level 20 final boss
            eHP = 90 + (rand() % 11); eDMG = 7 + (rand() % 5);
            eICE = 5 + (rand() % 3); eFIRE = 6; 
            eELECTRIC = 6; ePOISON = 5 + (rand() % 3); eHEAL = 25; eCRITD = 10; eCRITC += 10;
            if(eTYPE == "Ice"){eICE += 5;} //ice sorcerer buff
            if(eTYPE == "Unstable"){eDMG += 12;} //unstable mage buff
            if(eTYPE == "Necro"){ePOISON += 5;} //necromancer buff
        }
    }

    //Endless mode
    if(factor == "X"){
        //get enemy type
        int type = rand()%7;
        if(type == 0){eTYPE = "Wizard";} //evil wizard
        else if(type == 1){eTYPE = "Fire";} //fire mage
        else if(type == 2){eTYPE = "Ice";} //ice sorcerer
        else if(type == 3){eTYPE = "Necro";} //necromancer
        else if(type == 4){eTYPE = "Storm";} //stormcaster
        else if(type == 5){eTYPE = "Unstable";} //stormcaster
        else{eTYPE = "Defend";} //defender

        //factor strength based off endless level
        if(endlessNum < 10){eCRITC = 5; eDODGE = 5;}
        else if(endlessNum < 100){eCRITC = 10; eDODGE = 10;}
        else if(endlessNum < 250){eCRITC = 20; eDODGE = 15;}
        else if(endlessNum < 500){eCRITC = 30; eDODGE = 20;}
        else if(endlessNum < 1000){eCRITC = 40; eDODGE = 25;}
        else{eCRITC = 45; eDODGE = 30;}
        //boss
        if(endlessNum%10 == 0){
            eHP += rand()%(endlessNum/5); eDMG += 5;
            eHEAL += rand()%(endlessNum/10); eCRITD += 5;
            eCRITC += 5; eDODGE += 2;
        }

        //set stats
        eHP = 4 + (rand() % endlessNum); 
        eDMG = 2 + (rand() % endlessNum/4);
        eICE = 3 + (rand() % endlessNum/10); 
        eFIRE = 3 + (rand() % endlessNum/10); 
        ePOISON = 3 + (rand() % endlessNum/10); 
        eELECTRIC = 3 + (rand() % endlessNum/10); 
        eHEAL = 3 + (rand() % endlessNum/3); 
        eCRITD = 2 + (rand() % endlessNum/5);
        if(eTYPE == "Wizard" || eTYPE == "Unstable"){eCRITC += 2;}
        if(eTYPE == "Fire"){eFIRE += 1 + (rand() % endlessNum/10);}
        if(eTYPE == "Ice"){eICE += 1 + (rand() % endlessNum/10);}
        if(eTYPE == "Necro"){ePOISON += 1 + (rand() % endlessNum/10);}
        if(eTYPE == "Storm"){eELECTRIC += 1 + (rand() % endlessNum/10);}
        if(eTYPE == "UNSTABLE"){
            eDMG += 1 + (rand() % endlessNum/10);
            eCRITD += 1 + (rand() % endlessNum/20);
        }
        if(eTYPE == "Defend"){
            eHEAL += 1 + (rand() % endlessNum/10); 
            eHP += 3 + (rand() % endlessNum/5); 
            eDMG -= (rand() % endlessNum/10);
            eDODGE +=3;
        }

        //check that stats will work (health/damage)
        if(eHP < (endlessNum - 40)){eHP = endlessNum - 40;}
        if(eDMG < (endlessNum - 150)){eHP = endlessNum - 150;}
        if(eDMG < 1){eDMG = 10;} //in unlikely chance defender dmg drops below 1, sets to a base dmg
    }

    if(items[4] == 1){eHP -= RoD.getStat();} //rune of death
    if(eHP < 1){eHP = 1;}
    if((eDMG - shield) < 0){eDMG = 0;} //apply shield
    else{eDMG -= shield;}
}

void endless_mode(){ //endless game mode
    int random;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    health = tempHP = HP; damage = DMG; fire = FIRE; ice = ICE; poison = POISON; heal = HEAL; TURN = 0; level = 1;
    critc = CRITC; critd = CRITD; dodge = DODGE; luck = LUCK; shield = SHIELD; electric = ELECTRIC; endlessNum = 1;
    
    //sets all status effects to off
    for(int i = 0; i < 4; i++){player_status[i] = 0;}
    reset_enemy_status();

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
        electric += SoP.getStat();
    }
    if(items[6] == 1){ //Golden Talisman
        critc += G_T.getStat();
    }
    if(items[7] == 1){ //Boots of the Elves
        dodge += BotE.getStat();
    }
    if(items[8] == 1){ //Wand of Heroes
        shield += WoH.getStat();
    }
    this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly

    while(tempHP > 0){
        make_enemy("X"); //create this level's enemy
        enemy_name(); //create the enemy name
        eTempHP = eHP; //set enemy temp health
    
        while(tempHP > 0 && eTempHP > 0){ //runs through battle
            if(TURN == 0){ //player turn
                player("X");
                if(TURN == 2){TURN = 0;} //when enemy is stunned
                else{TURN = 1;}
            }
            else{ //enemy turn
                enemy("X");
                if(TURN == 3){TURN = 1;} //when player is stunned
                else{TURN = 0;}
            }
        }
    
        if(tempHP < 1){ //player lost
            system("clear");
            cout << " You have been defeated\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
            if(endlessNum > ENDLESS){ENDLESS = endlessNum;}
            cout << " Level Reached: " << endlessNum << endl;
            cout << ITALIC << " Record: " << ENDLESS << RESET << endl << endl;
            this_thread::sleep_for(chrono::milliseconds(game_speed*2)); //wait briefly
            //give player reward
            if(endlessNum < 25){
                cout << " Reward: " << YELLOW << endlessNum*5*REBIRTH << " coins!\n" << endl; 
                COINS += (endlessNum*5*REBIRTH);
            }
            else if(endlessNum < 50){
                cout << " Reward: " << YELLOW << endlessNum*10*REBIRTH << " coins!\n" << endl; 
                COINS += (endlessNum*10*REBIRTH);
            }
            else{
                cout << " Reward: " << YELLOW << endlessNum*15*REBIRTH << " coins!\n" << endl; 
                COINS += (endlessNum*15*REBIRTH);
            }
            cout << RESET;
            random = (rand() % 3); //player has chance to get a diamond
            if(random == 0){DIAMONDS++;
            cout << CYAN << " You have found a diamond!\n\n" << RESET;}
            this_thread::sleep_for(chrono::milliseconds(game_speed)); //wait briefly
            cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
            cin >> X; this_thread::sleep_for(chrono::milliseconds(game_speed));
            update(); battle(); //back to play menu
        }
        else{ //proceed to next level
            system("clear");
            reset_enemy_status();
            cout << " Enemy defeated!\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(items[0] == 1 && tempHP < health){ //Amulet of Undying
                cout << " Amulet of Undying activates\n" << endl;
                tempHP += AoU.getStat();
                if(tempHP > health){tempHP = health;} //make sure doesn't go over max hp
                this_thread::sleep_for(chrono::milliseconds(game_speed));
            }
            if(endlessNum%50 == 0){ //every 50 levels gives big buff
                cout << "Your powers are growing!\n\n";
                health+=20; tempHP+=20; damage+=5; heal+=5;
                ice+=2; fire+=2; poison+=2; electric+=2; critd+=5;
                this_thread::sleep_for(chrono::milliseconds(game_speed));
            }
            else if(endlessNum%10 == 0){ //every 10th level cleared stat boost
                cout << "Choose upgrade:\n\n";
                cout << " 1) Ice Boost (current: " << ice <<")\n" << 
                " 2) Fire Boost (current: " << fire << ")\n" <<
                " 3) Poison Boost (current: " << poison << ")\n" <<
                " 4) Electric Boost (current: " << electric << ")\n\n -> ";
                cin >> X;
                int buff;
                if(endlessNum < 30){buff = 1;}
                else if(endlessNum < 50){buff = 2;}
                else if(endlessNum < 100){buff = 3;}
                else{buff = 5;}
                if(X == "1"){ice+=buff; cout << "\n Ice increased!\n\n";}
                else if(X == "2"){fire+=buff; cout << "\n Fire increased!\n\n";}
                else if(X == "3"){poison+=buff; cout << "\n Poison increased!\n\n";}
                else{electric+=buff; cout << "\n Electric increased!\n\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
            }
            else if(endlessNum%5 == 0){ //every 5th level cleared gives stat boost
                cout << "Choose upgrade:\n\n";
                cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                cin >> X;
                int buff;
                if(endlessNum < 30){buff = 1;}
                else if(endlessNum < 50){buff = 2;}
                else if(endlessNum < 100){buff = 3;}
                else{buff = 5;}
                if(X == "1"){damage+=buff; cout << "\n Damage increased!\n\n";}
                else{health+=(buff+1); tempHP+=(buff+2); if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
                this_thread::sleep_for(chrono::milliseconds(game_speed));
            }
            if(endlessNum%10 != 0){ //random encounter
                if(rand()%6 == 0){encounter();}
            }
            if(tempHP > 0){cout << " Continuing on...\n"; 
            this_thread::sleep_for(chrono::milliseconds(game_speed));}
            endlessNum++; TURN = 0; //set turn to players, increase dungeon level
        }
    }
}

void level_up(){ //level up menu
    system("clear");
    do{
    cout << BLUE << "    - LEVEL UP -" << RESET << endl << endl;
    cout << MAGENTA << "Select stat to increase" << RESET << endl;
    cout << "COINS: " << YELLOW << COINS << RESET << endl << endl;

    cout << GREEN << " (1):" << RESET << " Health: " << CYAN << HP << RESET << "        ["; //health and varied cost
    if(HP < 11){cout << YELLOW << "25 Coins" << RESET << "]" << endl;}
    else if(HP < 15){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(HP < 20){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (2):" << RESET << " Damage: " << CYAN << DMG << RESET << "        ["; //damage and varied cost
    if(DMG < 2){cout << YELLOW << "25 Coins" << RESET << "]" << endl;}
    else if(DMG < 5){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(DMG < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (3):" << RESET << " Fire: " << CYAN << FIRE << RESET << "          ["; //fire and varied cost
    if(FIRE < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(FIRE < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;} 

    cout << GREEN << " (4):" << RESET << " Ice: " << CYAN << ICE << RESET << "           ["; //ice and varied cost
    if(ICE < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(ICE < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;} 

    cout << GREEN << " (5):" << RESET << " Poison: " << CYAN << POISON << RESET << "        ["; //poison and varied cost
    if(POISON < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(POISON < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (6):" << RESET << " Electric: " << CYAN << ELECTRIC << RESET << "      ["; //poison and varied cost
    if(ELECTRIC < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(ELECTRIC < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (7):" << RESET << " Heal: " << CYAN << HEAL << RESET << "          ["; //heal and varied cost
    if(HEAL < 5){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(HEAL < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (8):" << RESET << " Crit Chance: " << CYAN << CRITC << RESET << "%  ["; //crit chance and varied cost
    if(CRITC < 10){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(CRITC < 20){cout << YELLOW << "75 Coins" << RESET << "]" << endl;}
    else if(CRITC < 60){cout << YELLOW << "150 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]" << endl;}

    cout << GREEN << " (9):" << RESET << " Crit Damage: " << CYAN << CRITD << RESET << "   ["; //crit damage and varied cost
    if(CRITD < 7){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(CRITD < 10){cout << YELLOW << "150 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "300 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (10):" << RESET << " Dodge: " << CYAN << DODGE << RESET << "%       ["; //crit chance and varied cost
    if(DODGE < 10){cout << YELLOW << "30 Coins" << RESET << "]" << endl;}
    else if(DODGE < 15){cout << YELLOW << "80 Coins" << RESET << "]" << endl;}
    else if(DODGE < 40){cout << YELLOW << "120 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << " (11):" << RESET << " Shield: " << CYAN << SHIELD << RESET << "        ["; //shield
    if(SHIELD == 0){cout << YELLOW << "250 Coins" << RESET << "]" << endl;}
    else if(SHIELD < 3){cout << YELLOW << "500 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << " (12):" << RESET << " Luck: " << CYAN << LUCK << RESET << "%        ["; //shield
    if(LUCK < 75){cout << YELLOW << "10 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << "\n (0):" << RESET << " [Menu]" << endl << endl;
    cout << " -> "; 
    cin >> X;
    system("clear");
    }while(stoi(X) < 0 || stoi(X) > 12);
    if(X == "1"){ //health
        if(HP < 11){ 
            if(COINS > 24){COINS -= 25; HP += 1; update();}
            else{too_poor();} //tell players they don't have enough coins
        }
        else if(HP < 15){ 
            if(COINS > 49){COINS -= 50; HP += 1; update();}
            else{too_poor();}
        }
        else if(HP < 20){
            if(COINS > 99){COINS -= 100; HP += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; HP += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "2"){ //damage
        if(DMG < 2){
            if(COINS > 24){COINS -= 25; DMG += 1; update();}
            else{too_poor();}
        }
        else if(DMG < 5){
            if(COINS > 49){COINS -= 50; DMG += 1; update();}
            else{too_poor();}
        }
        else if(DMG < 10){
            if(COINS > 99){COINS -= 100; DMG += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; DMG += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "3"){ //fire
        if(FIRE < 5){
            if(COINS > 39){COINS -= 40; FIRE += 1; update();}
            else{too_poor();}
        }
        else if(FIRE < 10){
            if(COINS > 99){COINS -= 100; FIRE += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; FIRE += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "4"){ //ice
        if(ICE < 5){
            if(COINS > 39){COINS -= 40; ICE += 1; update();}
            else{too_poor();}
        }
        else if(ICE < 10){
            if(COINS > 99){COINS -= 100; ICE += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; ICE += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "5"){ //poison
        if(POISON < 5){
            if(COINS > 39){COINS -= 40; POISON += 1; update();}
            else{too_poor();}
        }
        else if(POISON < 10){
            if(COINS > 99){COINS -= 100; POISON += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; POISON += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "6"){ //electric
        if(ELECTRIC < 5){
            if(COINS > 39){COINS -= 40; ELECTRIC += 1; update();}
            else{too_poor();}
        }
        else if(ELECTRIC < 10){
            if(COINS > 99){COINS -= 100; ELECTRIC += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; ELECTRIC += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "7"){ //heal
        if(HEAL < 5){
            if(COINS > 49){COINS -= 50; HEAL += 1; update();}
            else{too_poor();}
        }
        else if(HEAL < 10){
            if(COINS > 99){COINS -= 100; HEAL += 1; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 199){COINS -= 200; HEAL += 1; update();}
            else{too_poor();}
        }
    }
    else if(X == "8"){ //crit chance
        if(CRITC < 10){
            if(COINS > 49){COINS -= 50; CRITC += 1; update();}
            else{too_poor();}
        }
        else if(CRITC < 20){
            if(COINS > 74){COINS -= 75; CRITC += 1; update();}
            else{too_poor();}
        }
        else if(CRITC < 60){
            if(COINS > 149){COINS -= 150; CRITC += 1; update();}
            else{too_poor();}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up();
        }
    }
    else if(X == "9"){ //crit damage
        if(CRITD < 7){
            if(COINS > 49){COINS -= 50; CRITD += 2; update();}
            else{too_poor();}
        }
        else if(CRITD < 10){
            if(COINS > 149){COINS -= 150; CRITD += 2; update();}
            else{too_poor();}
        }
        else{
            if(COINS > 299){COINS -= 300; CRITD += 2; update();}
            else{too_poor();}
        }
    }
    else if(X == "10"){ //dodge chance
        if(DODGE < 10){
            if(COINS > 29){COINS -= 30; DODGE += 1; update();}
            else{too_poor();}
        }
        else if(DODGE < 15){
            if(COINS > 79){COINS -= 80; DODGE += 1; update();}
            else{too_poor();}
        }
        else if(DODGE < 40){
            if(COINS > 119){COINS -= 120; DODGE += 1; update();}
            else{too_poor();}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up();
        }
    }
    else if(X == "11"){ //shield
        if(SHIELD == 0){
            if(COINS > 249){COINS -= 250; SHIELD += 1; update();}
            else{too_poor();}
        }
        else if(SHIELD < 3){
            if(COINS > 499){COINS -= 500; SHIELD += 1; update();}
            else{too_poor();}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up();
        }
    }
    else if(X == "12"){ //luck
        if(LUCK < 75){
            if(COINS > 9){COINS -= 10; LUCK += 1; update();}
            else{too_poor();}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up();
        }
    }
    else{menu();}
    level_up();
}

void how_to(){ //game instructions
    system("clear");
    cout << BOLD << YELLOW << " WIZARDS OF DESTINY\n" << RESET << endl;
    cout << BLUE << "  - HOW TO PLAY -\n" << RESET << endl;
    cout << MAGENTA << "*" << RESET << " When you enter an adventure, you start with your base stats\n";
    cout << MAGENTA << "*" << RESET << " You may select an item to give you an advantage on your run\n";
    cout << MAGENTA << "*" << RESET << " You'll encounter enemies on each level. Enemies grow stronger as levels progress\n";
    cout << MAGENTA << "*" << RESET << " You take turns casting spells, until you or the enemy are defeated\n";
    cout << MAGENTA << "*" << RESET << " You get a selection of 3 random spells, which are influenced by your stats\n";
    cout << MAGENTA << "*" << RESET << " At certain points in the adventure, you can gain upgrades for your stats\n";
    cout << MAGENTA << "*" << RESET << " When you die, you recieve coins based on your progress in the level\n";
    cout << MAGENTA << "*" << RESET << " Spend coins in the \"Level Up\" menu to increase your base stats\n";
    cout << MAGENTA << "*" << RESET << " Continue to battle and level up to become the greatest wizard of all time!\n" << endl;
    cout << MAGENTA << "*" << RESET << " Now go on an adventure, and find your destiny!\n" << endl;
    cout << GREEN << " (0):" << RESET << " Menu\n\n -> ";
    cin >> X;
    menu();
}

void store(){ //store menu
    do{
        system("clear");
        cout << BLUE << "  - STORE -\n" << RESET << endl;
        cout << "COINS: " << YELLOW << COINS << RESET << endl << "DIAMONDS: " << CYAN << DIAMONDS << RESET << endl << endl;
        cout << GREEN << " (1):" << RESET << " Game Speed Increase ";
        if(store1 == "no"){cout << CYAN << " [20 Diamonds]\n" << RESET;} //can be bought
        else{cout << RED << "*Already Purchased*\n" << RESET;} //already bought
        cout << GREEN << " (2):" << RESET << " Stat Boost " << CYAN << " [5 Diamonds]\n" << RESET;
        cout << GREEN << " (3):" << RESET << " Buy Items\n";
        cout << GREEN << " (4):" << RESET << " Second Starting Item ";
        if(store2 == "no"){cout << YELLOW << " [750 Coins]\n" << RESET;} //can be bought
        else{cout << RED << "*Already Purchased*\n" << RESET;} //already bought
        cout << GREEN << " (0):" << RESET << " Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "4");
    if(X == "1"){
        if(store1 == "yes"){ //already own game speed upgrade
            system("clear"); cout << CYAN << "You already own this item\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{
            if(DIAMONDS > 19){ //buy game speed upgrade
                DIAMONDS -= 20; store1 = "yes"; game_speed = 500;
                update(); store();
            }
            else{ //too poor
                system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); store();
            }
        }
    }
    else if(X == "2"){
        if(DIAMONDS > 4){ //buy stat boost
            DIAMONDS -= 5; HP += 2; DMG += 2; FIRE += 2; ICE += 2; POISON += 2; HEAL += 2; CRITD += 2; ELECTRIC += 2;
            update(); system("clear"); cout << CYAN << " Stats have been boosted\n" << RESET; 
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{ //too poor
            system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
    }
    else if(X == "3"){item_shop();}
    else if(X == "4"){
        if(store2 == "yes"){ //already own second item
            system("clear"); cout << CYAN << "You already own this upgrade\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{
            if(COINS > 749){ //buy game speed upgrade
                COINS -= 750; store2 = "yes";
                update(); store();
            }
            else{system("clear"); cout << CYAN << "You don't have enough coins\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); store();}
        }
    }
    else{menu();}
}

void settings(){ //settings menu
    do{
        system("clear");
        cout << BLUE << "  - SETTINGS -\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Change Game Speed [";
        if(game_speed == 1000){cout << "normal]";}
        else{cout << "fast]";}
        if(store1 == "no"){cout << YELLOW << " *Unlock in store*" << RESET;} //shows if setting needs bought
        cout << endl << GREEN << " (2):" << RESET << " Reset Save" << RED << " *Permanent*" << RESET;
        cout << endl << GREEN << " (0):" << RESET << " Back to Menu\n\n -> ";
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
            cout << BLUE << " RESET SAVE\n" << RESET << endl;
            cout << BOLD << RED << "Are you sure you want to reset? All progress will be lost\n" << RESET << endl;
            cout << GREEN << " (1):" << RESET << " Reset\n " << GREEN << "(0):" << RESET << " Back to Settings\n\n -> ";
            cin >> X;
        }while(X < "0" || X > "1");
        if(X == "1"){ //reset save
            HP=10; DMG=1; FIRE=0; ICE=0; POISON=0; HEAL=0; COINS=0; PROGRESS = 0; CRITC = 5; CRITD = 2; ELECTRIC = 0;
            game_speed = 1000; store1 = "no"; DIAMONDS = 0; numItems = 0; DODGE = 5; LUCK = 5; SHIELD = 0;
            store2 = "no"; boon1 = boon2 = boon3 = boon4 = "no"; BOON = 0; ENDLESS = 0; REBIRTH = 1; COMPANION = 0;
            comp1 = comp2 = comp3 = comp4 = comp5 = "no"; update(); reset_items(); settings();
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
    outfile << "G_T " << G_T.getStat() << " " << G_T.getLevel() << endl; //Golden Talisman
    outfile << "BotE " << BotE.getStat() << " " << BotE.getLevel() << endl; //Boots of the Elves
    outfile << "WoH " << WoH.getStat() << " " << WoH.getLevel() << endl; //Wand of Heroes
    outfile.close();
}

void reset_items(){ //reset item data
    AoU.setStat(1); AoU.setLevel(1);
    RoL.setStat(2); RoL.setLevel(1);
    SoP.setStat(1); SoP.setLevel(1);
    GoS.setStat(2); GoS.setLevel(1);
    RoD.setStat(2); RoD.setLevel(1);
    CoP.setStat(1); CoP.setLevel(1);
    G_T.setStat(10); G_T.setLevel(1);
    BotE.setStat(10); BotE.setLevel(1);
    WoH.setStat(1); WoH.setLevel(1);
    update_items();
}

void enemy_name(){ //generate enemy name
    eName = "";
    int random;
    random = (rand() % 2);
    if(random == 0){ //first first name list
        random = (rand() % 25);
        eName += FNAME[random];
    }
    else{ //second first name list
        random = (rand() % 25);
        eName += FNAME2[random];
    }
    eName += " ";
    random = (rand() % 2);
    if(random == 0){ //first last name list
        random = (rand() % 25);
        eName += LNAME[random];
    }
    else{ //second last name list
        random = (rand() % 25);
        eName += LNAME2[random];
    }
}

void pick_item(){ //get new item
    for(int i = 0; i < 9; i++){ //reset items
        items[i] = 0;
    }
    Item x, y, z; int a, b, c; string d, e, f;
    string info = get_item(numItems); //return three items
    d = info.at(0); e = info.at(1); f = info.at(2);
    a = stoi(d); b = stoi(e); c = stoi(f);
    if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
    else if(a == 3){x = GoS;} else if(a == 4){x = RoD;} else if(a == 5){x = CoP;}
    else if(a == 6){x = G_T;} else if(a == 7){x = BotE;} else{x = WoH;}

    if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
    else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
    else if(b == 6){y = G_T;} else if(b == 7){y = BotE;} else{y = WoH;}

    if(c == 0){z = AoU;} else if(c == 1){z = RoL;} else if(c == 2){z = SoP;} 
    else if(c == 3){z = GoS;} else if(c == 4){z = RoD;} else if(c == 5){z = CoP;}
    else if(c == 6){z = G_T;} else if(c == 7){z = BotE;} else{z = WoH;}
    do{
        system("clear");
        cout << BLUE << " Select Starting Item\n" << RESET << endl;
        cout << GREEN << " (1): " << RESET; x.print();
        cout << GREEN << "\n (2): " << RESET; y.print();
        cout << GREEN << "\n (3): " << RESET; z.print();
        cout << "\n\n -> ";
        cin >> X;
    }while(X < "1" || X > "3");
    if(X == "1"){items[a] = 1;}
    else if(X == "2"){items[b] = 1;}
    else{items[c] = 1;}

    if(store2 == "yes"){ //if second item upgrade owned
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        system("clear");
        info = extra_item(numItems, items); //return two items
        d = info.at(0); e = info.at(1);
        a = stoi(d); b = stoi(e);
        if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
        else if(a == 3){x = GoS;} else if(a == 4){x = RoD;} else if(a == 5){x = CoP;}
        else if(a == 6){x = G_T;} else if(a == 7){x = BotE;} else{x = WoH;}
    
        if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
        else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
        else if(b == 6){y = G_T;} else if(b == 7){y = BotE;} else{y = WoH;}
    
        cout << BLUE << " Select Second Item\n" << RESET << endl;
        cout << GREEN << " (1): " << RESET; x.print();
        cout << GREEN << "\n (2): " << RESET; y.print();
        cout << "\n\n -> ";
        cin >> X;
        if(X == "1"){items[a] = 1;}
        else{items[b] = 1;}
    }
}

void item_shop(){ //buy items
    do{
        system("clear");
        cout << BLUE << "  - ITEM SHOP -\n" << RESET << endl;
        cout << "DIAMONDS: " << CYAN << DIAMONDS << RESET << endl << endl;
        if(numItems < 5){cout << GREEN << " (1):" << RESET << " Unlock Next Item " << CYAN << " [4 Diamonds]\n" << RESET;}
        else{cout << GREEN << " (-):" << RESET << " All Items Unlocked\n";}
        cout << GREEN << " (0):" << RESET << " Back To Store\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "1"){
        if(numItems == 5){ //already own all items
            system("clear"); cout << CYAN << "Currently no items to buy\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); item_shop();
        }
        else{
            if(DIAMONDS < 4){ //too poor
                system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); item_shop(); 
            }
            else{ //buy next item
                system("clear");
                DIAMONDS -=4;
                if(numItems == 0){ //rune of death
                    cout << CYAN << " Acquired: Rune of Death!\n" << RESET;
                }
                else if(numItems == 1){ //cloak of protection
                    cout << CYAN << " Acquired: Cloak of Protection!\n" << RESET;
                }
                else if(numItems == 2){ //golden talisman
                    cout << CYAN << " Acquired: Golden Talisman!\n" << RESET;
                }
                else if(numItems == 3){ //boots of the elves
                    cout << CYAN << " Acquired: Boots of the Elves!\n" << RESET;
                }
                else{ //wand of heroes
                    cout << CYAN << " Acquired: Wand of Heroes!\n" << RESET;
                }
                numItems++; update();
                this_thread::sleep_for(chrono::seconds(1)); item_shop(); 
            }
        }
    }
    else{store();}
}

void boost_menu(){ //boons, companions, item upgrades, and rebirth
    do{
        system("clear");
        cout << BLUE << "  - ADDITIONAL UPGRADES -\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Boons\n";
        cout << GREEN << " (2):" << RESET << " Companions\n";
        cout << GREEN << " (3):" << RESET << " Upgrade Items\n";
        cout << GREEN << " (4):" << RESET << " Rebirth\n";
        cout << GREEN << " (0):" << RESET << " Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "4");
    if(X == "0"){menu();}
    else if(X == "1"){boon_menu();}
    else if(X == "2"){companion_menu();}
    else if(X == "3"){item_menu();}
    else{rebirth_menu();}
}

void boon_menu(){ //controls player boons
    do{
        system("clear");
        cout << BLUE << "  - BOONS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Boons give a unique in-game buff\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Boon of the Guardian: Enemies cannot crit";
        if(boon1 == "no"){cout << YELLOW << " (Unlock for 1500 coins)" << RESET;}
        if(BOON == 1){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (2):" << RESET << " Boon of the Warrior: Enemies cannot dodge";
        if(boon2 == "no"){cout << YELLOW << " (Unlock for 3000 coins)" << RESET;}
        if(BOON == 2){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (3):" << RESET << " Boon of the Trickster: Heal on crits";
        if(boon3 == "no"){cout << YELLOW << " (Unlock for 5000 coins)" << RESET;}
        if(BOON == 3){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (4):" << RESET << " Boon of the Strategist: Enemies cannot gain buffs";
        if(boon4 == "no"){cout << YELLOW << " (Unlock for 5500 coins)" << RESET;}
        if(BOON == 4){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (5):" << RESET << " Disable Boons\n";
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "5");
    if(X == "0"){boost_menu();}
    else if(X == "1"){ //guardian
        if(boon1 == "no"){
            if(COINS < 1500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu();
            }
            else{COINS -= 1500; boon1 = "yes"; update(); boon_menu();}
        }
        else{BOON = 1; boon_menu();}
    }
    else if(X == "2"){ //warrior
        if(boon2 == "no"){
            if(COINS < 3000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu();
            }
            else{COINS -= 3000; boon2 = "yes"; update(); boon_menu();}
        }
        else{BOON = 2; boon_menu();}
    }
    else if(X == "3"){ //trickster
        if(boon3 == "no"){
            if(COINS < 5000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu();
            }
            else{COINS -= 5000; boon3 = "yes"; update(); boon_menu();}
        }
        else{BOON = 3; boon_menu();}
    }
    else if(X == "4"){ //strategist
        if(boon4 == "no"){
            if(COINS < 5500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu();
            }
            else{COINS -= 5500; boon4 = "yes"; update(); boon_menu();}
        }
        else{BOON = 4; boon_menu();}
    }
    else{BOON = 0; boon_menu();}
}

void companion_menu(){ //controls player companions
    do{
        system("clear");
        cout << BLUE << "  - COMPANIONS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Companions assist you in battle\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Fairy: Heals your wounds"; //fairy
        if(comp1 == "no"){cout << YELLOW << " (Unlock for 800 coins)" << RESET;}
        if(COMPANION == 1){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (2):" << RESET << " Imp: Attacks enemies"; //imp
        if(comp2 == "no"){cout << YELLOW << " (Unlock for 1000 coins)" << RESET;}
        if(COMPANION == 2){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (3):" << RESET << " Pixie: Can stun enemies"; //pixie
        if(comp3 == "no"){cout << YELLOW << " (Unlock for 2000 coins)" << RESET;}
        if(COMPANION == 3){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (4):" << RESET << " Gnome: Searches for treasure"; //gnome
        if(comp4 == "no"){cout << YELLOW << " (Unlock for 5000 coins)" << RESET;}
        if(COMPANION == 4){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (5):" << RESET << " Lizard: Can apply bleed or heal"; //lizard
        if(comp5 == "no"){cout << YELLOW << " (Unlock for 6000 coins)" << RESET;}
        if(COMPANION == 5){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (6):" << RESET << " Disable Companions\n";
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "6");
    if(X == "0"){boost_menu();}
    else if(X == "1"){ //fairy
        if(comp1 == "no"){
            if(COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu();
            }
            else{COINS -= 800; comp1 = "yes"; update(); companion_menu();}
        }
        else{COMPANION = 1; companion_menu();}
    }
    else if(X == "2"){ //imp
        if(comp2 == "no"){
            if(COINS < 1000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu();
            }
            else{COINS -= 1000; comp2 = "yes"; update(); companion_menu();}
        }
        else{COMPANION = 2; companion_menu();}
    }
    else if(X == "3"){ //pixie
        if(comp3 == "no"){
            if(COINS < 2000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu();
            }
            else{COINS -= 2000; comp3 = "yes"; update(); companion_menu();}
        }
        else{COMPANION = 3; companion_menu();}
    }
    else if(X == "4"){ //gnome
        if(comp4 == "no"){
            if(COINS < 5000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu();
            }
            else{COINS -= 5000; comp4 = "yes"; update(); companion_menu();}
        }
        else{COMPANION = 4; companion_menu();}
    }
    else if(X == "5"){ //lizard
        if(comp5 == "no"){
            if(COINS < 6000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu();
            }
            else{COINS -= 6000; comp5 = "yes"; update(); companion_menu();}
        }
        else{COMPANION = 5; companion_menu();}
    }
    else{COMPANION = 0; companion_menu();}
}

void item_menu(){ //upgrade item menu
    do{
        system("clear");
        cout << BLUE << "  - UPGRADE ITEMS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Level up items to increase their effects\n" << RESET << endl;

        cout << GREEN << " (1):" << RESET << " Amulet of Undying: Level " << AoU.getLevel(); //AoU
        if(AoU.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
        else if(AoU.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
        else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}

        cout << GREEN << "\n (2):" << RESET << " Ring of Life: Level " << RoL.getLevel(); //RoL
        if(RoL.getLevel() == 1){cout << YELLOW << " (Upgrade for 200 coins)" << RESET;}
        else if(RoL.getLevel() == 2){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
        else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}

        cout << GREEN << "\n (3):" << RESET << " Staff of Power: Level " << SoP.getLevel(); //SoP
        if(SoP.getLevel() == 1){cout << YELLOW << " (Upgrade for 200 coins)" << RESET;}
        else if(SoP.getLevel() == 2){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
        else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}

        cout << GREEN << "\n (4):" << RESET << " Gauntlets of Strength: Level " << GoS.getLevel(); //GoS
        if(GoS.getLevel() == 1){cout << YELLOW << " (Upgrade for 200 coins)" << RESET;}
        else if(GoS.getLevel() == 2){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
        else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}

        if(numItems > 0){
            cout << GREEN << "\n (5):" << RESET << " Rune of Death: Level " << RoD.getLevel(); //RoD
            if(RoD.getLevel() == 1){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
            else if(RoD.getLevel() == 2){cout << YELLOW << " (Upgrade for 800 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(numItems > 1){
            cout << GREEN << "\n (6):" << RESET << " Cloak of Protection: Level " << CoP.getLevel(); //CoP
            if(CoP.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(CoP.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(numItems > 2){
            cout << GREEN << "\n (7):" << RESET << " Golden Talisman: Level " << G_T.getLevel(); //G_T
            if(G_T.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(G_T.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(numItems > 3){
            cout << GREEN << "\n (8):" << RESET << " Boots of the Elves: Level " << BotE.getLevel(); //BotE
            if(BotE.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(BotE.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(numItems > 4){
            cout << GREEN << "\n (9):" << RESET << " Wand of Heroes: Level " << BotE.getLevel(); //WoH
            if(WoH.getLevel() == 1){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
            else if(WoH.getLevel() == 2){cout << YELLOW << " (Upgrade for 800 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        cout << GREEN << "\n (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "9");

    if(X == "0"){boost_menu();}
    else if(X == "1"){ //amulet of undying
        if(AoU.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(AoU.getLevel() == 2){
            if(COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 500; AoU.setLevel(3); AoU.setStat(4); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 250; AoU.setLevel(2); AoU.setStat(2); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "2"){ //ring of life
        if(RoL.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(RoL.getLevel() == 2){
            if(COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 400; RoL.setLevel(3); RoL.setStat(6); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 200; RoL.setLevel(2); RoL.setStat(4); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "3"){ //staff of power
        if(SoP.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(SoP.getLevel() == 2){
            if(COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 400; SoP.setLevel(3); SoP.setStat(3); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 200; SoP.setLevel(2); SoP.setStat(2); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "4"){ //gauntlets of strength
        if(GoS.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(GoS.getLevel() == 2){
            if(COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 400; GoS.setLevel(3); GoS.setStat(5); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 200; GoS.setLevel(2); GoS.setStat(3); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "5" && numItems > 0){ //rune of death
        if(RoD.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(RoD.getLevel() == 2){
            if(COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 800; RoD.setLevel(3); RoD.setStat(10); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 400; RoD.setLevel(2); RoD.setStat(5); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "6" && numItems > 1){ //cloak of protection
        if(CoP.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(CoP.getLevel() == 2){
            if(COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 500; CoP.setLevel(3); CoP.setStat(3); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 250; CoP.setLevel(2); CoP.setStat(2); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "7" && numItems > 2){ //golden talisman
        if(G_T.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(G_T.getLevel() == 2){
            if(COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 500; G_T.setLevel(3); G_T.setStat(20); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 250; G_T.setLevel(2); G_T.setStat(15); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "8" && numItems > 3){ //boots of the elves
        if(BotE.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(BotE.getLevel() == 2){
            if(COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 500; BotE.setLevel(3); BotE.setStat(10); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 250; BotE.setLevel(2); BotE.setStat(5); update_items(); update(); item_menu();
            }
        }
    }
    else if(X == "9" && numItems > 4){ //wand of heroes
        if(WoH.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu();
        }
        else if(WoH.getLevel() == 2){
            if(COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 800; WoH.setLevel(3); WoH.setStat(10); update_items(); update(); item_menu();
            }
        }
        else{
            if(COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu();
            }
            else{
                COINS -= 400; WoH.setLevel(2); WoH.setStat(5); update_items(); update(); item_menu();
            }
        }
    }
    else{item_menu();} //in case of errors
}

void rebirth_menu(){ //controls player rebirth
    do{
        system("clear");
        cout << BLUE << "  - REBIRTH (Level: " << REBIRTH << ") -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Rebirth resets all your stats and progress, but increases your coin income\n" << endl;
        cout << RESET << GREEN << " (1):" << RESET << " Rebirth " << YELLOW << "(" << 1000 * pow(2, REBIRTH-1) << " Coins)\n" << RESET;
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "0"){boost_menu();}
    else{
        system("clear");
        if(COINS < 1000 * pow(2, REBIRTH-1)){
            cout << CYAN << " You don't have enough coins!\n" << RESET;
        }
        else{
            cout << YELLOW << " You are reborn!\n" << RESET;
            cout << " Your stats and progress have been reset\n";
            cout << " Your items and upgrades have been kept\n";
            REBIRTH++; PROGRESS = 0; COINS = 0; HP = 10; DMG = 1; FIRE = 0; ICE = 0; POISON = 0;
            ELECTRIC = 0; HEAL = 0; DODGE = 5; LUCK = 5; SHIELD = 0; CRITC = 5; CRITD = 2; update();
            this_thread::sleep_for(chrono::seconds(1));
        }
        this_thread::sleep_for(chrono::seconds(1));
        rebirth_menu();
    }
}

void too_poor(){ //function calls when players try to buy something too expensive
    system("clear"); cout << CYAN << "You don't have enough coins\n" << RESET;
    this_thread::sleep_for(chrono::seconds(1)); level_up();
}

void reset_enemy_status(){ //quickly set all enemy status to 0;
    for(int i = 0; i < 3; i++){enemy_status[i] = 0;}
}

void database(){ //enemy and status information
    do{
        system("clear");
        cout << BLUE << " - DATABASES -\n\n" << RESET;
        cout << GREEN << " (1): " << RESET << "Enemy Database\n";
        cout << GREEN << " (2): " << RESET << "Status Effect Database\n";
        cout << GREEN << " (0): " << RESET << "Return to Menu\n -> ";
        cin >> X;
    }while(X < "0" || X > "2");
    if(X == "0"){menu();}
    else if(X == "1"){ //enemy database
        system("clear");
        cout << BLUE << " - ENEMY DATABASE -\n\n" << RESET;
        if(PROGRESS == 0){
            cout << " No enemies unlocked yet\n\n";
        }
        if(PROGRESS > 0){
            cout << GREEN << " *" << RESET << " Evil Wizard - Crits more frequently, resistant to electric\n";
            cout << GREEN << " *" << RESET << " Fire Mage - Resistant to fire, vunerable to ice\n";
            cout << GREEN << " *" << RESET << " Ice Sorcerer - Resistant to ice, vulnerable to fire\n";
        }
        if(PROGRESS > 1){
            cout << GREEN << " *" << RESET << " Necromancer - Resistant to poison, vulnerable to electric\n";
        }
        if(PROGRESS > 2){
            cout << GREEN << " *" << RESET << " Defender - Dodges more frequently, vulnerable to poison\n";
        }
        if(PROGRESS > 3){
            cout << GREEN << " *" << RESET << " Stormcaster - Can stun player, resistant to electric\n";
        }
        if(PROGRESS > 4){
            cout << GREEN << " *" << RESET << " Unstable Mage - Deals high damage but injures themselves\n";
        }
        cout << RED << "\n [0]" << RESET << " Back to Databases\n\n -> ";
        cin >> X; database();
    }
    else{ //status database
        system("clear");
        cout << BLUE << " - ENEMY DATABASE -\n\n" << RESET;
        cout << GREEN << " *" << RESET << " Bleed - Take damage at end of turn\n";
        cout << GREEN << " *" << RESET << " Heal - Gain health at start of turn\n";
        cout << GREEN << " *" << RESET << " Shield - Block some damage for a turn\n";
        cout << GREEN << " *" << RESET << " Drained - Lose one spell option\n";
        cout << RED << "\n [0]" << RESET << " Back to Databases\n\n -> ";
        cin >> X; database();
    }

}

void encounter(){ //random encounters
    int factor = rand()%20; //get encounter type
    if(factor < 5){encounterType = "trap";} //25%
    else if(factor < 9){encounterType = "hp potion";} //20%
    else if(factor < 10){encounterType = "shop";} //5%
    else if(factor < 14){encounterType = "potion choice";} //20%
    else if(factor < 16){encounterType = "diamond";} //10%
    else if(factor < 18){encounterType = "item";} //10%
    else if(factor < 19){encounterType = "fairy";} //5%
    else{encounterType = "secret passage";} //5%

    if(encounterType == "trap"){
        factor = rand()%3;
        if(factor < 2){ //pit trap
            cout << RED << " You encounter a pit trap!\n\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%100 < luck){ //save
                cout << " You manage to leap over it in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it!" << RED << " -2 health!\n" << RESET; tempHP -= 2;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{ //arrow trap
            cout << RED << " You encounter an arrow trap!\n\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%100 < luck){ //save
                cout << " You manage to duck behind cover in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it!" << RED << " -4 health!\n" << RESET; tempHP -= 4;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "hp potion"){
        if(tempHP < health){
            cout << GREEN << " You find a health potion! It's refreshing!\n" << RESET;
            tempHP = health; this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << YELLOW << " You find a trinket! +10 Coins!\n" << RESET; COINS += 10;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "potion choice"){
        cout << MAGENTA << " You find a glittering potion with unknown properties...\n\n" << YELLOW;
        cout << GREEN << " (1):" << RESET << " Drink unknown potion\n " << GREEN << "(2): " << RESET << "Don't drink unknown potion\n\n -> ";
        cin >> X;
        if(X == "1"){
            if(rand()%100 < (20 + (luck/2))){ //stat boost
                factor = rand()%6;
                if(factor == 0){ //health
                    cout << endl << " Your health permanently increases!\n"; HP++; tempHP++; health++;
                }
                else if(factor == 1){ //damage
                    cout << endl << " Your damage permanently increases!\n"; DMG++; damage++;
                }
                else if(factor == 2){ //heal
                    cout << endl << " Your healing permanently increases!\n"; HEAL++; heal++;
                }
                else if(factor == 3){ //fire
                    cout << endl << " Your fire permanently increases!\n"; FIRE++; fire++;
                }
                else if(factor == 4){ //ice
                    cout << endl << " Your ice permanently increases!\n"; ICE++; ice++;
                }
                else if(factor == 5){ //electric
                    cout << endl << " Your electric permanently increases!\n"; ELECTRIC++; electric++;
                }
                else{ //poison
                    cout << endl << " Your poison permanently increases!\n"; POISON++; poison++;
                }
            }
            else{ //poison
                cout << endl << " You've been poisoned!" << RED << " -5 health!\n" << RESET; tempHP -= 5;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << endl << " Probably a smart choice...\n";
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "diamond"){
        cout << CYAN << " You notice a diamond by your foot. Shiny!\n" << RESET; DIAMONDS++;
        this_thread::sleep_for(chrono::milliseconds(game_speed));
    }

    else if(encounterType == "item"){
        if(itemCount() > 1){ //there are enough items
            Item x, y; int a, b; string c, d;
            string info = extra_item(numItems, items); //return two items
            c = info.at(0); d = info.at(1);
            a = stoi(c); b = stoi(d);
            if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
            else if(a == 3){x = GoS;} else if(a == 4){x = RoD;} else if(a == 5){x = CoP;}
            else if(a == 6){x = G_T;} else if(a == 7){x = BotE;} else{x = WoH;}
    
            if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
            else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
            else if(b == 6){y = G_T;} else if(b == 7){y = BotE;} else{y = WoH;}
    
            cout << BLUE << " You find an item!\n" << RESET << endl;
            cout << GREEN << " (1): " << RESET; x.print();
            cout << GREEN << "\n (2): " << RESET; y.print();
            cout << "\n\n -> ";
            cin >> X;
            if(X == "1"){items[a] = 1;
                if(a == 1){health+=RoL.getStat(); tempHP+=RoL.getStat();}//RoL
                else if(a == 2){fire+=SoP.getStat(); ice+=SoP.getStat();
                    poison+=SoP.getStat(); electric+=SoP.getStat();}//SoP
                else if(a == 3){damage+=GoS.getStat();}//GoS
                else if(a == 6){critc+=G_T.getStat();}//G_T
                else if(a == 7){dodge+=BotE.getStat();}//BotE
                else if(a == 8){shield+=WoH.getStat();}//WoH
            }
            else{items[b] = 1;
                if(b == 1){health+=RoL.getStat(); tempHP+=RoL.getStat();}//RoL
                else if(b == 2){fire+=SoP.getStat(); ice+=SoP.getStat();
                    poison+=SoP.getStat(); electric+=SoP.getStat();}//SoP
                else if(b == 3){damage+=GoS.getStat();}//GoS
                else if(b == 6){critc+=G_T.getStat();}//G_T
                else if(b == 7){dodge+=BotE.getStat();}//BotE
                else if(b == 8){shield+=WoH.getStat();}//WoH
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else if(itemCount() == 1){ //one item can be found
            int count;
            for(count = 0; items[count] == 1; count++);
            items[count] = 1;
            if(count == 0){cout << " You found the Amulet of Undying!\n";}
            else if(count == 1){cout << " You come across a Ring of Life!\n"; 
                health+=RoL.getStat(); tempHP+=RoL.getStat();}
            else if(count == 2){cout << " You found a Staff of Power!\n"; fire+=SoP.getStat();
                ice+=SoP.getStat(); poison+=SoP.getStat(); electric+=SoP.getStat();}
            else if(count == 3){cout << " You found the Gauntlets of Strength!\n"; damage+=GoS.getStat();}
            else if(count == 4){cout << " You pick up the Rune of Death!\n";}
            else if(count == 5){cout << " You found the Cloak of Protection!\n";}
            else if(count == 6){cout << " You discover a Golden Talisman!\n"; critc+=G_T.getStat();}
            else if(count == 7){cout << " You find the Wand of Heroes!\n"; shield+=WoH.getStat();}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{ //no more items
            cout << YELLOW << " You find some treasure! +40 Coins!\n" << RESET; COINS += 40;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "shop"){
        cout << MAGENTA << " You come across a strange merchant. He shows you his wares\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        cout << " Coins: " << YELLOW << COINS << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Health Potion " << YELLOW << " [50 Coins] " <<
            RESET << " (Health: "; 
            if(tempHP < health){cout << RED;}
            else{cout << GREEN;}
            cout << tempHP << RESET << "/" << GREEN << health << RESET << ")\n";
        cout << GREEN << " (2):" << RESET << " Ornate Dagger " << YELLOW << " [100 Coins]\n" << RESET;
        cout << GREEN << " (3):" << RESET << " Glittering Amulet " << YELLOW << " [500 Coins]\n" << RESET;
        cout << GREEN << " (0):" << RESET << " Buy Nothing\n -> ";
        cin >> X;
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        if(X != "0" && rand()%100 == 0){ //1% chance for merchant to curse player
            cout << BOLD << RED << "\n The merchant laughs, and casts a curse on you before vanishing\n" << RESET;
            damage -= 2; if(damage < 1){damage = 1;} health -= 2; if(tempHP > health){tempHP = health;}
        }
        else if(X == "1"){ //health potion
            if(COINS > 49){
                cout << "\n The potion tastes great!\n"; COINS -= 50; tempHP += (1+heal); health += (1+heal);
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; COINS++;
            }
            
        }
        else if(X == "2"){ //ornate dagger
            if(COINS > 99){
                cout << "\n The dagger looks like it will cause some damage!\n"; COINS -= 100; damage += 5;
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; COINS++;
            }    
        }
        else if(X == "3"){ //glittering amulet
            if(COINS > 499){
                cout << "\n The amulet is pulsing with power!\n"; COINS -= 500; damage += 10; health += 5;
                tempHP += 5; ice += 3; fire += 3; poison += 3; electric += 3; heal += 3; critc += 10; luck +=10;
                dodge += 10; critd += 10; shield++;
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; COINS++;
            }    
        }
        else{
            cout << "\n The merchant sighs, but lets you go on your way\n";
        }
        this_thread::sleep_for(chrono::milliseconds(game_speed));
    }

    else if(encounterType == "fairy"){
        cout << GREEN << " A little fairy lands on your shoulder, and gives you a blessing\n" << RESET;
        damage++; critd += 2; fire++; ice++; poison++; electric++;
        this_thread::sleep_for(chrono::milliseconds(game_speed));
    }

    else{ //secret passage
        if(level < 18){
            cout << GREEN << " You find a secret passage!\n" << RESET;
            level += (2+(rand()%3));
            if(level > 20){level = 19;}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << YELLOW << " You find a purse! +25 Coins!\n" << RESET; COINS += 25;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }
    cout << endl;
}

int itemCount(){ //find number of items still not equipped
    int count = 0;
    for(int i = 0; i < 8; i++){
        if(items[i] == 0){count++;}
    }
    return count;
}
