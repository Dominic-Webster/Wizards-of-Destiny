#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "spell.h"

struct Player{
    Player();
    void update();
    void reset_status();

    //variables
    Spell CARD1, CARD2, CARD3;
    std::string store1, store2, boon1, boon2, boon3, boon4,
        comp1, comp2, comp3, comp4, comp5;
    //main stats
    int HP, DMG, FIRE, ICE, POISON, ELECTRIC, HEAL, LUCK, SHIELD, 
        CRITC, CRITD, DODGE, PROGRESS, COINS, DIAMONDS, game_speed, numItems,
        ENDLESS, REBIRTH, BOON, COMPANION;
    //temp stats
    int health, tempHP, damage, fire, ice, poison, electric, shield, heal, luck, critc, critd, dodge;
    //effects with * can have varying numbers
    //status effects: *bleed:0, *shield:1, *heal:2, drained:3
    int status[4]; //keeps track of status effects on player
};

#endif