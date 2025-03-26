#include "spell.h"
#include "item.h"
#include <ctime>
#include <fstream>
#include <thread>

void menu(); void battle(); void store(); void how_to();
void fight(string factor); void database();
void level_up(); void settings(); void update();
void make_enemy(string factor); void encounter();
void output_level(string factor); int itemCount();
void show_card(Spell card); void too_poor();
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

//0, 1, 2, 3, 4, 5, 6, 7
Item AoU("Amulet of Undying", "Regain life after each battle", 0, 0), RoL("Ring of Life", "Boost health", 0, 0), 
SoP("Staff of Power", "Boost elements", 0, 0), GoS("Gauntlets of Strength", "Boost damage", 0, 0), 
RoD("Rune of Death", "Weaken enemy health", 0, 0), CoP("Cloak of Protection", "Reduce elemental damage", 0, 0),
G_T("Golden Talisman", "Boost crit chance", 0, 0), BotE("Boots of the Elves", "Boost dodge chance", 0, 0); 
int items[8]; //keeps track of which items player is using

Spell CARD1, CARD2, CARD3;
string X, eTYPE, store1, store2, eName, encounterType, t;
int HP, DMG, COINS, FIRE, ICE, POISON, HEAL, PROGRESS, eHP, eTempHP, eDMG, TURN, level, SHIELD, shield,
eFIRE, eICE, ePOISON, eHEAL, health, tempHP, damage, fire, ice, poison, heal, game_speed, LUCK, luck, 
DIAMONDS, CRITC, CRITD, critc, critd, eCRITC, eCRITD, DODGE, dodge, eDODGE, numItems, ELECTRIC, electric,
eELECTRIC, e, efactor; 

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
    infile >> waste >> temp; numItems = stoi(temp);
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
        cout << " (6): Enemy Database" << endl;
        cout << " (0): [Exit Game]" << endl << endl;
        cout << " -> ";
        cin >> X;
        system("clear");
    }while(X < "0" || X > "6");

    if(X == "1"){battle();} //play the game
    else if(X == "2"){level_up();} //go to level up menu
    else if(X == "3"){store();} //go to store
    else if(X == "4"){how_to();} //how to play
    else if(X == "5"){settings();} //go to settings
    else if(X == "6"){database();} //go to enemy database
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
        if(PROGRESS > 2){cout << " (4): Desolate Wastes" << endl;} //only show after mountain of despair completed
        cout << " (0): [Menu]" << endl << endl << " -> ";
        cin >> X;
    }while(X < "0" || X > "4");
    if(X == "0"){menu();}
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    if(X == "1"){fight(X);} //misty dungeon
    else if(X == "2" && PROGRESS > 0){fight(X);} //ruined castle
    else if(X == "3" && PROGRESS > 1){fight(X);} //mountain of despair
    else if(X == "4" && PROGRESS > 2){fight(X);} //desolate wastes
}

void fight(string factor){ //fight function
    int random;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    health = tempHP = HP; damage = DMG; fire = FIRE; ice = ICE; poison = POISON; heal = HEAL; TURN = 0; level = 1;
    critc = CRITC; critd = CRITD; dodge = DODGE; luck = LUCK; shield = SHIELD; electric = ELECTRIC;
    
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
                cout << " Reward: " << level*5 << " coins!\n" << endl; //give player reward
                COINS += (level*5);
                random = (rand() % 3); //player has chance to get a diamond
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
                    cout << " 1) Damage Boost (current: " << damage << ")\n" <<
                    " 2) Health Boost (current: " << tempHP << "/" << health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){damage++; cout << "\n Damage increased!\n\n";}
                    else{health++; tempHP+=2; if(tempHP > health){tempHP = health;} cout << "\n Health increased!\n\n";}
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
                    cout << "Reward: 750 Coins\n" << endl; //player reward
                    COINS += 750;
                    random = (rand() % 2);
                    if(random == 0){DIAMONDS += 2;
                    cout << "You have found 2 diamonds!\n" << endl;}
                    if(PROGRESS == 2){
                        cout << "Desolate Wastes: unlocked!\n" << endl;
                        PROGRESS = 3; //unlock mountain of despaiir
                        this_thread::sleep_for(chrono::milliseconds(game_speed));
                    } //if first time completed
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
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
                cout << " Reward: " << level*40 << " coins!\n" << endl; //give reward
                COINS += (level*40);
                random = (rand() % 3); //diamond chance
                if(random == 0){DIAMONDS += 2;
                cout << " You have found 2 diamonds!\n";}
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
                    cout << "Reward: 800 Coins\n" << endl; //player reward
                    COINS += 800;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){DIAMONDS += 3;
                        cout << "You have found 3 diamonds!\n" << endl;}
                    this_thread::sleep_for(chrono::milliseconds(game_speed));
                    if(PROGRESS == 3){ //first time completed
                        PROGRESS = 4; //unlock next?
                    }
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

}

