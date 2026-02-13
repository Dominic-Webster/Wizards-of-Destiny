/**
 * WIZARDS OF DESTINY
 * @author: Dominic Webster
 * @version: 3.2.0
 * @brief: controls the main game
 */

#include "player.h"
#include "enemy.h"
#include "colors.h"
#include "item.h"
#include <ctime>
#include <cmath>
#include <fstream>
#include <thread>

void battle(Player player); 
void boon_menu(Player player); 
void boost_menu(Player player);
void calculate(Spell card, Player player, Enemy enemy); 
void calculate_comp(Player player, Enemy enemy); 
void calculate_enemy(Player player, Enemy enemy);
void companion_menu(Player player); 
void database(Player player); 
void encounter(Player player, int levNum);
void endless_mode(Player player);
string enemy_name(); 
void enemy_turn(string factor, Player player, Enemy enemy, int levNum); 
void fight(string factor, Player player); 
void how_to(Player player);
int itemCount();
void item_menu(Player player);
void item_shop(Player player); 
void level_up(Player player); 
void make_enemy(string factor, Player player, int levNum); 
void menu(Player player); 
void output_level(string factor, Player player, Enemy enemy, int levNum); 
void pick_item(Player player);
void player_turn(string factor, Player player, Enemy enemy, int levNum); 
void rebirth_menu(Player player);
void reset_enemy_status();
void reset_items();
void settings(Player player);
void show_card(Spell card); 
void store(Player player); 
void too_poor(Player player);
void update_items();

//0, 1, 2, 3, 4, 5, 6, 7, 8
Item AoU("Amulet of Undying", "Regain life after each battle", 0, 0), 
RoL("Ring of Life", "Boost health", 0, 0), 
SoP("Staff of Power", "Boost elements", 0, 0), 
GoS("Gauntlets of Strength", "Boost damage", 0, 0), 
RoD("Rune of Death", "Weaken enemy health", 0, 0), 
CoP("Cloak of Protection", "Reduce elemental damage", 0, 0),
G_T("Golden Talisman", "Boost crit chance", 0, 0), 
BotE("Boots of the Elves", "Boost dodge chance", 0, 0),
WoH("Wand of Heroes", "Boost shield", 1, 1); 
int items[9]; //keeps track of which items player is using

string encounterType, t;
int TURN, e, efactor;

int main(int argc, char const *argv[]){
    srand(time(0)); //seeds random to time
    string temp, waste;
    Player player;

    ifstream infile;
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
    menu(player);
}

void menu(Player player){ //game menu
    string X;
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

    if(X == "1"){battle(player);} //play the game
    else if(X == "2"){level_up(player);} //go to level up menu
    else if(X == "3"){boost_menu(player);} //boons/companions/rebirth
    else if(X == "4"){store(player);} //go to store
    else if(X == "5"){how_to(player);} //how to play
    else if(X == "6"){settings(player);} //go to settings
    else if(X == "7"){database(player);} //go to enemy database
    else{player.update(); update_items(); exit(0);} //save and exit
}

void battle(Player player){ //adventure menu
    string X;
    do{
        system("clear");
        cout << BLUE << "    - PLAY -" << RESET << endl << endl;
        cout << " Select Adventure" << endl << endl;
        cout << GREEN << " (1):" << RESET << " ENDLESS MODE (Record: " << player.ENDLESS << ")\n"; 
        cout << GREEN << " (2):" << RESET << " Misty Dungeon" << endl;
        if(player.PROGRESS > 0){cout << GREEN << " (3):" << RESET << " Ruined Castle" << endl;} //only show after misty dungeon completed
        if(player.PROGRESS > 1){cout << GREEN << " (4):" << RESET << " Mountain of Despair" << endl;} //only show after ruined castle completed
        if(player.PROGRESS > 2){cout << GREEN << " (5):" << RESET << " Desolate Wastes" << endl;} //only show after mountain of despair completed
        if(player.PROGRESS > 3){cout << GREEN << " (6):" << RESET << " Cursed Mines" << endl;} //only show after desolate wastes completed
        cout << GREEN << " (0):" << RESET << " [Menu]" << endl << endl << " -> ";
        cin >> X;
    }while(X < "0" || X > "5");
    if(X == "0"){menu(player);}
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    if(X == "1"){endless_mode(player);} //endless
    else if(X == "2"){fight("1", player);} //misty dungeon
    else if(X == "3" && player.PROGRESS > 0){fight("2", player);} //ruined castle
    else if(X == "4" && player.PROGRESS > 1){fight("3", player);} //mountain of despair
    else if(X == "5" && player.PROGRESS > 2){fight("4", player);} //desolate wastes
    else if(X == "6" && player.PROGRESS > 3){fight("5", player);} //cursed mines
}

