#include "enemy.h"
using namespace std;

Enemy::Enemy(){
    type = name = "";
    health = tempHP = damage = fire = ice = poison = electric = shield = heal = luck = critc = critd = dodge = 0;
    reset_status();
}

void Enemy::make_enemy(string factor, Player &player, int levNum){
    //Misty Dungeon
    if(factor == "1"){
        //get enemy type
        int eType = (rand() % 4);
        if(eType < 2){type = "Wizard";} //evil wizard
        else if(eType == 2){type = "Fire";} //fire mage 
        else{type = "Ice";} //ice sorcerer
        critc = 10; //crit chance
        dodge = 5; //dodge chance

        //set stats based on adventure level
        if(levNum < 5){ //levels 1-4
            health = 4 + (rand() % 5); damage = 1 + (rand() % 2);
            ice = 0; fire = 0; poison = 0; 
            electric = 0; heal = 1; critd = 1;
            if(type == "Fire"){fire = 1;} //fire mage buff
            if(type == "Ice"){ice = 1;} //ice sorcerer buff
        }
        else if(levNum < 10){ //levels 5-9
            health = 8 + (rand() % 6); damage = 1 + (rand() % 3);
            ice = (rand() % 2); fire = (rand() % 2); 
            poison = 1; electric = 1;
            heal = 2; critd = 1;
            if(type == "Fire"){fire += 1;} //fire mage buff
            if(type == "Ice"){ice += 1;} //ice sorcerer buff
        }
        else if(levNum == 10){ //level 10 mini boss
            health = 15 + (rand() % 6); damage = 3 + (rand() % 3);
            ice = 2 + (rand() % 2); fire = 2 + (rand() % 2); 
            poison = 3; electric = 3;
            heal = 5; critd = 2; critc += 5;
            if(type == "Fire"){fire += 2;} //fire mage buff
            if(type == "Ice"){ice += 2;} //ice sorcerer buff
        }
        else if(levNum < 15){ //levels 11-14
            health = 12 + (rand() % 6); damage = 2 + (rand() % 3);
            ice = 1 + (rand() % 2); fire = 1 + (rand() % 2); 
            poison = 2; electric = 2;
            heal = 4; critd = 2;
            if(type == "Fire"){fire += 2;} //fire mage buff
            if(type == "Ice"){ice += 2;} //ice sorcerer buff
        }
        else if(levNum < 20){ //levels 15-19
            health = 15 + (rand() % 7); damage = 3 + (rand() % 3);
            ice = 2 + (rand() % 2); fire = 2 + (rand() % 2); 
            poison = 3; electric = 3;
            heal = 5; critd = 3;
            if(type == "Fire"){fire += 3;} //fire mage buff
            if(type == "Ice"){ice += 3;} //ice sorcerer buff
        }
        else{ //level 20 final boss
            health = 22 + (rand() % 10); damage = 4 + (rand() % 3);
            ice = 2 + (rand() % 2); fire = 2 + (rand() % 2); 
            poison = 3; electric = 3;
            heal = 7; critd = 4; critc += 5;
            if(type == "Fire"){fire += 3;} //fire mage buff
            if(type == "Ice"){ice += 3;} //ice sorcerer buff
        }
    }

    //Ruined Castle
    if(factor == "2"){
        //get enemy type
        int eType = (rand() % 20);
        if(eType < 8){type = "Wizard";} //evil wizard
        else if(eType < 13){type = "Fire";} //fire mage
        else if(eType < 18){type = "Ice";} //ice sorcerer
        else{type = "Necro";} //necromancer

        if(type == "Wizard"){critc = 15;} //crit chance
        else{critc = 10;}
        dodge = 7; //dodge chance

        //set stats
        if(levNum < 5){ //levels 1-4
            health = 8 + (rand() % 5); damage = 2 + (rand() % 3);
            ice = 1; fire = 1; poison = 1;
            electric = 1; heal = 4; critd = 1;
            if(type == "Fire"){fire = 2;} //fire mage buff
            if(type == "Ice"){ice = 2;} //ice sorcerer buff
            if(type == "Necro"){poison = 2;} //necromancer buff
        }
        else if(levNum < 10){ //levels 5-9
            health = 12 + (rand() % 8); damage = 3 + (rand() % 3);
            ice = (rand() % 3); fire = (rand() % 3); 
            poison = (rand() % 3); electric = 1;
            heal = 5; critd = 2;
            if(type == "Fire"){fire += 1;}
            if(type == "Ice"){ice += 1;}
            if(type == "Necro"){poison += 1;}
        }
        else if(levNum == 10){ //level 10 mini boss
            health = 20 + (rand() % 8); damage = 3 + (rand() % 4);
            ice = 1 + (rand() % 3); fire = 1 + (rand() % 3); 
            poison = 1 + (rand() % 3); electric = 3;
            heal = 8; critd = 3; critc += 5;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
        }
        else if(levNum < 15){ //levels 11-14
            health = 16 + (rand() % 6); damage = 3 + (rand() % 3);
            ice = 1 + (rand() % 3); fire = 1 + (rand() % 3); 
            poison = 1 + (rand() % 3); electric = 2;
            heal = 6; critd = 3;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
        }
        else if(levNum < 20){ //levels 15-19
            health = 20 + (rand() % 7); damage = 4 + (rand() % 3);
            ice = 2 + (rand() % 3); fire = 2 + (rand() % 3); 
            poison = 2 + (rand() % 3); electric = 3;
            heal = 7; critd = 4;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
        }
        else{ //level 20 final boss
            health = 30 + (rand() % 10); damage = 4 + (rand() % 5);
            ice = 2 + (rand() % 3); fire = 2 + (rand() % 3); 
            poison = 2 + (rand() % 3); electric = 4;
            heal = 9; critd = 5; critc += 3;
            if(type == "Fire"){fire += 3;}
            if(type == "Ice"){ice += 3;}
            if(type == "Necro"){poison += 3;}
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        //get enemy type
        int eType = (rand() % 20);
        if(eType < 2){type = "Wizard";} //evil wizard
        else if(eType < 6){type = "Fire";} //fire mage
        else if(eType < 10){type = "Ice";} //ice sorcerer
        else if(eType < 15){type = "Necro";} //necromancer
        else{type = "Defend";} //defender

        if(type == "Wizard"){critc = 20;} //crit chance
        else{critc = 12;}
        if(type == "Defend"){dodge = 15;} //dodge chance
        else{dodge = 10;}

        //set stats
        if(levNum < 5){ //levels 1-4
            health = 20 + (rand() % 6); damage = 3 + (rand() % 4);
            ice = 2; fire = 2; poison = 2;
            electric = 2; heal = 4; critd = 2;
            if(type == "Fire"){fire = 3;} //fire mage buff
            if(type == "Ice"){ice = 3;} //ice sorcerer buff
            if(type == "Necro"){poison = 3;} //necromancer buff
            if(type == "Defend"){heal = 8; health += 5; damage -= 2;} //defender buff
        }
        else if(levNum < 10){ //levels 5-9
            health = 24 + (rand() % 7); damage = 4 + (rand() % 3);
            ice = 1 + (rand() % 3); fire = 1 + (rand() % 3); 
            poison = 1 + (rand() % 3); electric = 2;
            heal = 6; critd = 3;
            if(type == "Fire"){fire += 1;}
            if(type == "Ice"){ice += 1;}
            if(type == "Necro"){poison += 1;}
            if(type == "Defend"){heal = 10; health += 7; damage -= 2;}
        }
        else if(levNum == 10){ //level 10 mini boss
            health = 35 + (rand() % 8); damage = 5 + (rand() % 5);
            ice = 1 + (rand() % 4); fire = 1 + (rand() % 4); 
            poison = 1 + (rand() % 4); electric = 3;
            heal = 10; critd = 4; critc += 3;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
            if(type == "Defend"){heal = 14; health += 8; damage -= 1;}
        }
        else if(levNum < 15){ //levels 11-14
            health = 28 + (rand() % 6); damage = 4 + (rand() % 3);
            ice = 1 + (rand() % 3); fire = 1 + (rand() % 3); 
            poison = 1 + (rand() % 3); electric = 3;
            heal = 8; critd = 4;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
            if(type == "Defend"){heal = 10; health += 9; damage -= 1;}
        }
        else if(levNum < 20){ //levels 15-19
            health = 32 + (rand() % 7); damage = 4 + (rand() % 4);
            ice = 2 + (rand() % 3); fire = 2 + (rand() % 3); 
            poison = 2 + (rand() % 3); electric = 4;
            heal = 10; critd = 5;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
            if(type == "Defend"){heal = 12; health += 10; damage -= 1;}
        }
        else{ //level 20 final boss
            health = 45 + (rand() % 11); damage = 4 + (rand() % 5);
            ice = 3 + (rand() % 3); fire = 3 + (rand() % 3); 
            poison = 3 + (rand() % 3); electric = 6;
            heal = 12; critd = 6; critc += 3;
            if(type == "Fire"){fire += 2;}
            if(type == "Ice"){ice += 2;}
            if(type == "Necro"){poison += 2;}
            if(type == "Defend"){heal = 15; health += 15; damage -= 2;}
        }
    }

    //Desolate Wastes
    if(factor == "4"){
        //get enemy type
        int eType = (rand() % 3);
        if(eType == 0){type = "Fire";} //fire mage
        else if(eType == 1){type = "Defend";} //defender
        else{type = "Storm";} //stormcaster

        critc = 15; //crit chance
        if(type == "Defend"){dodge = 18;} //dodge chance
        else{dodge = 12;}

        //set stats
        if(levNum < 5){ //levels 1-4
            health = 25 + (rand() % 6); damage = 4 + (rand() % 4);
            ice = 3; fire = 3; poison = 3;
            electric = 3; heal = 7; critd = 3;
            if(type == "Fire"){fire = 5;} //fire mage buff
            if(type == "Defend"){heal = 9; health += 5; damage -= 2;} //defender buff
            if(type == "Storm"){electric = 5;} //stormcaster buff
        }
        else if(levNum < 10){ //levels 5-9
            health = 30 + (rand() % 7); damage = 4 + (rand() % 5);
            ice = 2 + (rand() % 3); fire = 2 + (rand() % 3); 
            poison = 4; electric = 2 + (rand() % 3);
            heal = 9; critd = 5;
            if(type == "Fire"){fire += 2;}
            if(type == "Storm"){electric += 2;}
            if(type == "Defend"){heal = 12; health += 8; damage -= 2;}
        }
        else if(levNum == 10){ //level 10 mini boss
            health = 50 + (rand() % 11); damage = 5 + (rand() % 6);
            ice = 2 + (rand() % 4); fire = 2 + (rand() % 4); 
            electric = 1 + (rand() % 4); poison = 4;
            heal = 12; critd = 7; critc += 5;
            if(type == "Fire"){fire += 4;}
            if(type == "Storm"){electric += 4;}
            if(type == "Defend"){heal = 15; health += 10; damage -= 1;}
        }
        else if(levNum < 15){ //levels 11-14
            health = 40 + (rand() % 6); damage = 4 + (rand() % 6);
            ice = 2 + (rand() % 3); fire = 2 + (rand() % 3); 
            electric = 2 + (rand() % 3); poison = 4;
            heal = 10; critd = 5;
            if(type == "Fire"){fire += 3;}
            if(type == "Storm"){electric += 3;}
            if(type == "Defend"){heal = 13; health += 9; damage -= 1;}
        }
        else if(levNum < 20){ //levels 15-19
            health = 50 + (rand() % 7); damage = 5 + (rand() % 6);
            ice = 2 + (rand() % 4); fire = 2 + (rand() % 4); 
            electric = 2 + (rand() % 4); poison = 4;
            heal = 12; critd = 6;
            if(type == "Fire"){fire += 4;}
            if(type == "Storm"){electric += 4;}
            if(type == "Defend"){heal = 15; health += 10; damage -= 1;}
        }
        else{ //level 20 final boss
            health = 75 + (rand() % 11); damage = 6 + (rand() % 5);
            ice = 3 + (rand() % 3); fire = 3 + (rand() % 3); 
            electric = 3 + (rand() % 3); poison = 6;
            heal = 20; critd = 8; critc += 10;
            if(type == "Fire"){fire += 4;}
            if(type == "Storm"){electric += 4;}
            if(type == "Defend"){heal = 15; health += 15; damage -= 1;}
        }
    }

    //Cursed Mines
    if(factor == "5"){
        //get enemy type
        int eType = (rand() % 4);
        if(eType == 0){type = "Wizard";} //evil wizard
        else if(eType == 1){type = "Ice";} //ice sorcerer
        else if(eType == 2){type = "Unstable";} //unstable mage
        else{type = "Necro";} //necromancer

        if(type == "Wizard" || type == "Unstable"){critc = 20;} //improved crit chance
        else{critc = 15;} //basic crit chance
        dodge = 13; //dodge

        //set stats
        if(levNum < 5){ //levels 1-4
            health = 40 + (rand() % 10); damage = 5 + (rand() % 5);
            ice = 3; fire = 3; poison = 3;
            electric = 3; heal = 8; critd = 5;
            if(type == "Ice"){ice = 5;} //ice sorcerer buff
            if(type == "Unstable"){damage += 5;} //unstable mage buff
            if(type == "Necro"){poison = 5;} //necromancer buff
        }
        else if(levNum < 10){ //levels 5-9
            health = 50 + (rand() % 7); damage = 5 + (rand() % 5);
            ice = 3 + (rand() % 3); fire = 4; 
            poison = 3 + (rand() % 3); electric = 4;
            heal = 9; critd = 5;
            if(type == "Ice"){ice += 2;} //ice sorcerer buff
            if(type == "Unstable"){damage += 5;} //unstable mage buff
            if(type == "Necro"){poison += 2;} //necromancer buff
        }
        else if(levNum == 10){ //level 10 mini boss
            health = 65 + (rand() % 10); damage = 6 + (rand() % 6);
            ice = 4 + (rand() % 4); fire = 5; 
            electric = 5; poison = 4 + (rand() % 4);
            heal = 15; critd = 8; critc += 5;
            if(type == "Ice"){ice += 5;} //ice sorcerer buff
            if(type == "Unstable"){damage += 10;} //unstable mage buff
            if(type == "Necro"){poison += 5;} //necromancer buff
        }
        else if(levNum < 15){ //levels 11-14
            health = 60 + (rand() % 6); damage = 6 + (rand() % 4);
            ice = 4 + (rand() % 3); fire = 5; 
            electric = 5; poison = 4 + (rand() % 3);
            heal = 12; critd = 7;
            if(type == "Ice"){ice += 3;} //ice sorcerer buff
            if(type == "Unstable"){damage += 7;} //unstable mage buff
            if(type == "Necro"){poison += 3;} //necromancer buff
        }
        else if(levNum < 20){ //levels 15-19
            health = 70 + (rand() % 5); damage = 6 + (rand() % 6);
            ice = 4 + (rand() % 4); fire = 5; 
            electric = 5; poison = 4 + (rand() % 4);
            heal = 15; critd = 8;
            if(type == "Ice"){ice += 4;} //ice sorcerer buff
            if(type == "Unstable"){damage += 9;} //unstable mage buff
            if(type == "Necro"){poison += 4;} //necromancer buff
        }
        else{ //level 20 final boss
            health = 90 + (rand() % 11); damage = 7 + (rand() % 5);
            ice = 5 + (rand() % 3); fire = 6; 
            electric = 6; poison = 5 + (rand() % 3);
            heal = 25; critd = 10; critc += 10;
            if(type == "Ice"){ice += 5;} //ice sorcerer buff
            if(type == "Unstable"){damage += 12;} //unstable mage buff
            if(type == "Necro"){poison += 5;} //necromancer buff
        }
    }

    //Endless mode
    if(factor == "X"){
        //get enemy type
        int eType = rand()%7;
        if(eType == 0){type = "Wizard";} //evil wizard
        else if(eType == 1){type = "Fire";} //fire mage
        else if(eType == 2){type = "Ice";} //ice sorcerer
        else if(eType == 3){type = "Necro";} //necromancer
        else if(eType == 4){type = "Storm";} //stormcaster
        else if(eType == 5){type = "Unstable";} //stormcaster
        else{type = "Defend";} //defender

        //factor strength based off endless level
        if(levNum < 10){critc = 5; dodge = 5;}
        else if(levNum < 100){critc = 10; dodge = 10;}
        else if(levNum < 250){critc = 20; dodge = 15;}
        else if(levNum < 500){critc = 30; dodge = 20;}
        else if(levNum < 1000){critc = 40; dodge = 25;}
        else{critc = 45; dodge = 30;}
        //boss
        if(levNum%10 == 0){
            health += rand()%(levNum/5); damage += 5;
            heal += rand()%(levNum/10); critd += 5;
            critc += 5; dodge += 2;
        }

        //set stats
        health = 4 + (rand() % levNum); 
        damage = 2 + (rand() % levNum/4);
        ice = 3 + (rand() % levNum/10); 
        fire = 3 + (rand() % levNum/10); 
        poison = 3 + (rand() % levNum/10); 
        electric = 3 + (rand() % levNum/10); 
        heal = 3 + (rand() % levNum/3); 
        critd = 2 + (rand() % levNum/5);
        if(type == "Wizard" || type == "Unstable"){critc += 2;}
        if(type == "Fire"){fire += 1 + (rand() % levNum/10);}
        if(type == "Ice"){ice += 1 + (rand() % levNum/10);}
        if(type == "Necro"){poison += 1 + (rand() % levNum/10);}
        if(type == "Storm"){electric += 1 + (rand() % levNum/10);}
        if(type == "Unstable"){
            damage += 1 + (rand() % levNum/10);
            critd += 1 + (rand() % levNum/20);
        }
        if(type == "Defend"){
            heal += 1 + (rand() % levNum/10); 
            health += 3 + (rand() % levNum/5); 
            damage -= (rand() % levNum/10);
            dodge +=3;
        }

        //check that stats will work (health/damage)
        if(health < (levNum - 40)){health = levNum - 40;}
        if(damage < (levNum - 150)){damage = levNum - 150;}
        if(damage < 1){damage = 10;} //in unlikely chance defender dmg drops below 1, sets to a base dmg
    }

    generate_name();
    
    if((damage - player.shield) < 0){damage = 0;} //apply shield
    else{damage -= player.shield;}
}

void Enemy::generate_name(){
    string f_name[50] = {"Yarno", "Belloc", "Soma", "Yeen", "Marcuus", "Liol", "Quand", "Jurno", "Corsto", "Kaimo", "Lord Denna", "Hubert",
"Wernda", "Helena", "Astan", "Lucia", "Ferdinand", "Orp", "Oogga", "Ray", "Rendolf", "Portian", "Billis", "Quamm", "Foxy", "Holga", "Waine", 
"Harkken", "Folda", "Swinn", "Varis", "Galdaf", "Halfdan", "Eldar", "Roirand", "Keet", "Wet Sod", "Germaine", "Zandar", "Kieran", "Noss", 
"Theoran", "Juju", "Yymigg", "Deathman", "Cildas", "Inhilla", "Harper", "Jermalline", "Biggo"};
    string l_name[50] = {"Hellfire", "Wedlok", "Hona", "Perf", "Orelius", "The Slayer", "The Butcher", "Doombringer", "The Savage", "The Destroyer", 
"The Loser", "The Fox", "Hogtie", "Far-Wanderer", "Oathbreaker", "Kindy", "Wok", "Erp", "King Killer", "Nightwalker", "Pain-Bringer", "Xondoloxa", 
"Of The Forest", "Of The Warlords", "The Annoying", "Westbound", "The Dead", "The Lost", "The Old", "The Young", "Gillian", "The Fallen", "Bell", 
"Jund", "Ungundo", "Jojo", "Kiwi", "The Wise", "The Hopeless", "Hungerer", "Aaros", "Qi", "Theros", "Queen Lover", "Flesh Eater", "Swedle", "Zikolthu", 
"The Small", "The Chum", "Of The Wolves"};

    string enemy_name;
    int random = (rand() % 50);
    enemy_name = f_name[random] + " ";
    random = (rand() % 50);
    enemy_name += l_name[random];
    name = enemy_name;
}

void Enemy::reset_status(){ //quickly set all enemy status to 0;
    for(int i = 0; i < 3; i++){status[i] = 0;}
}