void player(string factor){ //player turn
    CARD1.get_card(health, damage, fire, ice, poison, electric, heal); //generate first spell
    CARD2.get_card(health, damage, fire, ice, poison, electric, heal); //generate second spell
    CARD3.get_card(health, damage, fire, ice, poison, electric, heal); //generate third spell
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
    t = card.getType(); e = card.getEffect();
    if(t == "attack" || t == "fire" || t == "ice" || t == "poison" || t == "electric"){ //attack spell
        if(t == "fire" && eTYPE == "Ice"){e+=fire;} //ice sorcerer is weak to fire
        if(t == "fire" && eTYPE == "Fire"){e-=fire;} //fire mage is fire resistant
        if(t == "ice" && eTYPE == "Fire"){e+=ice;} //fire mage is weak to ice
        if(t == "ice" && eTYPE == "Ice"){e-=ice;} //ice sorcerer is ice resistant
        if(t == "poison" && eTYPE == "Necro"){e-=poison;} //Necro is poison resistant
        if(t == "poison" && eTYPE == "Defend"){e+=poison;} //defender is weak to poison
        if(t == "electric" && eTYPE == "Wizard"){e-=electric;} //Wizard is electric resistant
        if(t == "electric" && eTYPE == "Necro"){e+=electric;} //Necro is weak to poison
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
        if(rand()%2 == 0){ //trigger stun
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << endl << " Enemy is stunned!\n"; TURN = 2;
        }
    }
    else if(t == "atk-stun"){ //attack(stun) spell
        if(rand()%110 < eDODGE){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            eTempHP -= e; TURN = 2; //deal damage, trigger stun
            cout << endl << " You stun your enemy, dealing " << e << " damage!\n";}
    }
    else if(t == "ice-stun"){ //ice(stun) spell
        if(rand()%105 < eDODGE){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            eTempHP -= e; //deal damage
            cout << endl << " You deal " << e << " ice damage!\n";
            if(rand()%4 == 0){this_thread::sleep_for(chrono::milliseconds(game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else if(t == "electric-stun"){ //electric(stun) spell
        if(rand()%105 < eDODGE){cout << "\n " << eName << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < critc+5){e += critd; cout << "\n * CRITICAL HIT! *\n"; 
                this_thread::sleep_for(chrono::milliseconds(game_speed));} //crits
            eTempHP -= e; //deal damage
            cout << endl << " You deal " << e << " electric damage!\n";
            if(rand()%10 < 3){this_thread::sleep_for(chrono::milliseconds(game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else{ //drain spell
        eTempHP -= e; //damage
        tempHP += e; //heal
        if(tempHP > health){tempHP = health;} //can't go over max
        cout << endl << " You drain " << e << " life from the enemy!\n";
    }
}

void calculate_enemy(){ //calculate what spell enemy casts
    if(eTYPE == "Wizard"){ //evil wizard
        efactor = rand()%11;
        if(efactor < 6){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";} //player dodges
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; 
                    cout << " " << eName << " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 7){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " <<
                    eName << " deals " << eDMG + eCRITD + eFIRE << " *critiacl* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 8){ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eICE << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 9){ //poison
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + ePOISON);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + ePOISON + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 10){ //electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eELECTRIC);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
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
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 9){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD + eFIRE << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
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
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName << 
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else{ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eICE + eDMG + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
    }
    else if(eTYPE == "Necro"){ //necromancer
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 5){ //poison
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + ePOISON);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << ePOISON + eDMG + eCRITD << " *critical* poison damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + ePOISON << " poison damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 6){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
        else{ //drain
            tempHP -= (1 + ((eDMG + eHEAL) / 2));
            eTempHP += (1 + ((eDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
    else if(eTYPE == "Defend"){ //defender
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 2){ //fire
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eFIRE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eFIRE + eCRITD << " *critical* fire damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eFIRE << " fire damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                 cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 3){ //ice
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eICE);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eICE + eCRITD << " *critical* ice damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eICE << " ice damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else if(efactor < 7){ //heal
            eTempHP += eHEAL;
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " heals themself for " << eHEAL << " health!\n";
        }
        else if(efactor < 8){ //electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eELECTRIC);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else{ //drain
            tempHP -= (1 + ((eDMG + eHEAL) / 2));
            eTempHP += (1 + ((eDMG + eHEAL) / 2));
            if(eTempHP > eHP){eTempHP = eHP;}
            cout << " " << eName << " drains " << (1 + ((eDMG + eHEAL) / 2)) << " life from you!\n";
        }
    }
    else if(eTYPE == "Storm"){
        efactor = rand()%10;
        if(efactor < 2){ //attack
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= eDMG;
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eCRITD << " *critical* damage!\n";}
                else{cout << " " << eName << " deals " << eDMG << " damage!\n";}}
        }
        else if(efactor < 9){//electric
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eELECTRIC);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
        }
        else{//stun
            if(rand()%100 < dodge+5){cout << " You dodge an attack!\n";}
            else{tempHP -= (eDMG + eELECTRIC);
                if(rand()%100 < eCRITC){tempHP -= eCRITD; cout << " " << eName <<
                    " deals " << eDMG + eELECTRIC + eCRITD << " *critical* electric damage!\n";}
                else{cout << " " << eName << " deals " << eDMG + eELECTRIC << " electric damage!\n";}}
            if(items[5] == 1){tempHP++; this_thread::sleep_for(chrono::milliseconds(game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            cout << "\n The shock from the spell leaves you stunned...\n"; TURN = 3;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
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
    else if(card.getType() == "ice-stun"){ //ice stun spell
        cout << "Deal " << card.getEffect() << " ice damage. 25% chance to stun enemy\n";
    }
    else if(card.getType() == "poison"){ //poison spell
        cout << "Deal " << card.getEffect() << " poison damage\n";
    }
    else if(card.getType() == "electric"){ //electric spell
        cout << "Deal " << card.getEffect() << " electric damage\n";
    }
    else if(card.getType() == "electric-stun"){ //electric stun spell
        cout << "Deal " << card.getEffect() << " electric damage. 30% chance to stun enemy\n";
    }
    else if(card.getType() == "heal"){ //healing spell
        cout << "Gain " << card.getEffect() << " health. 50% chance to stun enemy\n";
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
    else if(factor == "3"){ //mountain of despair
        cout << "    - MOUNTAIN OF DESPAIR: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Watcher of the Pass -\n";}
        if(level == 20){cout << "  - Dweller in the Deep -\n";}
    }
    else{ //desolate waste
        cout << "    - DESOLATE WASTES: LEVEL " << level << " -\n" << endl;
        if(level == 10){cout << "  - Lord of the Dunes -\n";}
        if(level == 20){cout << "  - King of the Wastes -\n";}
    }
    cout << "  " << eName; //show enemy name
    if(eTYPE == "Wizard"){cout << " - Evil Wizard: ";} //these show enemy type
    else if(eTYPE == "Fire"){cout << " - Fire Mage: ";}
    else if(eTYPE == "Ice"){cout << " - Ice Sorcerer: ";}
    else if(eTYPE == "Necro"){cout << " - Necromancer: ";}
    else if(eTYPE == "Storm"){cout << " - Stormcaster: ";}
    else{cout << " - Defender: ";}
    cout << "[Health: " << eTempHP << "/" << eHP << "]" << endl << endl; //show enemy health
    if(items[0] == 1){ cout << "       - Equipped: Amulet of Undying -\n";}
    if(items[1] == 1){ cout << "       - Equipped: Ring of Life -\n";}
    if(items[2] == 1){ cout << "       - Equipped: Staff of Power -\n";}
    if(items[3] == 1){ cout << "       - Equipped: Gauntlets of Strength -\n";}
    if(items[4] == 1){ cout << "       - Equipped: Rune of Death -\n";}
    if(items[5] == 1){ cout << "       - Equipped: Cloak of Protection -\n";}
    if(items[6] == 1){ cout << "       - Equipped: Golden Talisman -\n";}
    if(items[7] == 1){ cout << "       - Equipped: Boots of the Elves -\n";}
    cout << "       [Health: " << tempHP << "/" << health << "] [Damage: " << damage << "] [Fire: " << fire <<
    "] [Ice: " << ice << "] [Poison: " << poison << "]" << endl <<" You:  [Electric: " << electric <<
    "] [Heal: " << heal << "] [Crit Chance: " << critc << "%] [Crit Damage: " << critd << "]" << endl <<
    "       [Dodge: " << dodge << "%] [Shield: " << shield << "] [Luck: " << luck << "%]\n\n"; //player info
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

    if(items[4] == 1){eHP -= RoD.getStat();} //rune of death
    if((eDMG - shield) < 0){eDMG = 0;} //apply shield
    else{eDMG -= shield;}
}

void level_up(){ //level up menu
    system("clear");
    do{
    cout << "    - LEVEL UP -" << endl << endl;
    cout << "Select stat to increase" << endl;
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
    if(FIRE < 5){cout << "40 Coins]" << endl;}
    else if(FIRE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (4): Ice: " << ICE << "           ["; //ice and varied cost
    if(ICE < 5){cout << "40 Coins]" << endl;}
    else if(ICE < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;} 

    cout << " (5): Poison: " << POISON << "        ["; //poison and varied cost
    if(POISON < 5){cout << "40 Coins]" << endl;}
    else if(POISON < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (6): Electric: " << ELECTRIC << "      ["; //poison and varied cost
    if(ELECTRIC < 5){cout << "40 Coins]" << endl;}
    else if(ELECTRIC < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (7): Heal: " << HEAL << "          ["; //heal and varied cost
    if(HEAL < 5){cout << "50 Coins]" << endl;}
    else if(HEAL < 10){cout << "100 Coins]" << endl;}
    else{cout << "200 Coins]" << endl;}

    cout << " (8): Crit Chance: " << CRITC << "%  ["; //crit chance and varied cost
    if(CRITC < 10){cout << "50 Coins]" << endl;}
    else if(CRITC < 20){cout << "75 Coins]" << endl;}
    else if(CRITC < 60){cout << "150 Coins]" << endl;}
    else{cout << "MAX]" << endl;}

    cout << " (9): Crit Damage: " << CRITD << "   ["; //crit damage and varied cost
    if(CRITD < 7){cout << "50 Coins]" << endl;}
    else if(CRITD < 10){cout << "150 Coins]" << endl;}
    else{cout << "300 Coins]" << endl;}

    cout << " (10): Dodge: " << DODGE << "%       ["; //crit chance and varied cost
    if(DODGE < 10){cout << "30 Coins]" << endl;}
    else if(DODGE < 15){cout << "80 Coins]" << endl;}
    else if(DODGE < 40){cout << "120 Coins]" << endl;}
    else{cout << "MAX]\n";}

    cout << " (11): Shield: " << SHIELD << "        ["; //shield
    if(SHIELD == 0){cout << "250 Coins]" << endl;}
    else if(SHIELD < 3){cout << "500 Coins]" << endl;}
    else{cout << "MAX]\n";}

    cout << " (12): Luck: " << LUCK << "%        ["; //shield
    if(LUCK < 75){cout << "10 Coins]" << endl;}
    else{cout << "MAX]\n";}

    cout << "\n (0): [Menu]" << endl << endl;
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
        cout << " (4): Second Starting Item ";
        if(store2 == "no"){cout << " [750 Coins]\n";} //can be bought
        else{cout << "*Already Purchased*\n";} //already bought
        cout << " (0): Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "4");
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
            DIAMONDS -= 5; HP += 2; DMG += 2; FIRE += 2; ICE += 2; POISON += 2; HEAL += 2; CRITD += 2; ELECTRIC += 2;
            update(); system("clear"); cout << " Stats have been boosted\n"; 
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{ //too poor
            system("clear"); cout << "You don't have enough diamonds\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
    }
    else if(X == "3"){item_shop();}
    else if(X == "4"){
        if(store2 == "yes"){ //already own second item
            system("clear"); cout << "You already own this upgrade\n";
            this_thread::sleep_for(chrono::seconds(1)); store();
        }
        else{
            if(COINS > 749){ //buy game speed upgrade
                DIAMONDS -= 750; store2 = "yes";
                update(); store();
            }
            else{system("clear"); cout << "You don't have enough coins\n";
                this_thread::sleep_for(chrono::seconds(1)); store();}
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
            HP=10; DMG=1; FIRE=0; ICE=0; POISON=0; HEAL=0; COINS=0; PROGRESS = 0; CRITC = 5; CRITD = 2; ELECTRIC = 0;
            game_speed = 1000; store1 = "no"; DIAMONDS = 0; numItems = 0; DODGE = 5; LUCK = 5; SHIELD = 0;
            store2 = "no"; update(); reset_items(); settings();
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
    endl << "Diamonds: " << DIAMONDS << endl << "Items: " << numItems << endl;
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
    for(int i = 0; i < 8; i++){ //reset items
        items[i] = 0;
    }
    Item x, y, z; int a, b, c; string d, e, f;
    string info = get_item(numItems); //return three items
    d = info.at(0); e = info.at(1); f = info.at(2);
    a = stoi(d); b = stoi(e); c = stoi(f);
    if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
    else if(a == 3){x = GoS;} else if(a == 4){x = RoD;} else if(a == 5){x = CoP;}
    else if(a == 6){x = G_T;} else{x = BotE;}

    if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
    else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
    else if(b == 6){y = G_T;} else{y = BotE;}

    if(c == 0){z = AoU;} else if(c == 1){z = RoL;} else if(c == 2){z = SoP;} 
    else if(c == 3){z = GoS;} else if(c == 4){z = RoD;} else if(c == 5){z = CoP;}
    else if(c == 6){z = G_T;} else{z = BotE;}
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

    if(store2 == "yes"){ //if second item upgrade owned
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        system("clear");
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        info = extra_item(numItems, items); //return two items
        d = info.at(0); e = info.at(1);
        a = stoi(d); b = stoi(e);
        if(a == 0){x = AoU;} else if(a == 1){x = RoL;} else if(a == 2){x = SoP;}
        else if(a == 3){x = GoS;} else if(a == 4){x = RoD;} else if(a == 5){x = CoP;}
        else if(a == 6){x = G_T;} else{x = BotE;}
    
        if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
        else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
        else if(b == 6){y = G_T;} else{y = BotE;}
    
        cout << " Select Second Item\n" << endl;
        cout << " (1): "; x.print();
        cout << "\n (2): "; y.print();
        cout << "\n\n -> ";
        cin >> X;
        if(X == "1"){items[a] = 1;}
        else{items[b] = 1;}
    }
}

void item_shop(){ //buy items
    do{
        system("clear");
        cout << "  - ITEM SHOP -\n" << endl;
        cout << "DIAMONDS: " << DIAMONDS << endl << endl;
        if(numItems < 4){cout << " (1): Unlock Next Item [4 Diamonds]\n";}
        else{cout << " (-): All Items Unlocked\n";}
        cout << " (0): Back To Store\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "1"){
        if(numItems == 4){ //already own all items
            system("clear"); cout << "Currently no items to buy\n";
            this_thread::sleep_for(chrono::seconds(1)); item_shop();
        }
        else{
            if(DIAMONDS < 4){ //too poor
                system("clear"); cout << "You don't have enough diamonds\n";
                this_thread::sleep_for(chrono::seconds(1)); item_shop(); 
            }
            else{ //buy next item
                system("clear");
                DIAMONDS -=4;
                if(numItems == 0){ //rune of death
                    cout << " Acquired: Rune of Death!\n";
                }
                else if(numItems == 1){ //cloak of protection
                    cout << " Acquired: Cloak of Protection!\n";
                }
                else if(numItems == 2){ //golden talisman
                    cout << " Acquired: Golden Talisman!\n";
                }
                else{ //boots of the elves
                    cout << " Acquired: Boots of the Elves!\n";
                }
                numItems++; update();
                this_thread::sleep_for(chrono::seconds(1)); item_shop(); 
            }
        }
    }
    else{store();}
}

void too_poor(){ //function calls when players try to buy something too expensive
    system("clear"); cout << "You don't have enough coins\n";
    this_thread::sleep_for(chrono::seconds(1)); level_up();
}

void database(){ //enemy information
    system("clear");
    cout << " - ENEMY DATABASE -\n\n";
    if(PROGRESS == 0){
        cout << " No enemies unlocked yet\n\n";
    }
    if(PROGRESS > 0){
        cout << " * Evil Wizard - Crits more frequently, resistant to electric\n";
        cout << " * Fire Mage - Resistant to fire, vunerable to ice\n";
        cout << " * Ice Sorcerer - Resistant to ice, vulnerable to fire\n";
    }
    if(PROGRESS > 1){
        cout << " * Necromancer - Resistant to poison, vulnerable to electric\n";
    }
    if(PROGRESS > 2){
        cout << " * Defender - Dodges more frequently, vulnerable to poison\n";
    }
    if(PROGRESS > 3){
        cout << " * Stormcaster - Can stun player, resistant to electric\n";
    }
    cout << "\n [0] Back to Menu\n\n -> ";
    cin >> X; menu();
}

void encounter(){ //random encounters
    int factor = rand()%20; //get encounter type
    if(factor < 5){encounterType = "trap";} //25%
    else if(factor < 9){encounterType = "hp potion";} //20%
    else if(factor < 10){encounterType = "shop";} //5%
    else if(factor < 14){encounterType = "potion choice";} //20%
    else if(factor < 16){encounterType = "diamond";} //10%
    else if(factor < 18){encounterType = "item";} //10%
    else{encounterType = "secret passage";} //10%

    if(encounterType == "trap"){
        factor = rand()%3;
        if(factor < 2){ //pit trap
            cout << " You encounter a pit trap!\n\n";
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%100 < luck){ //save
                cout << " You manage to leap over it in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it! -2 health!\n"; tempHP -= 2;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{ //arrow trap
            cout << " You encounter an arrow trap!\n\n";
            this_thread::sleep_for(chrono::milliseconds(game_speed));
            if(rand()%100 < luck){ //save
                cout << " You manage to duck behind cover in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it! -4 health!\n"; tempHP -= 4;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "hp potion"){
        if(tempHP < health){
            cout << " You find a health potion! It's refreshing!\n";
            tempHP = health; this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << " You find a trinket! +10 Coins!\n"; COINS += 10;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "potion choice"){
        cout << " You find a glittering potion with unknown properties...\n\n";
        cout << " (1): Drink unknown potion\n (2): Don't drink unknown potion\n\n -> ";
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
                cout << endl << " You've been poisoned! -5 health!\n"; tempHP -= 5;
            }
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << endl << " Probably a smart choice...\n";
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "diamond"){
        cout << " You notice a diamond by your foot. Shiny!\n"; DIAMONDS++;
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
            else if(a == 6){x = G_T;} else{x = BotE;}
    
            if(b == 0){y = AoU;} else if(b == 1){y = RoL;} else if(b == 2){y = SoP;} 
            else if(b == 3){y = GoS;} else if(b == 4){y = RoD;} else if(b == 5){y = CoP;}
            else if(b == 6){y = G_T;} else{y = BotE;}
    
            cout << " You find an item!\n" << endl;
            cout << " (1): "; x.print();
            cout << "\n (2): "; y.print();
            cout << "\n\n -> ";
            cin >> X;
            if(X == "1"){items[a] = 1;
                if(a == 1){health+=RoL.getStat(); tempHP+=RoL.getStat();}//RoL
                else if(a == 2){fire+=SoP.getStat(); ice+=SoP.getStat();
                    poison+=SoP.getStat(); electric+=SoP.getStat();}//SoP
                else if(a == 3){damage+=GoS.getStat();}//GoS
                else if(a == 6){critc+=G_T.getStat();}//G_T
                else if(a == 7){dodge+=BotE.getStat();}//BotE
            }
            else{items[b] = 1;
                if(b == 1){health+=RoL.getStat(); tempHP+=RoL.getStat();}//RoL
                else if(b == 2){fire+=SoP.getStat(); ice+=SoP.getStat();
                    poison+=SoP.getStat(); electric+=SoP.getStat();}//SoP
                else if(b == 3){damage+=GoS.getStat();}//GoS
                else if(b == 6){critc+=G_T.getStat();}//G_T
                else if(b == 7){dodge+=BotE.getStat();}//BotE
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
            else{cout << " You found some Boots of the Elves!\n"; dodge+=BotE.getStat();}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{ //no more items
            cout << " You find some treasure! +40 Coins!\n"; COINS += 40;
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
    }

    else if(encounterType == "shop"){
        cout << " You come across a strange merchant. He shows you his wares\n\n";
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        cout << " Coins: " << COINS << endl;
        cout << " (1): Health Potion [50 Coins] (Health: " << tempHP << "/" << health << ")\n";
        cout << " (2): Ornate Dagger [100 Coins]\n";
        cout << " (3): Glittering Amulet [500 Coins]\n";
        cout << " (0): Buy Nothing\n -> ";
        cin >> X;
        this_thread::sleep_for(chrono::milliseconds(game_speed));
        if(X != "0" && rand()%100 == 0){ //1% chance for merchant to curse player
            cout << "\n The merchant laughs, and casts a curse on you before vanishing\n";
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

    else{ //secret passage
        if(level < 18){
            cout << " You find a secret passage!\n";
            level += (2+(rand()%3));
            if(level > 20){level = 19;}
            this_thread::sleep_for(chrono::milliseconds(game_speed));
        }
        else{
            cout << " You find a purse! +25 Coins!\n"; COINS += 25;
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