void fight(string factor, Player player){ //fight function
    int random, level = 1;
    string X;
    Enemy enemy;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    player.health = player.tempHP = player.HP; player.damage = player.DMG; player.fire = player.FIRE; player.ice = player.ICE; player.poison = player.POISON; player.heal = player.HEAL; TURN = 0;
    player.critc = player.CRITC; player.critd = player.CRITD; player.dodge = player.DODGE; player.luck = player.LUCK; player.shield = player.SHIELD; player.electric = player.ELECTRIC;

    //sets all status effects to off
    player.reset_status();
    enemy.reset_status();
    
    pick_item(player); //get starting item
    if(items[1] == 1){ //Ring of Life
        player.health += RoL.getStat();
        player.tempHP = player.health;
    }
    if(items[3] == 1){ //Gauntlets of Strength
        player.damage += GoS.getStat();
    }
    if(items[2] == 1){ //Staff of Power
        player.fire += SoP.getStat();
        player.ice += SoP.getStat();
        player.poison += SoP.getStat();
        player.electric += SoP.getStat();
    }
    if(items[6] == 1){ //Golden Talisman
        player.critc += G_T.getStat();
    }
    if(items[7] == 1){ //Boots of the Elves
        player.dodge += BotE.getStat();
    }
    if(items[8] == 1){ //Wand of Heroes
        player.shield += WoH.getStat();
    }
    this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly

    //Misty Dungeon
    if(factor == "1"){
        while(level < 21){ //runs through dungeon
            enemy.make_enemy(factor, player, level); //create this level's enemy

            if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
            if(enemy.health < 1){enemy.health = 1;}

            enemy.tempHP = enemy.health; //set enemy temp health
            while(player.tempHP > 0 && enemy.tempHP > 0){ //runs through battle
                if(TURN == 0){ //player turn
                    player_turn(factor, player, enemy, level);
                    if(TURN == 2){TURN = 0;} //when enemy is stunned
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy_turn(factor, player, enemy, level);
                    if(TURN == 3){TURN = 1;} //when player is stunned
                    else{TURN = 0;}
                }
            }
            if(player.tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly
                cout << " Reward: " << YELLOW << level*5*player.REBIRTH << " coins!\n" << RESET << endl; //give player reward
                player.COINS += (level*5*player.REBIRTH);
                random = (rand() % 3); //player has chance to get a diamond
                if(random == 0){player.DIAMONDS++;
                    cout << CYAN << " You have found a diamond!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly
                cout << GREEN << "[1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                player.update(); battle(player); //back to play menu
            }
            else{ //proceed to next level
                system("clear");
                enemy.reset_status();
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                if(items[0] == 1 && level != 20 && player.tempHP < player.health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    player.tempHP += AoU.getStat();
                    if(player.tempHP > player.health){player.tempHP = player.health;} //make sure doesn't go over max hp
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 5){ //level 5 cleared gives stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage++; cout << "\n Damage increased!\n\n";}
                    else{player.health++; player.tempHP+=3; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 10){ //level 10 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                    " 2) Fire Boost (current: " << player.fire << ")\n" <<
                    " 3) Poison Boost (current: " << player.poison << ")\n" <<
                    " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.ice++; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){player.fire++; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){player.poison++; cout << "\n Poison increased!\n\n";}
                    else{player.electric++; cout << "\n Electric increased!\n\n";}
                        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 15){ //level 15 cleared stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 2; cout << "\n Damage increased!\n\n";}
                    else{player.health += 2; player.tempHP += 5;
                        if(player.tempHP > player.health){player.tempHP = player.health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 20){ //dungeon cleared
                    cout << "You've cleared the Misty Dungeon!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << "Reward: " << YELLOW << 250*player.REBIRTH << " Coins\n" << RESET << endl; //completion reward
                    player.COINS += 250*player.REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){player.DIAMONDS++;
                        cout << CYAN << "You have found a diamond!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    if(player.PROGRESS == 0){ //if first time completing
                        cout << "Ruined Castle: unlocked!\n" << endl;
                        player.PROGRESS = 1; //unlock ruined castle
                        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    player.update(); battle(player); //save and return to play menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter(player, level);}
                }
                if(player.tempHP > 0){cout << " Descending further into the dungeon...\n"; 
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
                level++; TURN = 0; //set turn to players, increase dungeon level
            }
        }
    }

    //Ruined Castle
    if(factor == "2"){
        while(level < 21){ //runs until reaches end
            enemy.make_enemy(factor, player, level); //create this level's enemy

            if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
            if(enemy.health < 1){enemy.health = 1;}
            
            enemy.tempHP = enemy.health; //set enemy temp health
            while(player.tempHP > 0 && enemy.tempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player_turn(factor, player, enemy, level);
                    if(TURN == 2){TURN = 0;} //enemy stunned
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy_turn(factor, player, enemy, level);
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(player.tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << " Reward: " << YELLOW << level*10*player.REBIRTH << " coins!\n" << RESET << endl; //give reward
                player.COINS += (level*10*player.REBIRTH);
                random = (rand() % 4); //diamond chance
                if(random == 0){player.DIAMONDS++;
                    cout << CYAN << " You have found a diamond!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                player.update(); battle(player); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                enemy.reset_status();
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                if(items[0] == 1 && level != 20 && player.tempHP < player.health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    player.tempHP += AoU.getStat();
                    if(player.tempHP > player.health){player.tempHP = player.health;} //make sure health doesn't go over
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 2; cout << "\n Damage increased!\n\n";}
                    else{player.health += 2; player.tempHP += 4; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                    " 2) Fire Boost (current: " << player.fire << ")\n" <<
                    " 3) Poison Boost (current: " << player.poison << ")\n" <<
                    " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.ice += 2; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){player.fire += 2; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){player.poison += 2; cout << "\n Poison increased!\n\n";}
                    else{player.electric += 2; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 4; cout << "\n Damage increased!\n\n";}
                    else{player.health += 3; player.tempHP += 6; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << "Reward: " << YELLOW << 500*player.REBIRTH << " Coins\n" << RESET << endl; //player reward
                    player.COINS += 500*player.REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){player.DIAMONDS += 2;
                        cout << CYAN << "You have found 2 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    if(player.PROGRESS == 1){ //first time completed
                        cout << "Mountain of Despair: unlocked!\n" << endl;
                        player.PROGRESS = 2; //unlock mountain of despaiir
                        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    player.update(); battle(player); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter(player, level);}
                }
                if(player.tempHP > 0){cout << " Descending further into the ruins...\n";
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
                level++; TURN = 0; //go to next level, set turn to player
            }
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        while(level < 21){ //runs to end of adventure
            enemy.make_enemy(factor, player, level); //create this level's enemy

            if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
            if(enemy.health < 1){enemy.health = 1;}
            
            enemy.tempHP = enemy.health; //set enemy temp health
            while(player.tempHP > 0 && enemy.tempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player_turn(factor, player, enemy, level);
                    if(TURN == 2){TURN = 0;} //enemy stunned
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy_turn(factor, player, enemy, level);
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(player.tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << " Reward: " << YELLOW << level*20*player.REBIRTH << " coins!\n" << RESET << endl; //player reward
                player.COINS += (level*20*player.REBIRTH);
                random = (rand() % 4); //diamond chance
                if(random == 0){player.DIAMONDS += 2;
                    cout << CYAN << " You have found 2 diamonds\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                player.update(); battle(player); //save and return to menu
            }
            else{ //player defeated level
                system("clear");
                enemy.reset_status();
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                if(items[0] == 1 && level != 20 && player.tempHP < player.health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    player.tempHP += AoU.getStat();
                    if(player.tempHP > player.health){player.tempHP = player.health;}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 4; cout << "\n Damage increased!\n\n";}
                    else{player.health += 4; player.tempHP += 6; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                    " 2) Fire Boost (current: " << player.fire << ")\n" <<
                    " 3) Poison Boost (current: " << player.poison << ")\n" <<
                    " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.ice += 4; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){player.fire += 4; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){player.poison += 4; cout << "\n Poison increased!\n\n";}
                    else{player.electric += 4; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 6; cout << "\n Damage increased!\n\n";}
                    else{player.health += 6; player.tempHP += 9; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 20){ //mountain cleared
                    cout << "You've cleared the Mountain of Despair!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << "Reward: " << YELLOW << 750*player.REBIRTH << " Coins\n" << RESET << endl; //player reward
                    player.COINS += 750*player.REBIRTH;
                    random = (rand() % 2);
                    if(random == 0){player.DIAMONDS += 2;
                    cout << CYAN << "You have found 2 diamonds!\n" << RESET << endl;}
                    if(player.PROGRESS == 2){
                        cout << "Desolate Wastes: unlocked!\n" << endl;
                        player.PROGRESS = 3; //unlock desolate wastes
                        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    } //if first time completed
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    player.update(); battle(player); //save and go to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter(player, level);}
                }
                if(player.tempHP > 0){cout << " Descending further into the mountain...\n";
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
                level++; TURN = 0; //level increase and turn set to player
            }
        }
    }

    //Desolate Wastes
    if(factor == "4"){
        while(level < 21){ //runs until reaches end
            enemy.make_enemy(factor, player, level); //create this level's enemy

            if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
            if(enemy.health < 1){enemy.health = 1;}
            
            enemy.tempHP = enemy.health; //set enemy temp health
            while(player.tempHP > 0 && enemy.tempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player_turn(factor, player, enemy, level);
                    if(TURN == 2){TURN = 0;} //enemy stunned
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy_turn(factor, player, enemy, level);
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(player.tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << " Reward: " << YELLOW << level*40*player.REBIRTH << " coins!\n" << RESET << endl; //give reward
                player.COINS += (level*40*player.REBIRTH);
                random = (rand() % 3); //diamond chance
                if(random == 0){player.DIAMONDS += 2;
                    cout << CYAN << " You have found 2 diamonds!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << GREEN << " [1]: " << RESET << "Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                player.update(); battle(player); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                enemy.reset_status();
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                if(items[0] == 1 && level != 20 && player.tempHP < player.health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    player.tempHP += AoU.getStat();
                    if(player.tempHP > player.health){player.tempHP = player.health;} //make sure health doesn't go over
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 6; cout << "\n Damage increased!\n\n";}
                    else{player.health += 6; player.tempHP += 9; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                    " 2) Fire Boost (current: " << player.fire << ")\n" <<
                    " 3) Poison Boost (current: " << player.poison << ")\n" <<
                    " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.ice += 5; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){player.fire += 5; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){player.poison += 5; cout << "\n Poison increased!\n\n";}
                    else{player.electric += 5; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 7; cout << "\n Damage increased!\n\n";}
                    else{player.health += 8; player.tempHP += 10; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << "Reward: " << YELLOW << 800*player.REBIRTH << " Coins\n" << RESET << endl; //player reward
                    player.COINS += 800*player.REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){player.DIAMONDS += 3;
                        cout << CYAN << "You have found 3 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    if(player.PROGRESS == 3){ //first time completed
                        cout << "Cursed Mines: unlocked!\n" << endl;
                        player.PROGRESS = 4; //unlock cursed mines
                        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    player.update(); battle(player); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%6 == 0){encounter(player, level);}
                }
                if(player.tempHP > 0){cout << " Descending further into the wastes...\n";
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
                level++; TURN = 0; //go to next level, set turn to player
            }
        }
    }

    //Cursed Mines
    if(factor == "5"){
        while(level < 21){ //runs until reaches end
            enemy.make_enemy(factor, player, level); //create this level's enemy

            if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
            if(enemy.health < 1){enemy.health = 1;}
            
            enemy.tempHP = enemy.health; //set enemy temp health
            while(player.tempHP > 0 && enemy.tempHP > 0){ //runs till someone is defeated
                if(TURN == 0){ //player turn
                    player_turn(factor, player, enemy, level);
                    if(TURN == 2){TURN = 0;} //enemy stunned
                    else{TURN = 1;}
                }
                else{ //enemy turn
                    enemy_turn(factor, player, enemy, level);
                    if(TURN == 3){TURN = 1;} //player stunned
                    else{TURN = 0;}
                }
            }
            if(player.tempHP < 1){ //player lost
                system("clear");
                cout << " You have been defeated\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << " Reward: " << YELLOW << level*50*player.REBIRTH << RESET << " coins!\n" << endl; //give reward
                player.COINS += (level*50*player.REBIRTH);
                random = (rand() % 3); //diamond chance
                if(random == 0){player.DIAMONDS += 2;
                    cout << CYAN << " You have found 2 diamonds!\n\n" << RESET;}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                player.update(); battle(player); //save and return to menu
            }
            else{ //player beat level
                system("clear");
                enemy.reset_status();
                cout << " Enemy defeated!\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                if(items[0] == 1 && level != 20 && player.tempHP < player.health){ //Amulet of Undying
                    cout << " Amulet of Undying activates\n" << endl;
                    player.tempHP += AoU.getStat();
                    if(player.tempHP > player.health){player.tempHP = player.health;} //make sure health doesn't go over
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 5){ //level 5 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 7; cout << "\n Damage increased!\n\n";}
                    else{player.health += 6; player.tempHP += 12; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 10){ //level 10 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                    " 2) Fire Boost (current: " << player.fire << ")\n" <<
                    " 3) Poison Boost (current: " << player.poison << ")\n" <<
                    " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.ice += 5; cout << "\n Ice increased!\n\n";}
                    else if(X == "2"){player.fire += 5; cout << "\n Fire increased!\n\n";}
                    else if(X == "3"){player.poison += 5; cout << "\n Poison increased!\n\n";}
                    else{player.electric += 5; cout << "\n Electric increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 15){ //level 15 stat boost
                    cout << "Choose upgrade:\n\n";
                    cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                    " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                    cin >> X;
                    if(X == "1"){player.damage += 7; cout << "\n Damage increased!\n\n";}
                    else{player.health += 8; player.tempHP += 14; 
                        if(player.tempHP > player.health){player.tempHP = player.health;} 
                        cout << "\n Health increased!\n\n";}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                }
                if(level == 20){ //castle cleared
                    cout << "You've cleared the Ruined Castle!\n" << endl;
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    cout << "Reward: " << YELLOW << 900*player.REBIRTH << " Coins\n" << RESET << endl; //player reward
                    player.COINS += 900*player.REBIRTH;
                    random = (rand() % 2); //diamond chance
                    if(random == 0){player.DIAMONDS += 3;
                        cout << CYAN << "You have found 3 diamonds!\n" << RESET << endl;}
                    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    if(player.PROGRESS == 4){ //first time completed
                        player.PROGRESS = 5; //unlock next?
                    }
                    cout << GREEN << "\n [1]:" << RESET << " Return to Menu\n\n -> ";
                    cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                    player.update(); battle(player); //save and exit to menu
                }
                if(level != 5 && level != 10 && level != 15){ //random encounter
                    if(rand()%7 == 0){encounter(player, level);}
                }
                if(player.tempHP > 0){cout << " Descending deeper into the mines...\n";
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
                level++;//go to next level
                if(rand()%4 == 0){TURN = 1;} //25% chance enemy goes first
                else{TURN = 0;} //75% chance player goes first
            }
        }
    }

}

void player_turn(string factor, Player player, Enemy enemy, int levNum){ //player turn
    string X;
    player.CARD1.get_card(player.health, player.damage, player.fire, player.ice, player.poison, player.electric, player.heal); //generate first spell
    player.CARD2.get_card(player.health, player.damage, player.fire, player.ice, player.poison, player.electric, player.heal); //generate second spell
    player.CARD3.get_card(player.health, player.damage, player.fire, player.ice, player.poison, player.electric, player.heal); //generate third spell

    //reset any neccesary status effects
    player.status[1] = 0; //shield

    system("clear");
    //start of turn status effects
    if(player.status[2] != 0){ //heal
        cout << ITALIC << GREEN << " You heal for " << player.status[2] << " health\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        player.tempHP += player.status[2];
        if(player.tempHP > player.health){player.tempHP = player.health;}
        player.status[2] = 0;
    }

    do{
    system("clear");
    output_level(factor, player, enemy, levNum); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
    cout << " Your turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
    cout << GREEN << " 1) " << RESET; show_card(player.CARD1); //these show the spells
    cout << GREEN << " 2) " << RESET; show_card(player.CARD2);
    if(player.status[3] == 0){cout << GREEN << " 3) " << RESET; show_card(player.CARD3);} //weakened
    cout << "\n -> ";
    cin >> X;
    }while(X < "1" || X > "3"); //until player selects spell
    this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
    if(X == "1"){calculate(player.CARD1, player, enemy);} //calculate spell player chose
    else if(X == "2"){calculate(player.CARD2, player, enemy);}
    else if(X == "3"){calculate(player.CARD3, player, enemy);}
    this_thread::sleep_for(chrono::milliseconds(player.game_speed));

    //end of turn status effects
    system("clear");
    if(player.status[0] != 0){ //bleed
        cout << ITALIC << RED << " You bleed for " << player.status[0] << " damage\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        player.tempHP -= player.status[0];
        if(player.tempHP < 1){
            cout << ITALIC << RED << " You succumb to your wounds\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        }
        player.status[0] = 0;
    }

    //reset any neccesary status effects
    player.status[3] = 0; //drained
}

void enemy_turn(string factor, Player player, Enemy enemy, int levNum){ //enemy turn
    //reset any neccesary status effects
    enemy.status[1] = 0; //shield

    system("clear");
    //start of turn status effects
    if(enemy.status[2] != 0){ //heal
        cout << ITALIC << GREEN << " " << enemy.name << " heals for " << enemy.status[2] << " health\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        enemy.tempHP += enemy.status[2];
        if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
        enemy.status[2] = 0;
    }
    system("clear");
    output_level(factor, player, enemy, levNum); //show level, enemy, and player info
    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
    cout << " Enemy's turn\n" << endl;
    this_thread::sleep_for(chrono::milliseconds(player.game_speed));
    calculate_enemy(player, enemy); //calculate what spell enemy casts
    this_thread::sleep_for(chrono::milliseconds(player.game_speed));

    //end of turn status effects
    system("clear");
    if(enemy.status[0] != 0){ //bleed
        cout << ITALIC << RED << " " << enemy.name << " bleeds for " << enemy.status[0] << " damage\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        enemy.tempHP -= enemy.status[0];
        if(enemy.tempHP < 1){
            cout << ITALIC << RED << " They succumb to their wounds\n\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait
        }
        enemy.status[0] = 0;
    }
}

void calculate(Spell card, Player player, Enemy enemy){ //calculate player spell results
    bool critted = false;
    t = card.getType(); e = card.getEffect();
    if(t == "attack" || t == "fire" || t == "ice" || t == "poison" || t == "electric" || t == "poison-heal" || t == "atk-bleed"){ //attack spell
        if(t == "fire" && enemy.type == "Ice"){e+=player.fire;} //ice sorcerer is weak to fire
        if(t == "fire" && enemy.type == "Fire"){e-=player.fire;} //fire mage is fire resistant
        if(t == "ice" && enemy.type == "Fire"){e+=player.ice;} //fire mage is weak to ice
        if(t == "ice" && enemy.type == "Ice"){e-=player.ice;} //ice sorcerer is ice resistant
        if(t == "poison" && enemy.type == "Necro"){e-=player.poison;} //Necro is poison resistant
        if(t == "poison-heal" && enemy.type == "Necro"){e-=player.poison;} //Necro is poison resistant
        if(t == "poison" && enemy.type == "Defend"){e+=player.poison;} //defender is weak to poison
        if(t == "poison-heal" && enemy.type == "Defend"){e+=player.poison;} //defender is weak to poison
        if(t == "electric" && enemy.type == "Wizard"){e-=player.electric;} //Wizard is electric resistant
        if(t == "electric" && enemy.type == "Necro"){e+=player.electric;} //Necro is weak to electric
        if(rand()%100 < enemy.dodge && player.BOON != 2){cout << "\n " << enemy.name << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < player.critc+5){e += player.critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));} //crits
            e -= enemy.status[1]; if(e < 0){e = 0;} //enemy shield status
            enemy.tempHP -= e; //decrease enemy health
            if(t == "attack"){cout << endl << " You deal " << e << " damage!\n";} //show results
            else if(t == "atk-bleed"){cout << endl << " You deal " << e << " damage and apply bleed!\n";} //show results
            else if(t == "poison-heal"){cout << endl << " You deal " << e << " poison damage and gain heal!\n";} //show results
            else{cout << endl << " You deal " << e << " " << t << " damage!\n";}} //show results

            if(t == "poison-heal"){player.status[2] = player.poison; if(player.poison == 0){player.status[2] = 1;}} //poison/heal spell
            if(t == "atk-bleed"){enemy.status[0] = 1 + rand()%e;} //mystic slash
    }
    else if(t == "heal"){ //healing spell
        player.tempHP += e;
        if(player.tempHP > player.health){player.tempHP = player.health;} //can't go over max
        cout << endl << " You heal yourself for " << e << " health!\n";
        if(rand()%2 == 0){ //trigger stun
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            cout << endl << " Enemy is stunned!\n"; TURN = 2;
        }
    }
    else if(t == "heal-shield"){ //protective barrier spell
        player.tempHP += e;
        if(player.tempHP > player.health){player.tempHP = player.health;} //can't go over max
        cout << endl << " You heal yourself for " << e << " health, and throw up a magic barrier!\n";
        player.status[1] = e-1; if(e == 1){player.status[1] = 1;}
    }
    else if(t == "atk-stun"){ //attack(stun) spell
        if(rand()%110 < enemy.dodge && player.BOON != 2){cout << "\n " << enemy.name << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < player.critc+5){e += player.critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));} //crits
            e -= enemy.status[1]; if(e < 0){e = 0;} //enemy shield status
            enemy.tempHP -= e; TURN = 2; //deal damage, trigger stun
            cout << endl << " You stun your enemy, dealing " << e << " damage!\n";}
    }
    else if(t == "ice-stun"){ //ice(stun) spell
        if(enemy.type == "Fire"){e+=player.ice;} //fire mage is weak to ice
        if(enemy.type == "Ice"){e-=player.ice;} //ice sorcerer is ice resistant
        if(rand()%105 < enemy.dodge && player.BOON != 2){cout << "\n " << enemy.name << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < player.critc+5){e += player.critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));} //crits
            e -= enemy.status[1]; if(e < 0){e = 0;} //enemy shield status
            enemy.tempHP -= e; //deal damage
            cout << endl << " You deal " << e << " ice damage!\n";
            if(rand()%4 == 0){this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else if(t == "electric-stun"){ //electric(stun) spell
        if(enemy.type == "Necro"){e+=player.electric;} //Necro is weak to electric
        if(enemy.type == "Wizard"){e-=player.electric;} //Wizard is electric resistant
        if(rand()%105 < enemy.dodge && player.BOON != 2){cout << "\n " << enemy.name << " dodges your attack!\n";} //enemy dodge
        else{if(rand()%100 < player.critc+5){e += player.critd; cout << "\n * CRITICAL HIT! *\n"; critted = true;  
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));} //crits
            e -= enemy.status[1]; if(e < 0){e = 0;} //enemy shield status
            enemy.tempHP -= e; //deal damage
            cout << endl << " You deal " << e << " electric damage!\n";
            if(rand()%10 < 3){this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                TURN = 2; cout << "\n Enemy Stunned!\n";}
        }
    }
    else if(t == "trick"){ //trickery spell
        cout << endl << " Magic washes over you and your enemy!\n";
        enemy.status[0] = e;
        player.status[1] = e;
        player.status[2] = e;
    }
    else{ //drain spell
        e -= enemy.status[1]; if(e < 1){e = 1;} //enemy shield status
        if(enemy.tempHP < e){
            player.tempHP += enemy.tempHP;
            enemy.tempHP -= e;
            if(player.tempHP > player.health){player.tempHP = player.health;} //can't go over max
            cout << endl << " You drain the life from your enemy!\n";
        }
        else{
            enemy.tempHP -= e; //damage
            player.tempHP += e; //heal
            if(player.tempHP > player.health){player.tempHP = player.health;} //can't go over max
            cout << endl << " You drain " << e << " life from the enemy!\n";
        }
    }

    if(critted == true){ //a critical hit happened
        if(player.BOON == 3 && player.tempHP < player.health){ //booon of the trickster
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            cout << YELLOW << "\n The Trickster's blessing heals you\n" << RESET;
            if(player.heal < 6){player.tempHP += 3;}
            else{player.tempHP += player.heal/2;}
            if(player.tempHP > player.health){player.tempHP = player.health;}
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }

    if(player.COMPANION != 0){calculate_comp(player, enemy);} //companions
}

void calculate_comp(Player player, Enemy enemy){ //calculate companion effects
    if(player.COMPANION == 1){ //fairy
        if(player.tempHP < player.health){
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            cout << "\n Fairy blesses you with health\n";
            if(player.heal < 4){player.tempHP += 2;}
            else{player.tempHP += player.heal/2;}
            if(player.tempHP > player.health){player.tempHP = player.health;}
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }
    else if(player.COMPANION == 2){ //imp
        if(enemy.tempHP > 0){
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            cout << "\n Imp strikes at your enemy\n";
            enemy.tempHP -= player.damage/2;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }
    else if(player.COMPANION == 3){ //pixie
        if(enemy.tempHP > 0 && TURN != 2){
            if(rand()%5 == 0){
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Pixie stuns your enemy\n"; TURN = 2;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            }
        }
    }
    else if(player.COMPANION == 4){ //gnome
        if(rand()%3 == 0){
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            if(rand()%8 == 0){
                cout << CYAN << "\n Gnome discovers a diamond!\n" << RESET; player.DIAMONDS++;
            }
            else{
                cout << "\n Gnome finds some treasure! +" << 25*player.REBIRTH << " Coins!\n"; player.COINS += 25*player.REBIRTH;
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }
    else{ //lizard
        if(rand()%3 == 0){
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            if(rand()%2 == 0 && enemy.status[0] == 0){
                cout << CYAN << "\n Lizard bites at the enemy, applying bleed!\n" << RESET;
                enemy.status[0] = (rand()%player.damage) + 1;
            }
            else if(player.status[2] == 0){
                cout << "\n Lizard grants you heal\n";
                player.status[2] = (rand()%(player.heal + 1)) + 1;
            }
            else{
                cout << "\n Lizard scurries around your feet. +2 health\n";
                player.tempHP+=2; if(player.tempHP > player.health){player.tempHP = player.health;}
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }
}

void calculate_enemy(Player player, Enemy enemy){ //calculate what spell enemy casts
    int tempDMG = enemy.damage - player.status[1]; if(tempDMG < 0){tempDMG = 0;} //player shield status
    if(enemy.type == "Wizard"){ //evil wizard
        efactor = rand()%11;
        if(efactor < 6){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";} //player dodges
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; 
                    cout << " " << enemy.name << " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else if(efactor < 7){ //fire
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.fire);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " <<
                   enemy.name << " deals " << enemy.damage + enemy.critd + enemy.fire << " *critical* fire damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.fire << " fire damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 8){ //ice
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.ice);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd + enemy.ice << " *critical* ice damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.ice << " ice damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 9){ //poison
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.poison);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.poison + enemy.critd << " *critical* poison damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.poison << " poison damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 10 || enemy.tempHP == enemy.health){ //electric
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.electric);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.electric + enemy.critd << " *critical* electric damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.electric << " electric damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //heal
            enemy.tempHP += enemy.heal;
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " heals themself for " << enemy.heal << " health!\n";
        }
    }
    else if(enemy.type == "Fire"){ //fire mage
        efactor = rand()%10;
        if(efactor < 3){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else if(efactor < 9 || enemy.tempHP == enemy.health){ //fire
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.fire);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd + enemy.fire << " *critical* fire damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.fire << " fire damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //heal
            enemy.tempHP += enemy.heal;
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " heals themself for " << enemy.heal << " health!\n";
        }
    }
    else if(enemy.type == "Ice"){ //ice sorcerer
        efactor = rand()%10;
        if(efactor < 4){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name << 
                    " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else{ //ice
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.ice);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.ice + enemy.damage + enemy.critd << " *critical* ice damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.ice << " ice damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
    }
    else if(enemy.type == "Necro"){ //necromancer
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else if(efactor < 5){ //poison
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.poison);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.poison + enemy.damage + enemy.critd << " *critical* poison damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.poison << " poison damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 6 || enemy.tempHP == enemy.health){ //heal
            enemy.tempHP += enemy.heal;
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " heals themself for " << enemy.heal << " health!\n";
        }
        else{ //drain
            player.tempHP -= (1 + ((tempDMG + enemy.heal) / 2));
            enemy.tempHP += (1 + ((tempDMG + enemy.heal) / 2));
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " drains " << (1 + ((enemy.damage + enemy.heal) / 2)) << " life from you!\n";
        }
    }
    else if(enemy.type == "Defend"){ //defender
        efactor = rand()%11;
        if(efactor < 1){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else if(efactor < 2){ //fire
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.fire);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.fire + enemy.critd << " *critical* fire damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.fire << " fire damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                 cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 3){ //ice
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.ice);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.ice + enemy.critd << " *critical* ice damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.ice << " ice damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else if(efactor < 7 && enemy.tempHP < enemy.health){ //heal
            enemy.tempHP += enemy.heal;
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " heals themself for " << enemy.heal << " health!\n";
        }
        else if(efactor < 8){ //electric
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.electric);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.electric + enemy.critd << " *critical* electric damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.electric << " electric damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{ //drain
            player.tempHP -= (1 + ((tempDMG + enemy.heal) / 2));
            enemy.tempHP += (1 + ((tempDMG + enemy.heal) / 2));
            if(enemy.tempHP > enemy.health){enemy.tempHP = enemy.health;}
            cout << " " << enemy.name << " drains " << (1 + ((enemy.damage + enemy.heal) / 2)) << " life from you!\n";
        }
    }
    else if(enemy.type == "Storm"){ //stormcaster
        efactor = rand()%10;
        if(efactor < 2){ //attack
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= tempDMG;
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}}
        }
        else if(efactor < 9){//electric
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.electric);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.electric + enemy.critd << " *critical* electric damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.electric << " electric damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";}} //cloak of protection
        }
        else{//stun
            if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
            else{player.tempHP -= (tempDMG + enemy.electric);
                if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                    " deals " << enemy.damage + enemy.electric + enemy.critd << " *critical* electric damage!\n";}
                else{cout << " " << enemy.name << " deals " << enemy.damage + enemy.electric << " electric damage!\n";}
            if(items[5] == 1){player.tempHP+=CoP.getStat(); this_thread::sleep_for(chrono::milliseconds(player.game_speed));
                cout << "\n Cloak of Protection activates\n";} //cloak of protection
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            cout << "\n The shock from the spell leaves you stunned...\n"; TURN = 3;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
        }    
    }
    else if(enemy.type == "Unstable"){ //unstable mage
        if(rand()%100 < player.dodge+5){cout << " You dodge an attack!\n";}
        else{player.tempHP -= tempDMG;
            if(rand()%100 < enemy.critc && player.BOON != 1){player.tempHP -= enemy.critd; cout << " " << enemy.name <<
                " deals " << enemy.damage + enemy.critd << " *critical* damage!\n";}
            else{cout << " " << enemy.name << " deals " << enemy.damage << " damage!\n";}
        }
        //mage takes damage
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        int unstable_damage = rand() % (enemy.damage + enemy.critd) + 1;
        cout << "\n " << enemy.name << " injuress themselves with their unstable magic!\n";
        cout << " They take " << unstable_damage << " damage\n";
        enemy.tempHP -= unstable_damage;
    }

    //fix any cloak of protection overheals
    if(player.tempHP > player.health){player.tempHP = player.health;}

    //enemy apply status effects
    int stat_chance = 0;
    if(enemy.type == "Wizard"){stat_chance = 6;}
    else if(enemy.type == "Fire" || enemy.type == "Storm"){stat_chance = 2;}
    else if(enemy.type == "Ice" || enemy.type == "Defend"){stat_chance = 3;}
    else if(enemy.type == "Necro" || enemy.type == "Unstable"){stat_chance = 4;}

    if(rand()%10 < stat_chance){ //applies stats
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        int z = rand()%4;
        if(z == 0 && player.BOON != 4){ //enemy heal
            cout << "\n " << enemy.name << " gains heal\n";
            enemy.status[2] = rand()%enemy.heal + 1;
        }
        else if(z == 1 && player.BOON != 4){ //enemy shield
            cout << "\n " << enemy.name << " gains shield\n";
            enemy.status[1] = rand()%enemy.heal + 1;
        }
        else if(z == 2){ //player bleed
            cout << "\n " << enemy.name << " applies bleed\n";
            player.status[0] = rand()%enemy.damage + 1;
        }
        else if(z == 3){ //player weakened
            cout << "\n " << enemy.name << " applies drained\n";
            player.status[3] = 1;
        }
        else{ //fails to apply any stauts effects
            cout << "\n " << enemy.name << " yells an insult at you\n";
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

void output_level(string factor, Player player, Enemy enemy, int levNum){ //show level player is on
    if(factor == "X"){ //endless mode
        cout << BOLD << BLUE << "    - ENDLESS MODE: LEVEL " << levNum << " (Record: " << player.ENDLESS << ") -\n" << RESET << endl;
        if(levNum%50 == 0){cout << "  - Demigod -\n";}
        else if(levNum%10 == 0){cout << "  - Archmage -\n";}
        else if(levNum%5 == 0){cout << "  - Great Wizard -\n";}
    }
    else if(factor == "1"){ //misty dungeon
        cout << BOLD << CYAN << "    - MISTY DUNGEON: LEVEL " << levNum << " -\n" << RESET << endl;
        if(levNum == 10){cout << "  - Guardian of the Tomb -\n";}
        if(levNum == 20){cout << "  - Master of the Dungeon -\n";}
    }
    else if(factor == "2"){ //ruined castle
        cout << MAGENTA << "    - RUINED CASTLE: LEVEL " << levNum << " -\n" << RESET << endl;
        if(levNum == 10){cout << "  - Upholder of Justice -\n";}
        if(levNum == 20){cout << "  - Lord of the Tower -\n";}
    }
    else if(factor == "3"){ //mountain of despair
        cout << RED << "    - MOUNTAIN OF DESPAIR: LEVEL " << levNum << " -\n" << RESET << endl;
        if(levNum == 10){cout << "  - Watcher of the Pass -\n";}
        if(levNum == 20){cout << "  - Dweller in the Deep -\n";}
    }
    else if(factor == "4"){ //desolate waste
        cout << BOLD << YELLOW << "    - DESOLATE WASTES: LEVEL " << levNum << " -\n" << RESET << endl;
        if(levNum == 10){cout << "  - Lord of the Dunes -\n";}
        if(levNum == 20){cout << "  - King of the Wastes -\n";}
    }
    else{ //cursed mines
        cout << BOLD << MAGENTA << "    - CURSED MINES: LEVEL " << levNum << " -\n" << RESET << endl;
        if(levNum == 10){cout << "  - Captain of the Depths -\n";}
        if(levNum == 20){cout << "  - Ruler of the Deep -\n";}
    }
    cout << BOLD << "  " << enemy.name << RESET; //show enemy name
    if(enemy.type == "Wizard"){cout << " - Evil Wizard: ";} //these show enemy type
    else if(enemy.type == "Fire"){cout << RED << " - Fire Mage: " << RESET;}
    else if(enemy.type == "Ice"){cout << BLUE << " - Ice Sorcerer: " << RESET;}
    else if(enemy.type == "Necro"){cout << MAGENTA << " - Necromancer: " << RESET;}
    else if(enemy.type == "Storm"){cout << YELLOW << " - Stormcaster: " << RESET;}
    else if(enemy.type == "Unstable"){cout << BOLD << RED << " - Unstable Mage: " << RESET;}
    else{cout << " - Defender: ";}
    cout << "[Health: "; if(enemy.tempHP < enemy.health){cout << RED;} else{cout << GREEN;}
    cout << enemy.tempHP << RESET << "/" << GREEN << enemy.health << RESET << "]" << endl; //show enemy health
    cout << YELLOW << ITALIC << "  Status Effects:\n"; //enemy status effects
    if(enemy.status[0] != 0){cout << RED << "   - Bleed " << enemy.status[0] << endl;}
    if(enemy.status[1] != 0){cout << BLUE << "   - Shield " << enemy.status[1] << endl;}
    if(enemy.status[2] != 0){cout << GREEN << "   - Heal " << enemy.status[2] << endl;}

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
    if(player.COMPANION != 0){
        cout << CYAN;
        if(player.COMPANION == 1){cout << "       - Companion: Fairy -\n";}
        if(player.COMPANION == 2){cout << "       - Companion: Imp -\n";}
        if(player.COMPANION == 3){cout << "       - Companion: Pixie -\n";}
        if(player.COMPANION == 4){cout << "       - Companion: Gnome -\n";}
        if(player.COMPANION == 5){cout << "       - Companion: Lizard -\n";}
    }
    if(player.BOON != 0){
        cout << YELLOW;
        if(player.BOON == 1){cout << "       - Boon of the Guardian -\n";}
        if(player.BOON == 2){cout << "       - Boon of the Warrior -\n";}
        if(player.BOON == 3){cout << "       - Boon of the Trickster -\n";}
        if(player.BOON == 3){cout << "       - Boon of the Strategist -\n";}
    }
    cout << RESET;
    cout << "       [Health: "; if(player.tempHP < player.health){cout << RED;} else{cout << GREEN;}
    cout << player.tempHP << RESET << "/" << GREEN << player.health << RESET << "] [Damage: " << player.damage << "] [Fire: " << player.fire <<
    "] [Ice: " << player.ice << "] [Poison: " << player.poison << "]" << endl <<" You:  [Electric: " << player.electric <<
    "] [Heal: " << player.heal << "] [Crit Chance: " << player.critc << "%] [Crit Damage: " << player.critd << "]" << endl <<
    "       [Dodge: " << player.dodge << "%] [Shield: " << player.shield << "] [Luck: " << player.luck << "%]\n"; //player info
    cout << YELLOW << ITALIC << "       Status Effects:\n"; //player status effects
    if(player.status[0] != 0){cout << RED << "        - Bleed " << player.status[0] << endl;}
    if(player.status[1] != 0){cout << BLUE << "        - Shield " << player.status[1] << endl;}
    if(player.status[2] != 0){cout << GREEN << "        - Heal " << player.status[2] << endl;}
    if(player.status[3] != 0){cout << RED << "        - Drained" << endl;}
    cout << RESET << endl;
}

void endless_mode(Player player){ //endless game mode
    int random, endlessNum = 1;
    string X;
    Enemy enemy;
    //set play stats equal to base stats (they can be modified without messing with base stats)
    player.health = player.tempHP = player.HP; player.damage = player.DMG; player.fire = player.FIRE; 
    player.ice = player.ICE; player.poison = player.POISON; player.heal = player.HEAL; TURN = 0;
    player.critc = player.CRITC; player.critd = player.CRITD; player.dodge = player.DODGE; player.luck = player.LUCK; 
    player.shield = player.SHIELD; player.electric = player.ELECTRIC;
    
    //sets all status effects to off
    player.reset_status();
    enemy.reset_status();

    pick_item(player); //get starting item
    if(items[1] == 1){ //Ring of Life
        player.health += RoL.getStat();
        player.tempHP = player.health;
    }
    if(items[3] == 1){ //Gauntlets of Strength
        player.damage += GoS.getStat();
    }
    if(items[2] == 1){ //Staff of Power
        player.fire += SoP.getStat();
        player.ice += SoP.getStat();
        player.poison += SoP.getStat();
        player.electric += SoP.getStat();
    }
    if(items[6] == 1){ //Golden Talisman
        player.critc += G_T.getStat();
    }
    if(items[7] == 1){ //Boots of the Elves
        player.dodge += BotE.getStat();
    }
    if(items[8] == 1){ //Wand of Heroes
        player.shield += WoH.getStat();
    }
    this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly

    while(player.tempHP > 0){
        enemy.make_enemy("X", player, endlessNum); //create this level's enemy

        if(items[4] == 1){enemy.health -= RoD.getStat();} //rune of death
        if(enemy.health < 1){enemy.health = 1;}

        enemy.tempHP = enemy.health; //set enemy temp health
        while(player.tempHP > 0 && enemy.tempHP > 0){ //runs through battle
            if(TURN == 0){ //player turn
                player_turn("X", player, enemy, endlessNum);
                if(TURN == 2){TURN = 0;} //when enemy is stunned
                else{TURN = 1;}
            }
            else{ //enemy turn
                enemy_turn("X", player, enemy, endlessNum);
                if(TURN == 3){TURN = 1;} //when player is stunned
                else{TURN = 0;}
            }
        }
    
        if(player.tempHP < 1){ //player lost
            system("clear");
            cout << " You have been defeated\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly
            if(endlessNum > player.ENDLESS){player.ENDLESS = endlessNum;}
            cout << " Level Reached: " << endlessNum << endl;
            cout << ITALIC << " Record: " << player.ENDLESS << RESET << endl << endl;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed*2)); //wait briefly
            //give player reward
            if(endlessNum < 25){
                cout << " Reward: " << YELLOW << endlessNum*5*player.REBIRTH << " coins!\n" << endl; 
                player.COINS += (endlessNum*5*player.REBIRTH);
            }
            else if(endlessNum < 50){
                cout << " Reward: " << YELLOW << endlessNum*10*player.REBIRTH << " coins!\n" << endl; 
                player.COINS += (endlessNum*10*player.REBIRTH);
            }
            else{
                cout << " Reward: " << YELLOW << endlessNum*15*player.REBIRTH << " coins!\n" << endl; 
                player.COINS += (endlessNum*15*player.REBIRTH);
            }
            cout << RESET;
            random = (rand() % 3); //player has chance to get a diamond
            if(random == 0){player.DIAMONDS++;
                cout << CYAN << " You have found a diamond!\n\n" << RESET;}
            this_thread::sleep_for(chrono::milliseconds(player.game_speed)); //wait briefly
            cout << GREEN << " [1]:" << RESET << " Return to Menu\n\n -> ";
            cin >> X; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            player.update(); battle(player); //back to play menu
        }
        else{ //proceed to next level
            system("clear");
            enemy.reset_status();
            cout << " Enemy defeated!\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            if(items[0] == 1 && player.tempHP < player.health){ //Amulet of Undying
                cout << " Amulet of Undying activates\n" << endl;
                player.tempHP += AoU.getStat();
                if(player.tempHP > player.health){player.tempHP = player.health;} //make sure doesn't go over max hp
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            }
            if(endlessNum%50 == 0){ //every 50 levels gives big buff
                cout << "Your powers are growing!\n\n";
                player.health+=20; player.tempHP+=20; player.damage+=5; player.heal+=5;
                player.ice+=2; player.fire+=2; player.poison+=2; player.electric+=2; player.critd+=5;
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            }
            else if(endlessNum%10 == 0){ //every 10th level cleared stat boost
                cout << "Choose upgrade:\n\n";
                cout << " 1) Ice Boost (current: " << player.ice <<")\n" << 
                " 2) Fire Boost (current: " << player.fire << ")\n" <<
                " 3) Poison Boost (current: " << player.poison << ")\n" <<
                " 4) Electric Boost (current: " << player.electric << ")\n\n -> ";
                cin >> X;
                int buff;
                if(endlessNum < 30){buff = 1;}
                else if(endlessNum < 50){buff = 2;}
                else if(endlessNum < 100){buff = 3;}
                else{buff = 5;}
                if(X == "1"){player.ice+=buff; cout << "\n Ice increased!\n\n";}
                else if(X == "2"){player.fire+=buff; cout << "\n Fire increased!\n\n";}
                else if(X == "3"){player.poison+=buff; cout << "\n Poison increased!\n\n";}
                else{player.electric+=buff; cout << "\n Electric increased!\n\n";}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            }
            else if(endlessNum%5 == 0){ //every 5th level cleared gives stat boost
                cout << "Choose upgrade:\n\n";
                cout << " 1) Damage Boost (current: " << player.damage << ")\n" <<
                " 2) Health Boost (current: " << player.tempHP << "/" << player.health << ")\n\n -> ";
                cin >> X;
                int buff;
                if(endlessNum < 30){buff = 1;}
                else if(endlessNum < 50){buff = 2;}
                else if(endlessNum < 100){buff = 3;}
                else{buff = 5;}
                if(X == "1"){player.damage+=buff; cout << "\n Damage increased!\n\n";}
                else{player.health+=(buff+1); player.tempHP+=(buff+2); 
                    if(player.tempHP > player.health){player.tempHP = player.health;} 
                    cout << "\n Health increased!\n\n";}
                this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            }
            if(endlessNum%10 != 0){ //random encounter
                if(rand()%6 == 0){encounter(player, endlessNum);}
            }
            if(player.tempHP > 0){cout << " Continuing on...\n"; 
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));}
            endlessNum++; TURN = 0; //set turn to players, increase dungeon level
        }
    }
}

void level_up(Player player){ //level up menu
    system("clear");
    string X;
    do{
    cout << BLUE << "    - LEVEL UP -" << RESET << endl << endl;
    cout << MAGENTA << "Select stat to increase" << RESET << endl;
    cout << "COINS: " << YELLOW << player.COINS << RESET << endl << endl;

    cout << GREEN << " (1):" << RESET << " Health: " << CYAN << player.HP << RESET << "        ["; //health and varied cost
    if(player.HP < 11){cout << YELLOW << "25 Coins" << RESET << "]" << endl;}
    else if(player.HP < 15){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(player.HP < 20){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (2):" << RESET << " Damage: " << CYAN << player.DMG << RESET << "        ["; //damage and varied cost
    if(player.DMG < 2){cout << YELLOW << "25 Coins" << RESET << "]" << endl;}
    else if(player.DMG < 5){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(player.DMG < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (3):" << RESET << " Fire: " << CYAN << player.FIRE << RESET << "          ["; //fire and varied cost
    if(player.FIRE < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(player.FIRE < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;} 

    cout << GREEN << " (4):" << RESET << " Ice: " << CYAN << player.ICE << RESET << "           ["; //ice and varied cost
    if(player.ICE < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(player.ICE < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;} 

    cout << GREEN << " (5):" << RESET << " Poison: " << CYAN << player.POISON << RESET << "        ["; //poison and varied cost
    if(player.POISON < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(player.POISON < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (6):" << RESET << " Electric: " << CYAN << player.ELECTRIC << RESET << "      ["; //poison and varied cost
    if(player.ELECTRIC < 5){cout << YELLOW << "40 Coins" << RESET << "]" << endl;}
    else if(player.ELECTRIC < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (7):" << RESET << " Heal: " << CYAN << player.HEAL << RESET << "          ["; //heal and varied cost
    if(player.HEAL < 5){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(player.HEAL < 10){cout << YELLOW << "100 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "200 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (8):" << RESET << " Crit Chance: " << CYAN << player.CRITC << RESET << "%  ["; //crit chance and varied cost
    if(player.CRITC < 10){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(player.CRITC < 20){cout << YELLOW << "75 Coins" << RESET << "]" << endl;}
    else if(player.CRITC < 60){cout << YELLOW << "150 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]" << endl;}

    cout << GREEN << " (9):" << RESET << " Crit Damage: " << CYAN << player.CRITD << RESET << "   ["; //crit damage and varied cost
    if(player.CRITD < 7){cout << YELLOW << "50 Coins" << RESET << "]" << endl;}
    else if(player.CRITD < 10){cout << YELLOW << "150 Coins" << RESET << "]" << endl;}
    else{cout << YELLOW << "300 Coins" << RESET << "]" << endl;}

    cout << GREEN << " (10):" << RESET << " Dodge: " << CYAN << player.DODGE << RESET << "%       ["; //crit chance and varied cost
    if(player.DODGE < 10){cout << YELLOW << "30 Coins" << RESET << "]" << endl;}
    else if(player.DODGE < 15){cout << YELLOW << "80 Coins" << RESET << "]" << endl;}
    else if(player.DODGE < 40){cout << YELLOW << "120 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << " (11):" << RESET << " Shield: " << CYAN << player.SHIELD << RESET << "        ["; //shield
    if(player.SHIELD == 0){cout << YELLOW << "250 Coins" << RESET << "]" << endl;}
    else if(player.SHIELD < 3){cout << YELLOW << "500 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << " (12):" << RESET << " Luck: " << CYAN << player.LUCK << RESET << "%        ["; //shield
    if(player.LUCK < 75){cout << YELLOW << "10 Coins" << RESET << "]" << endl;}
    else{cout << RED << "MAX" << RESET << "]\n";}

    cout << GREEN << "\n (0):" << RESET << " [Menu]" << endl << endl;
    cout << " -> "; 
    cin >> X;
    system("clear");
    }while(stoi(X) < 0 || stoi(X) > 12);
    if(X == "1"){ //health
        if(player.HP < 11){ 
            if(player.COINS > 24){player.COINS -= 25; player.HP += 1; player.update();}
            else{too_poor(player);} //tell players they don't have enough coins
        }
        else if(player.HP < 15){ 
            if(player.COINS > 49){player.COINS -= 50; player.HP += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.HP < 20){
            if(player.COINS > 99){player.COINS -= 100; player.HP += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.HP += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "2"){ //damage
        if(player.DMG < 2){
            if(player.COINS > 24){player.COINS -= 25; player.DMG += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.DMG < 5){
            if(player.COINS > 49){player.COINS -= 50; player.DMG += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.DMG < 10){
            if(player.COINS > 99){player.COINS -= 100; player.DMG += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.DMG += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "3"){ //fire
        if(player.FIRE < 5){
            if(player.COINS > 39){player.COINS -= 40; player.FIRE += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.FIRE < 10){
            if(player.COINS > 99){player.COINS -= 100; player.FIRE += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.FIRE += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "4"){ //ice
        if(player.ICE < 5){
            if(player.COINS > 39){player.COINS -= 40; player.ICE += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.ICE < 10){
            if(player.COINS > 99){player.COINS -= 100; player.ICE += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.ICE += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "5"){ //poison
        if(player.POISON < 5){
            if(player.COINS > 39){player.COINS -= 40; player.POISON += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.POISON < 10){
            if(player.COINS > 99){player.COINS -= 100; player.POISON += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.POISON += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "6"){ //electric
        if(player.ELECTRIC < 5){
            if(player.COINS > 39){player.COINS -= 40; player.ELECTRIC += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.ELECTRIC < 10){
            if(player.COINS > 99){player.COINS -= 100; player.ELECTRIC += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.ELECTRIC += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "7"){ //heal
        if(player.HEAL < 5){
            if(player.COINS > 49){player.COINS -= 50; player.HEAL += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.HEAL < 10){
            if(player.COINS > 99){player.COINS -= 100; player.HEAL += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 199){player.COINS -= 200; player.HEAL += 1; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "8"){ //crit chance
        if(player.CRITC < 10){
            if(player.COINS > 49){player.COINS -= 50; player.CRITC += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.CRITC < 20){
            if(player.COINS > 74){player.COINS -= 75; player.CRITC += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.CRITC < 60){
            if(player.COINS > 149){player.COINS -= 150; player.CRITC += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up(player);
        }
    }
    else if(X == "9"){ //crit damage
        if(player.CRITD < 7){
            if(player.COINS > 49){player.COINS -= 50; player.CRITD += 2; player.update();}
            else{too_poor(player);}
        }
        else if(player.CRITD < 10){
            if(player.COINS > 149){player.COINS -= 150; player.CRITD += 2; player.update();}
            else{too_poor(player);}
        }
        else{
            if(player.COINS > 299){player.COINS -= 300; player.CRITD += 2; player.update();}
            else{too_poor(player);}
        }
    }
    else if(X == "10"){ //dodge chance
        if(player.DODGE < 10){
            if(player.COINS > 29){player.COINS -= 30; player.DODGE += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.DODGE < 15){
            if(player.COINS > 79){player.COINS -= 80; player.DODGE += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.DODGE < 40){
            if(player.COINS > 119){player.COINS -= 120; player.DODGE += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up(player);
        }
    }
    else if(X == "11"){ //shield
        if(player.SHIELD == 0){
            if(player.COINS > 249){player.COINS -= 250; player.SHIELD += 1; player.update();}
            else{too_poor(player);}
        }
        else if(player.SHIELD < 3){
            if(player.COINS > 499){player.COINS -= 500; player.SHIELD += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up(player);
        }
    }
    else if(X == "12"){ //luck
        if(player.LUCK < 75){
            if(player.COINS > 9){player.COINS -= 10; player.LUCK += 1; player.update();}
            else{too_poor(player);}
        }
        else{
            system("clear"); cout << "This stat is maxed out\n";
            this_thread::sleep_for(chrono::seconds(1)); level_up(player);
        }
    }
    else{menu(player);}
    level_up(player);
}

void how_to(Player player){ //game instructions
    system("clear");
    string X;
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
    menu(player);
}

void store(Player player){ //store menu
    string X;
    do{
        system("clear");
        cout << BLUE << "  - STORE -\n" << RESET << endl;
        cout << "COINS: " << YELLOW << player.COINS << RESET << endl << "DIAMONDS: " << CYAN << player.DIAMONDS << RESET << endl << endl;
        cout << GREEN << " (1):" << RESET << " Game Speed Increase ";
        if(player.store1 == "no"){cout << CYAN << " [20 Diamonds]\n" << RESET;} //can be bought
        else{cout << RED << "*Already Purchased*\n" << RESET;} //already bought
        cout << GREEN << " (2):" << RESET << " Stat Boost " << CYAN << " [5 Diamonds]\n" << RESET;
        cout << GREEN << " (3):" << RESET << " Buy Items\n";
        cout << GREEN << " (4):" << RESET << " Second Starting Item ";
        if(player.store2 == "no"){cout << YELLOW << " [750 Coins]\n" << RESET;} //can be bought
        else{cout << RED << "*Already Purchased*\n" << RESET;} //already bought
        cout << GREEN << " (0):" << RESET << " Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "4");
    if(X == "1"){
        if(player.store1 == "yes"){ //already own game speed upgrade
            system("clear"); cout << CYAN << "You already own this item\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store(player);
        }
        else{
            if(player.DIAMONDS > 19){ //buy game speed upgrade
                player.DIAMONDS -= 20; player.store1 = "yes"; player.game_speed = 500;
                player.update(); store(player);
            }
            else{ //too poor
                system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); store(player);
            }
        }
    }
    else if(X == "2"){
        if(player.DIAMONDS > 4){ //buy stat boost
            player.DIAMONDS -= 5; player.HP += 2; player.DMG += 2; player.FIRE += 2; 
            player.ICE += 2; player.POISON += 2; player.HEAL += 2; player.CRITD += 2; player.ELECTRIC += 2;
            player.update(); system("clear"); cout << CYAN << " Stats have been boosted\n" << RESET; 
            this_thread::sleep_for(chrono::seconds(1)); store(player);
        }
        else{ //too poor
            system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store(player);
        }
    }
    else if(X == "3"){item_shop(player);}
    else if(X == "4"){
        if(player.store2 == "yes"){ //already own second item
            system("clear"); cout << CYAN << "You already own this upgrade\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); store(player);
        }
        else{
            if(player.COINS > 749){ //buy game speed upgrade
                player.COINS -= 750; player.store2 = "yes";
                player.update(); store(player);
            }
            else{system("clear"); cout << CYAN << "You don't have enough coins\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); store(player);}
        }
    }
    else{menu(player);}
}

void settings(Player player){ //settings menu
    string X;
    do{
        system("clear");
        cout << BLUE << "  - SETTINGS -\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Change Game Speed [";
        if(player.game_speed == 1000){cout << "normal]";}
        else{cout << "fast]";}
        if(player.store1 == "no"){cout << YELLOW << " *Unlock in store*" << RESET;} //shows if setting needs bought
        cout << endl << GREEN << " (2):" << RESET << " Reset Save" << RED << " *Permanent*" << RESET;
        cout << endl << GREEN << " (0):" << RESET << " Back to Menu\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "2");
    if(X == "1"){
        if(player.store1 == "yes"){ //if game speed has been bought
            if(player.game_speed == 1000){player.game_speed = 500;}
            else{player.game_speed = 1000;}
            player.update(); settings(player);
        }
        else{ //setting needs bought
            system("clear"); cout << "Unlock this settting in store\n";
            this_thread::sleep_for(chrono::seconds(1)); settings(player);
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
            player.HP=10; player.DMG=1; player.FIRE=0; player.ICE=0; player.POISON=0; player.HEAL=0; player.COINS=0; 
            player.PROGRESS = 0; player.CRITC = 5; player.CRITD = 2; player.ELECTRIC = 0; player.game_speed = 1000; 
            player.store1 = "no"; player.DIAMONDS = 0; player.numItems = 0; player.DODGE = 5; player.LUCK = 5; 
            player.SHIELD = 0; player.store2 = "no"; player.boon1 = player.boon2 = player.boon3 = player.boon4 = "no"; 
            player.BOON = 0; player.ENDLESS = 0; player.REBIRTH = 1; player.COMPANION = 0;
            player.comp1 = player.comp2 = player.comp3 = player.comp4 = player.comp5 = "no"; 
            player.update(); reset_items(); settings(player);
        }
        else{settings(player);}
    }
    else{menu(player);}
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

void pick_item(Player player){ //get new item
    string X;
    for(int i = 0; i < 9; i++){ //reset items
        items[i] = 0;
    }
    Item x, y, z; int a, b, c; string d, e, f;
    string info = get_item(player.numItems); //return three items
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

    if(player.store2 == "yes"){ //if second item upgrade owned
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        system("clear");
        info = extra_item(player.numItems, items); //return two items
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

void item_shop(Player player){ //buy items
    string X;
    do{
        system("clear");
        cout << BLUE << "  - ITEM SHOP -\n" << RESET << endl;
        cout << "DIAMONDS: " << CYAN << player.DIAMONDS << RESET << endl << endl;
        if(player.numItems < 5){cout << GREEN << " (1):" << RESET << " Unlock Next Item " << CYAN << " [4 Diamonds]\n" << RESET;}
        else{cout << GREEN << " (-):" << RESET << " All Items Unlocked\n";}
        cout << GREEN << " (0):" << RESET << " Back To Store\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "1"){
        if(player.numItems == 5){ //already own all items
            system("clear"); cout << CYAN << "Currently no items to buy\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1)); item_shop(player);
        }
        else{
            if(player.DIAMONDS < 4){ //too poor
                system("clear"); cout << CYAN << "You don't have enough diamonds\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1)); item_shop(player); 
            }
            else{ //buy next item
                system("clear");
                player.DIAMONDS -=4;
                if(player.numItems == 0){ //rune of death
                    cout << CYAN << " Acquired: Rune of Death!\n" << RESET;
                }
                else if(player.numItems == 1){ //cloak of protection
                    cout << CYAN << " Acquired: Cloak of Protection!\n" << RESET;
                }
                else if(player.numItems == 2){ //golden talisman
                    cout << CYAN << " Acquired: Golden Talisman!\n" << RESET;
                }
                else if(player.numItems == 3){ //boots of the elves
                    cout << CYAN << " Acquired: Boots of the Elves!\n" << RESET;
                }
                else{ //wand of heroes
                    cout << CYAN << " Acquired: Wand of Heroes!\n" << RESET;
                }
                player.numItems++; player.update();
                this_thread::sleep_for(chrono::seconds(1)); item_shop(player); 
            }
        }
    }
    else{store(player);}
}

void boost_menu(Player player){ //boons, companions, item upgrades, and rebirth
    string X;
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
    if(X == "0"){menu(player);}
    else if(X == "1"){boon_menu(player);}
    else if(X == "2"){companion_menu(player);}
    else if(X == "3"){item_menu(player);}
    else{rebirth_menu(player);}
}

void boon_menu(Player player){ //controls player boons
    string X;
    do{
        system("clear");
        cout << BLUE << "  - BOONS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << player.COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Boons give a unique in-game buff\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Boon of the Guardian: Enemies cannot crit";
        if(player.boon1 == "no"){cout << YELLOW << " (Unlock for 1500 coins)" << RESET;}
        if(player.BOON == 1){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (2):" << RESET << " Boon of the Warrior: Enemies cannot dodge";
        if(player.boon2 == "no"){cout << YELLOW << " (Unlock for 3000 coins)" << RESET;}
        if(player.BOON == 2){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (3):" << RESET << " Boon of the Trickster: Heal on crits";
        if(player.boon3 == "no"){cout << YELLOW << " (Unlock for 5000 coins)" << RESET;}
        if(player.BOON == 3){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (4):" << RESET << " Boon of the Strategist: Enemies cannot gain buffs";
        if(player.boon4 == "no"){cout << YELLOW << " (Unlock for 5500 coins)" << RESET;}
        if(player.BOON == 4){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (5):" << RESET << " Disable Boons\n";
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "5");
    if(X == "0"){boost_menu(player);}
    else if(X == "1"){ //guardian
        if(player.boon1 == "no"){
            if(player.COINS < 1500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu(player);
            }
            else{player.COINS -= 1500; player.boon1 = "yes"; player.update(); boon_menu(player);}
        }
        else{player.BOON = 1; boon_menu(player);}
    }
    else if(X == "2"){ //warrior
        if(player.boon2 == "no"){
            if(player.COINS < 3000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu(player);
            }
            else{player.COINS -= 3000; player.boon2 = "yes"; player.update(); boon_menu(player);}
        }
        else{player.BOON = 2; boon_menu(player);}
    }
    else if(X == "3"){ //trickster
        if(player.boon3 == "no"){
            if(player.COINS < 5000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu(player);
            }
            else{player.COINS -= 5000; player.boon3 = "yes"; player.update(); boon_menu(player);}
        }
        else{player.BOON = 3; boon_menu(player);}
    }
    else if(X == "4"){ //strategist
        if(player.boon4 == "no"){
            if(player.COINS < 5500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                boon_menu(player);
            }
            else{player.COINS -= 5500; player.boon4 = "yes"; player.update(); boon_menu(player);}
        }
        else{player.BOON = 4; boon_menu(player);}
    }
    else{player.BOON = 0; boon_menu(player);}
}

void companion_menu(Player player){ //controls player companions
    string X;
    do{
        system("clear");
        cout << BLUE << "  - COMPANIONS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << player.COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Companions assist you in battle\n" << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Fairy: Heals your wounds"; //fairy
        if(player.comp1 == "no"){cout << YELLOW << " (Unlock for 800 coins)" << RESET;}
        if(player.COMPANION == 1){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (2):" << RESET << " Imp: Attacks enemies"; //imp
        if(player.comp2 == "no"){cout << YELLOW << " (Unlock for 1000 coins)" << RESET;}
        if(player.COMPANION == 2){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (3):" << RESET << " Pixie: Can stun enemies"; //pixie
        if(player.comp3 == "no"){cout << YELLOW << " (Unlock for 2000 coins)" << RESET;}
        if(player.COMPANION == 3){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (4):" << RESET << " Gnome: Searches for treasure"; //gnome
        if(player.comp4 == "no"){cout << YELLOW << " (Unlock for 5000 coins)" << RESET;}
        if(player.COMPANION == 4){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (5):" << RESET << " Lizard: Can apply bleed or heal"; //lizard
        if(player.comp5 == "no"){cout << YELLOW << " (Unlock for 6000 coins)" << RESET;}
        if(player.COMPANION == 5){cout << MAGENTA << " [Equipped]" << RESET;}
        cout << GREEN << "\n (6):" << RESET << " Disable Companions\n";
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "6");
    if(X == "0"){boost_menu(player);}
    else if(X == "1"){ //fairy
        if(player.comp1 == "no"){
            if(player.COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu(player);
            }
            else{player.COINS -= 800; player.comp1 = "yes"; player.update(); companion_menu(player);}
        }
        else{player.COMPANION = 1; companion_menu(player);}
    }
    else if(X == "2"){ //imp
        if(player.comp2 == "no"){
            if(player.COINS < 1000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu(player);
            }
            else{player.COINS -= 1000; player.comp2 = "yes"; player.update(); companion_menu(player);}
        }
        else{player.COMPANION = 2; companion_menu(player);}
    }
    else if(X == "3"){ //pixie
        if(player.comp3 == "no"){
            if(player.COINS < 2000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu(player);
            }
            else{player.COINS -= 2000; player.comp3 = "yes"; player.update(); companion_menu(player);}
        }
        else{player.COMPANION = 3; companion_menu(player);}
    }
    else if(X == "4"){ //gnome
        if(player.comp4 == "no"){
            if(player.COINS < 5000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu(player);
            }
            else{player.COINS -= 5000; player.comp4 = "yes"; player.update(); companion_menu(player);}
        }
        else{player.COMPANION = 4; companion_menu(player);}
    }
    else if(X == "5"){ //lizard
        if(player.comp5 == "no"){
            if(player.COINS < 6000){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                companion_menu(player);
            }
            else{player.COINS -= 6000; player.comp5 = "yes"; player.update(); companion_menu(player);}
        }
        else{player.COMPANION = 5; companion_menu(player);}
    }
    else{player.COMPANION = 0; companion_menu(player);}
}

void item_menu(Player player){ //upgrade item menu
    string X;
    do{
        system("clear");
        cout << BLUE << "  - UPGRADE ITEMS -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << player.COINS << RESET << endl << endl;
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

        if(player.numItems > 0){
            cout << GREEN << "\n (5):" << RESET << " Rune of Death: Level " << RoD.getLevel(); //RoD
            if(RoD.getLevel() == 1){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
            else if(RoD.getLevel() == 2){cout << YELLOW << " (Upgrade for 800 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(player.numItems > 1){
            cout << GREEN << "\n (6):" << RESET << " Cloak of Protection: Level " << CoP.getLevel(); //CoP
            if(CoP.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(CoP.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(player.numItems > 2){
            cout << GREEN << "\n (7):" << RESET << " Golden Talisman: Level " << G_T.getLevel(); //G_T
            if(G_T.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(G_T.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(player.numItems > 3){
            cout << GREEN << "\n (8):" << RESET << " Boots of the Elves: Level " << BotE.getLevel(); //BotE
            if(BotE.getLevel() == 1){cout << YELLOW << " (Upgrade for 250 coins)" << RESET;}
            else if(BotE.getLevel() == 2){cout << YELLOW << " (Upgrade for 500 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        if(player.numItems > 4){
            cout << GREEN << "\n (9):" << RESET << " Wand of Heroes: Level " << BotE.getLevel(); //WoH
            if(WoH.getLevel() == 1){cout << YELLOW << " (Upgrade for 400 coins)" << RESET;}
            else if(WoH.getLevel() == 2){cout << YELLOW << " (Upgrade for 800 coins)" << RESET;}
            else{cout << MAGENTA << " (Fully Upgraded)" << RESET;}
        }

        cout << GREEN << "\n (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "9");

    if(X == "0"){boost_menu(player);}
    else if(X == "1"){ //amulet of undying
        if(AoU.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(AoU.getLevel() == 2){
            if(player.COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 500; AoU.setLevel(3); AoU.setStat(4); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 250; AoU.setLevel(2); AoU.setStat(2); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "2"){ //ring of life
        if(RoL.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(RoL.getLevel() == 2){
            if(player.COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 400; RoL.setLevel(3); RoL.setStat(6); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 200; RoL.setLevel(2); RoL.setStat(4); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "3"){ //staff of power
        if(SoP.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(SoP.getLevel() == 2){
            if(player.COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 400; SoP.setLevel(3); SoP.setStat(3); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 200; SoP.setLevel(2); SoP.setStat(2); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "4"){ //gauntlets of strength
        if(GoS.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(GoS.getLevel() == 2){
            if(player.COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 400; GoS.setLevel(3); GoS.setStat(5); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 200){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 200; GoS.setLevel(2); GoS.setStat(3); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "5" && player.numItems > 0){ //rune of death
        if(RoD.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(RoD.getLevel() == 2){
            if(player.COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 800; RoD.setLevel(3); RoD.setStat(10); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 400; RoD.setLevel(2); RoD.setStat(5); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "6" && player.numItems > 1){ //cloak of protection
        if(CoP.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(CoP.getLevel() == 2){
            if(player.COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 500; CoP.setLevel(3); CoP.setStat(3); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 250; CoP.setLevel(2); CoP.setStat(2); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "7" && player.numItems > 2){ //golden talisman
        if(G_T.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(G_T.getLevel() == 2){
            if(player.COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 500; G_T.setLevel(3); G_T.setStat(20); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 250; G_T.setLevel(2); G_T.setStat(15); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "8" && player.numItems > 3){ //boots of the elves
        if(BotE.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(BotE.getLevel() == 2){
            if(player.COINS < 500){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 500; BotE.setLevel(3); BotE.setStat(10); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 250){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 250; BotE.setLevel(2); BotE.setStat(5); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else if(X == "9" && player.numItems > 4){ //wand of heroes
        if(WoH.getLevel() == 3){
            system("clear");
            cout << CYAN << " This item is fully upgraded!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            item_menu(player);
        }
        else if(WoH.getLevel() == 2){
            if(player.COINS < 800){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 800; WoH.setLevel(3); WoH.setStat(10); update_items(); player.update(); item_menu(player);
            }
        }
        else{
            if(player.COINS < 400){
                system("clear");
                cout << CYAN << " You don't have enough coins!\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                item_menu(player);
            }
            else{
                player.COINS -= 400; WoH.setLevel(2); WoH.setStat(5); update_items(); player.update(); item_menu(player);
            }
        }
    }
    else{item_menu(player);} //in case of errors
}

void rebirth_menu(Player player){ //controls player rebirth
    string X;
    do{
        system("clear");
        cout << BLUE << "  - REBIRTH (Level: " << player.REBIRTH << ") -\n" << RESET << endl;
        cout << " COINS: " << YELLOW << player.COINS << RESET << endl << endl;
        cout << CYAN << ITALIC << " Rebirth resets all your stats and progress, but increases your coin income\n" << endl;
        cout << RESET << GREEN << " (1):" << RESET << " Rebirth " << YELLOW << "(" << 1000 * pow(2, player.REBIRTH-1) << " Coins)\n" << RESET;
        cout << GREEN << " (0):" << RESET << " Back to Upgrades\n\n -> ";
        cin >> X;
    }while(X < "0" || X > "1");
    if(X == "0"){boost_menu(player);}
    else{
        system("clear");
        if(player.COINS < 1000 * pow(2, player.REBIRTH-1)){
            cout << CYAN << " You don't have enough coins!\n" << RESET;
        }
        else{
            cout << YELLOW << " You are reborn!\n" << RESET;
            cout << " Your stats and progress have been reset\n";
            cout << " Your items and upgrades have been kept\n";
            player.REBIRTH++; player.PROGRESS = 0; player.COINS = 0; player.HP = 10; player.DMG = 1; 
            player.FIRE = 0; player.ICE = 0; player.POISON = 0; player.ELECTRIC = 0; player.HEAL = 0; 
            player.DODGE = 5; player.LUCK = 5; player.SHIELD = 0; player.CRITC = 5; player.CRITD = 2; player.update();
            this_thread::sleep_for(chrono::seconds(1));
        }
        this_thread::sleep_for(chrono::seconds(1));
        rebirth_menu(player);
    }
}

void too_poor(Player player){ //function calls when players try to buy something too expensive
    system("clear"); cout << CYAN << "You don't have enough coins\n" << RESET;
    this_thread::sleep_for(chrono::seconds(1)); level_up(player);
}

void database(Player player){ //enemy and status information
    string X;
    do{
        system("clear");
        cout << BLUE << " - DATABASES -\n\n" << RESET;
        cout << GREEN << " (1): " << RESET << "Enemy Database\n";
        cout << GREEN << " (2): " << RESET << "Status Effect Database\n";
        cout << GREEN << " (0): " << RESET << "Return to Menu\n -> ";
        cin >> X;
    }while(X < "0" || X > "2");
    if(X == "0"){menu(player);}
    else if(X == "1"){ //enemy database
        system("clear");
        cout << BLUE << " - ENEMY DATABASE -\n\n" << RESET;
        if(player.PROGRESS == 0){
            cout << " No enemies unlocked yet\n\n";
        }
        if(player.PROGRESS > 0){
            cout << GREEN << " *" << RESET << " Evil Wizard - Crits more frequently, resistant to electric\n";
            cout << GREEN << " *" << RESET << " Fire Mage - Resistant to fire, vunerable to ice\n";
            cout << GREEN << " *" << RESET << " Ice Sorcerer - Resistant to ice, vulnerable to fire\n";
        }
        if(player.PROGRESS > 1){
            cout << GREEN << " *" << RESET << " Necromancer - Resistant to poison, vulnerable to electric\n";
        }
        if(player.PROGRESS > 2){
            cout << GREEN << " *" << RESET << " Defender - Dodges more frequently, vulnerable to poison\n";
        }
        if(player.PROGRESS > 3){
            cout << GREEN << " *" << RESET << " Stormcaster - Can stun player, resistant to electric\n";
        }
        if(player.PROGRESS > 4){
            cout << GREEN << " *" << RESET << " Unstable Mage - Deals high damage but injures themselves\n";
        }
        cout << RED << "\n [0]" << RESET << " Back to Databases\n\n -> ";
        cin >> X; database(player);
    }
    else{ //status database
        system("clear");
        cout << BLUE << " - ENEMY DATABASE -\n\n" << RESET;
        cout << GREEN << " *" << RESET << " Bleed - Take damage at end of turn\n";
        cout << GREEN << " *" << RESET << " Heal - Gain health at start of turn\n";
        cout << GREEN << " *" << RESET << " Shield - Block some damage for a turn\n";
        cout << GREEN << " *" << RESET << " Drained - Lose one spell option\n";
        cout << RED << "\n [0]" << RESET << " Back to Databases\n\n -> ";
        cin >> X; database(player);
    }

}

void encounter(Player player, int levNum){ //random encounters
    string X;
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
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            if(rand()%100 < player.luck){ //save
                cout << " You manage to leap over it in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it!" << RED << " -2 health!\n" << RESET; player.tempHP -= 2;
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else{ //arrow trap
            cout << RED << " You encounter an arrow trap!\n\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
            if(rand()%100 < player.luck){ //save
                cout << " You manage to duck behind cover in time!\n";
            }
            else{ //fail
                cout << " You can't avoid it!" << RED << " -4 health!\n" << RESET; player.tempHP -= 4;
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }

    else if(encounterType == "hp potion"){
        if(player.tempHP < player.health){
            cout << GREEN << " You find a health potion! It's refreshing!\n" << RESET;
            player.tempHP = player.health; this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else{
            cout << YELLOW << " You find a trinket! +10 Coins!\n" << RESET; player.COINS += 10;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }

    else if(encounterType == "potion choice"){
        cout << MAGENTA << " You find a glittering potion with unknown properties...\n\n" << YELLOW;
        cout << GREEN << " (1):" << RESET << " Drink unknown potion\n " << GREEN << "(2): " << RESET << "Don't drink unknown potion\n\n -> ";
        cin >> X;
        if(X == "1"){
            if(rand()%100 < (20 + (player.luck/2))){ //stat boost
                factor = rand()%6;
                if(factor == 0){ //health
                    cout << endl << " Your health permanently increases!\n"; player.HP++; player.tempHP++; player.health++;
                }
                else if(factor == 1){ //damage
                    cout << endl << " Your damage permanently increases!\n"; player.DMG++; player.damage++;
                }
                else if(factor == 2){ //heal
                    cout << endl << " Your healing permanently increases!\n"; player.HEAL++; player.heal++;
                }
                else if(factor == 3){ //fire
                    cout << endl << " Your fire permanently increases!\n"; player.FIRE++; player.fire++;
                }
                else if(factor == 4){ //ice
                    cout << endl << " Your ice permanently increases!\n"; player.ICE++; player.ice++;
                }
                else if(factor == 5){ //electric
                    cout << endl << " Your electric permanently increases!\n"; player.ELECTRIC++; player.electric++;
                }
                else{ //poison
                    cout << endl << " Your poison permanently increases!\n"; player.POISON++; player.poison++;
                }
            }
            else{ //poison
                cout << endl << " You've been poisoned!" << RED << " -5 health!\n" << RESET; player.tempHP -= 5;
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else{
            cout << endl << " Probably a smart choice...\n";
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }

    else if(encounterType == "diamond"){
        cout << CYAN << " You notice a diamond by your foot. Shiny!\n" << RESET; player.DIAMONDS++;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
    }

    else if(encounterType == "item"){
        if(itemCount() > 1){ //there are enough items
            Item x, y; int a, b; string c, d;
            string info = extra_item(player.numItems, items); //return two items
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
                if(a == 1){player.health+=RoL.getStat(); player.tempHP+=RoL.getStat();}//RoL
                else if(a == 2){player.fire+=SoP.getStat(); player.ice+=SoP.getStat();
                    player.poison+=SoP.getStat(); player.electric+=SoP.getStat();}//SoP
                else if(a == 3){player.damage+=GoS.getStat();}//GoS
                else if(a == 6){player.critc+=G_T.getStat();}//G_T
                else if(a == 7){player.dodge+=BotE.getStat();}//BotE
                else if(a == 8){player.shield+=WoH.getStat();}//WoH
            }
            else{items[b] = 1;
                if(b == 1){player.health+=RoL.getStat(); player.tempHP+=RoL.getStat();}//RoL
                else if(b == 2){player.fire+=SoP.getStat(); player.ice+=SoP.getStat();
                    player.poison+=SoP.getStat(); player.electric+=SoP.getStat();}//SoP
                else if(b == 3){player.damage+=GoS.getStat();}//GoS
                else if(b == 6){player.critc+=G_T.getStat();}//G_T
                else if(b == 7){player.dodge+=BotE.getStat();}//BotE
                else if(b == 8){player.shield+=WoH.getStat();}//WoH
            }
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else if(itemCount() == 1){ //one item can be found
            int count;
            for(count = 0; items[count] == 1; count++);
            items[count] = 1;
            if(count == 0){cout << " You found the Amulet of Undying!\n";}
            else if(count == 1){cout << " You come across a Ring of Life!\n"; 
                player.health+=RoL.getStat(); player.tempHP+=RoL.getStat();}
            else if(count == 2){cout << " You found a Staff of Power!\n"; player.fire+=SoP.getStat();
                player.ice+=SoP.getStat(); player.poison+=SoP.getStat(); player.electric+=SoP.getStat();}
            else if(count == 3){cout << " You found the Gauntlets of Strength!\n"; player.damage+=GoS.getStat();}
            else if(count == 4){cout << " You pick up the Rune of Death!\n";}
            else if(count == 5){cout << " You found the Cloak of Protection!\n";}
            else if(count == 6){cout << " You discover a Golden Talisman!\n"; player.critc+=G_T.getStat();}
            else if(count == 7){cout << " You find the Wand of Heroes!\n"; player.shield+=WoH.getStat();}
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else{ //no more items
            cout << YELLOW << " You find some treasure! +40 Coins!\n" << RESET; player.COINS += 40;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
    }

    else if(encounterType == "shop"){
        cout << MAGENTA << " You come across a strange merchant. He shows you his wares\n\n" << RESET;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        cout << " Coins: " << YELLOW << player.COINS << RESET << endl;
        cout << GREEN << " (1):" << RESET << " Health Potion " << YELLOW << " [50 Coins] " <<
            RESET << " (Health: "; 
            if(player.tempHP < player.health){cout << RED;}
            else{cout << GREEN;}
            cout << player.tempHP << RESET << "/" << GREEN << player.health << RESET << ")\n";
        cout << GREEN << " (2):" << RESET << " Ornate Dagger " << YELLOW << " [100 Coins]\n" << RESET;
        cout << GREEN << " (3):" << RESET << " Glittering Amulet " << YELLOW << " [500 Coins]\n" << RESET;
        cout << GREEN << " (0):" << RESET << " Buy Nothing\n -> ";
        cin >> X;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        if(X != "0" && rand()%100 == 0){ //1% chance for merchant to curse player
            cout << BOLD << RED << "\n The merchant laughs, and casts a curse on you before vanishing\n" << RESET;
            player.damage -= 2; if(player.damage < 1){player.damage = 1;} player.health -= 2; if(player.tempHP > player.health){player.tempHP = player.health;}
        }
        else if(X == "1"){ //health potion
            if(player.COINS > 49){
                cout << "\n The potion tastes great!\n"; player.COINS -= 50; player.tempHP += (1+player.heal); player.health += (1+player.heal);
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; player.COINS++;
            }
            
        }
        else if(X == "2"){ //ornate dagger
            if(player.COINS > 99){
                cout << "\n The dagger looks like it will cause some damage!\n"; player.COINS -= 100; player.damage += 5;
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; player.COINS++;
            }    
        }
        else if(X == "3"){ //glittering amulet
            if(player.COINS > 499){
                cout << "\n The amulet is pulsing with power!\n"; player.COINS -= 500; player.damage += 10; player.health += 5;
                player.tempHP += 5; player.ice += 3; player.fire += 3; player.poison += 3; player.electric += 3; player.heal += 3; 
                player.critc += 10; player.luck +=10; player.dodge += 10; player.critd += 10; player.shield++;
            }
            else{
                cout << "\n The merchant sighs at your poverty, and gives you a coin for your trouble\n"; player.COINS++;
            }    
        }
        else{
            cout << "\n The merchant sighs, but lets you go on your way\n";
        }
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
    }

    else if(encounterType == "fairy"){
        cout << GREEN << " A little fairy lands on your shoulder, and gives you a blessing\n" << RESET;
        player.damage++; player.critd += 2; player.fire++; player.ice++; player.poison++; player.electric++;
        this_thread::sleep_for(chrono::milliseconds(player.game_speed));
    }

    else{ //secret passage
        if(levNum < 18){
            cout << GREEN << " You find a secret passage!\n" << RESET;
            levNum += (2+(rand()%3));
            if(levNum > 20){levNum = 19;}
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
        }
        else{
            cout << YELLOW << " You find a purse! +25 Coins!\n" << RESET; player.COINS += 25;
            this_thread::sleep_for(chrono::milliseconds(player.game_speed));
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
