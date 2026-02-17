#ifndef ENEMY
#define ENEMY

#include <iostream>
#include "player.h"

struct Enemy{
    Enemy();
    void make_enemy(std::string, Player &player, int levNum);
    void generate_name();
    void reset_status();

    //variables
    std::string type, name;
    //main stats
    int health, tempHP, damage, fire, ice, poison, electric, shield, heal, luck, critc, critd, dodge;
    //effects with * can have varying numbers
    //status effects: *bleed:0, *shield:1, *heal:2, drained:3
    int status[4]; //keeps track of status effects on player
};

#endif