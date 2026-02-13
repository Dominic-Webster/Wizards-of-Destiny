#include "enemy.h"
using namespace std;


Enemy Enemy::make_enemy(string factor, Player player, int levNum){
    Enemy new_enemy;

    //Misty Dungeon
    if(factor == "1"){
        //get enemy type
        int eType = (rand() % 4);
        if(eType < 2){new_enemy.type = "Wizard";} //evil wizard
        else if(eType == 2){new_enemy.type = "Fire";} //fire mage 
        else{new_enemy.type = "Ice";} //ice sorcerer
        new_enemy.critc = 10; //crit chance
        new_enemy.dodge = 5; //dodge chance

        //set stats based on adventure level
        if(levNum < 5){ //levels 1-4
            new_enemy.health = 4 + (rand() % 5); new_enemy.damage = 1 + (rand() % 2);
            new_enemy.ice = 0; new_enemy.fire = 0; new_enemy.poison = 0; 
            new_enemy.electric = 0; new_enemy.heal = 1; new_enemy.critd = 1;
            if(new_enemy.type == "Fire"){new_enemy.fire = 1;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice = 1;} //ice sorcerer buff
        }
        else if(levNum < 10){ //levels 5-9
            new_enemy.health = 8 + (rand() % 6); new_enemy.damage = 1 + (rand() % 3);
            new_enemy.ice = (rand() % 2); new_enemy.fire = (rand() % 2); 
            new_enemy.poison = 1; new_enemy.electric = 1;
            new_enemy.heal = 2; new_enemy.critd = 1;
            if(new_enemy.type == "Fire"){new_enemy.fire += 1;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice += 1;} //ice sorcerer buff
        }
        else if(levNum == 10){ //level 10 mini boss
            new_enemy.health = 15 + (rand() % 6); new_enemy.damage = 3 + (rand() % 3);
            new_enemy.ice = 2 + (rand() % 2); new_enemy.fire = 2 + (rand() % 2); 
            new_enemy.poison = 3; new_enemy.electric = 3;
            new_enemy.heal = 5; new_enemy.critd = 2; new_enemy.critc += 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;} //ice sorcerer buff
        }
        else if(levNum < 15){ //levels 11-14
            new_enemy.health = 12 + (rand() % 6); new_enemy.damage = 2 + (rand() % 3);
            new_enemy.ice = 1 + (rand() % 2); new_enemy.fire = 1 + (rand() % 2); 
            new_enemy.poison = 2; new_enemy.electric = 2;
            new_enemy.heal = 4; new_enemy.critd = 2;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;} //ice sorcerer buff
        }
        else if(levNum < 20){ //levels 15-19
            new_enemy.health = 15 + (rand() % 7); new_enemy.damage = 3 + (rand() % 3);
            new_enemy.ice = 2 + (rand() % 2); new_enemy.fire = 2 + (rand() % 2); 
            new_enemy.poison = 3; new_enemy.electric = 3;
            new_enemy.heal = 5; new_enemy.critd = 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 3;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice += 3;} //ice sorcerer buff
        }
        else{ //level 20 final boss
            new_enemy.health = 22 + (rand() % 10); new_enemy.damage = 4 + (rand() % 3);
            new_enemy.ice = 2 + (rand() % 2); new_enemy.fire = 2 + (rand() % 2); 
            new_enemy.poison = 3; new_enemy.electric = 3;
            new_enemy.heal = 7; new_enemy.critd = 4; new_enemy.critc += 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 3;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice += 3;} //ice sorcerer buff
        }
    }

    //Ruined Castle
    if(factor == "2"){
        //get enemy type
        int eType = (rand() % 20);
        if(eType < 8){new_enemy.type = "Wizard";} //evil wizard
        else if(eType < 13){new_enemy.type = "Fire";} //fire mage
        else if(eType < 18){new_enemy.type = "Ice";} //ice sorcerer
        else{new_enemy.type = "Necro";} //necromancer

        if(new_enemy.type == "Wizard"){new_enemy.critc = 15;} //crit chance
        else{new_enemy.critc = 10;}
        new_enemy.dodge = 7; //dodge chance

        //set stats
        if(levNum < 5){ //levels 1-4
            new_enemy.health = 8 + (rand() % 5); new_enemy.damage = 2 + (rand() % 3);
            new_enemy.ice = 1; new_enemy.fire = 1; new_enemy.poison = 1;
            new_enemy.electric = 1; new_enemy.heal = 4; new_enemy.critd = 1;
            if(new_enemy.type == "Fire"){new_enemy.fire = 2;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice = 2;} //ice sorcerer buff
            if(new_enemy.type == "Necro"){new_enemy.poison = 2;} //necromancer buff
        }
        else if(levNum < 10){ //levels 5-9
            new_enemy.health = 12 + (rand() % 8); new_enemy.damage = 3 + (rand() % 3);
            new_enemy.ice = (rand() % 3); new_enemy.fire = (rand() % 3); 
            new_enemy.poison = (rand() % 3); new_enemy.electric = 1;
            new_enemy.heal = 5; new_enemy.critd = 2;
            if(new_enemy.type == "Fire"){new_enemy.fire += 1;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 1;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 1;}
        }
        else if(levNum == 10){ //level 10 mini boss
            new_enemy.health = 20 + (rand() % 8); new_enemy.damage = 3 + (rand() % 4);
            new_enemy.ice = 1 + (rand() % 3); new_enemy.fire = 1 + (rand() % 3); 
            new_enemy.poison = 1 + (rand() % 3); new_enemy.electric = 3;
            new_enemy.heal = 8; new_enemy.critd = 3; new_enemy.critc += 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
        }
        else if(levNum < 15){ //levels 11-14
            new_enemy.health = 16 + (rand() % 6); new_enemy.damage = 3 + (rand() % 3);
            new_enemy.ice = 1 + (rand() % 3); new_enemy.fire = 1 + (rand() % 3); 
            new_enemy.poison = 1 + (rand() % 3); new_enemy.electric = 2;
            new_enemy.heal = 6; new_enemy.critd = 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
        }
        else if(levNum < 20){ //levels 15-19
            new_enemy.health = 20 + (rand() % 7); new_enemy.damage = 4 + (rand() % 3);
            new_enemy.ice = 2 + (rand() % 3); new_enemy.fire = 2 + (rand() % 3); 
            new_enemy.poison = 2 + (rand() % 3); new_enemy.electric = 3;
            new_enemy.heal = 7; new_enemy.critd = 4;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
        }
        else{ //level 20 final boss
            new_enemy.health = 30 + (rand() % 10); new_enemy.damage = 4 + (rand() % 5);
            new_enemy.ice = 2 + (rand() % 3); new_enemy.fire = 2 + (rand() % 3); 
            new_enemy.poison = 2 + (rand() % 3); new_enemy.electric = 4;
            new_enemy.heal = 9; new_enemy.critd = 5; new_enemy.critc += 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 3;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 3;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 3;}
        }
    }

    //Mountain of Despair
    if(factor == "3"){
        //get enemy type
        int eType = (rand() % 20);
        if(eType < 2){new_enemy.type = "Wizard";} //evil wizard
        else if(eType < 6){new_enemy.type = "Fire";} //fire mage
        else if(eType < 10){new_enemy.type = "Ice";} //ice sorcerer
        else if(eType < 15){new_enemy.type = "Necro";} //necromancer
        else{new_enemy.type = "Defend";} //defender

        if(new_enemy.type == "Wizard"){new_enemy.critc = 20;} //crit chance
        else{new_enemy.critc = 12;}
        if(new_enemy.type == "Defend"){new_enemy.dodge = 15;} //dodge chance
        else{new_enemy.dodge = 10;}

        //set stats
        if(levNum < 5){ //levels 1-4
            new_enemy.health = 20 + (rand() % 6); new_enemy.damage = 3 + (rand() % 4);
            new_enemy.ice = 2; new_enemy.fire = 2; new_enemy.poison = 2;
            new_enemy.electric = 2; new_enemy.heal = 4; new_enemy.critd = 2;
            if(new_enemy.type == "Fire"){new_enemy.fire = 3;} //fire mage buff
            if(new_enemy.type == "Ice"){new_enemy.ice = 3;} //ice sorcerer buff
            if(new_enemy.type == "Necro"){new_enemy.poison = 3;} //necromancer buff
            if(new_enemy.type == "Defend"){new_enemy.heal = 8; new_enemy.health += 5; new_enemy.damage -= 2;} //defender buff
        }
        else if(levNum < 10){ //levels 5-9
            new_enemy.health = 24 + (rand() % 7); new_enemy.damage = 4 + (rand() % 3);
            new_enemy.ice = 1 + (rand() % 3); new_enemy.fire = 1 + (rand() % 3); 
            new_enemy.poison = 1 + (rand() % 3); new_enemy.electric = 2;
            new_enemy.heal = 6; new_enemy.critd = 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 1;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 1;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 1;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 10; new_enemy.health += 7; new_enemy.damage -= 2;}
        }
        else if(levNum == 10){ //level 10 mini boss
            new_enemy.health = 35 + (rand() % 8); new_enemy.damage = 5 + (rand() % 5);
            new_enemy.ice = 1 + (rand() % 4); new_enemy.fire = 1 + (rand() % 4); 
            new_enemy.poison = 1 + (rand() % 4); new_enemy.electric = 3;
            new_enemy.heal = 10; new_enemy.critd = 4; new_enemy.critc += 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 14; new_enemy.health += 8; new_enemy.damage -= 1;}
        }
        else if(levNum < 15){ //levels 11-14
            new_enemy.health = 28 + (rand() % 6); new_enemy.damage = 4 + (rand() % 3);
            new_enemy.ice = 1 + (rand() % 3); new_enemy.fire = 1 + (rand() % 3); 
            new_enemy.poison = 1 + (rand() % 3); new_enemy.electric = 3;
            new_enemy.heal = 8; new_enemy.critd = 4;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 10; new_enemy.health += 9; new_enemy.damage -= 1;}
        }
        else if(levNum < 20){ //levels 15-19
            new_enemy.health = 32 + (rand() % 7); new_enemy.damage = 4 + (rand() % 4);
            new_enemy.ice = 2 + (rand() % 3); new_enemy.fire = 2 + (rand() % 3); 
            new_enemy.poison = 2 + (rand() % 3); new_enemy.electric = 4;
            new_enemy.heal = 10; new_enemy.critd = 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 12; new_enemy.health += 10; new_enemy.damage -= 1;}
        }
        else{ //level 20 final boss
            new_enemy.health = 45 + (rand() % 11); new_enemy.damage = 4 + (rand() % 5);
            new_enemy.ice = 3 + (rand() % 3); new_enemy.fire = 3 + (rand() % 3); 
            new_enemy.poison = 3 + (rand() % 3); new_enemy.electric = 6;
            new_enemy.heal = 12; new_enemy.critd = 6; new_enemy.critc += 3;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;}
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 15; new_enemy.health += 15; new_enemy.damage -= 2;}
        }
    }

    //Desolate Wastes
    if(factor == "4"){
        //get enemy type
        int eType = (rand() % 3);
        if(eType == 0){new_enemy.type = "Fire";} //fire mage
        else if(eType == 1){new_enemy.type = "Defend";} //defender
        else{new_enemy.type = "Storm";} //stormcaster

        new_enemy.critc = 15; //crit chance
        if(new_enemy.type == "Defend"){new_enemy.dodge = 18;} //dodge chance
        else{new_enemy.dodge = 12;}

        //set stats
        if(levNum < 5){ //levels 1-4
            new_enemy.health = 25 + (rand() % 6); new_enemy.damage = 4 + (rand() % 4);
            new_enemy.ice = 3; new_enemy.fire = 3; new_enemy.poison = 3;
            new_enemy.electric = 3; new_enemy.heal = 7; new_enemy.critd = 3;
            if(new_enemy.type == "Fire"){new_enemy.fire = 5;} //fire mage buff
            if(new_enemy.type == "Defend"){new_enemy.heal = 9; new_enemy.health += 5; new_enemy.damage -= 2;} //defender buff
            if(new_enemy.type == "Storm"){new_enemy.electric = 5;} //stormcaster buff
        }
        else if(levNum < 10){ //levels 5-9
            new_enemy.health = 30 + (rand() % 7); new_enemy.damage = 4 + (rand() % 5);
            new_enemy.ice = 2 + (rand() % 3); new_enemy.fire = 2 + (rand() % 3); 
            new_enemy.poison = 4; new_enemy.electric = 2 + (rand() % 3);
            new_enemy.heal = 9; new_enemy.critd = 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 2;}
            if(new_enemy.type == "Storm"){new_enemy.electric += 2;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 12; new_enemy.health += 8; new_enemy.damage -= 2;}
        }
        else if(levNum == 10){ //level 10 mini boss
            new_enemy.health = 50 + (rand() % 11); new_enemy.damage = 5 + (rand() % 6);
            new_enemy.ice = 2 + (rand() % 4); new_enemy.fire = 2 + (rand() % 4); 
            new_enemy.electric = 1 + (rand() % 4); new_enemy.poison = 4;
            new_enemy.heal = 12; new_enemy.critd = 7; new_enemy.critc += 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 4;}
            if(new_enemy.type == "Storm"){new_enemy.electric += 4;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 15; new_enemy.health += 10; new_enemy.damage -= 1;}
        }
        else if(levNum < 15){ //levels 11-14
            new_enemy.health = 40 + (rand() % 6); new_enemy.damage = 4 + (rand() % 6);
            new_enemy.ice = 2 + (rand() % 3); new_enemy.fire = 2 + (rand() % 3); 
            new_enemy.electric = 2 + (rand() % 3); new_enemy.poison = 4;
            new_enemy.heal = 10; new_enemy.critd = 5;
            if(new_enemy.type == "Fire"){new_enemy.fire += 3;}
            if(new_enemy.type == "Storm"){new_enemy.electric += 3;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 13; new_enemy.health += 9; new_enemy.damage -= 1;}
        }
        else if(levNum < 20){ //levels 15-19
            new_enemy.health = 50 + (rand() % 7); new_enemy.damage = 5 + (rand() % 6);
            new_enemy.ice = 2 + (rand() % 4); new_enemy.fire = 2 + (rand() % 4); 
            new_enemy.electric = 2 + (rand() % 4); new_enemy.poison = 4;
            new_enemy.heal = 12; new_enemy.critd = 6;
            if(new_enemy.type == "Fire"){new_enemy.fire += 4;}
            if(new_enemy.type == "Storm"){new_enemy.electric += 4;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 15; new_enemy.health += 10; new_enemy.damage -= 1;}
        }
        else{ //level 20 final boss
            new_enemy.health = 75 + (rand() % 11); new_enemy.damage = 6 + (rand() % 5);
            new_enemy.ice = 3 + (rand() % 3); new_enemy.fire = 3 + (rand() % 3); 
            new_enemy.electric = 3 + (rand() % 3); new_enemy.poison = 6;
            new_enemy.heal = 20; new_enemy.critd = 8; new_enemy.critc += 10;
            if(new_enemy.type == "Fire"){new_enemy.fire += 4;}
            if(new_enemy.type == "Storm"){new_enemy.electric += 4;}
            if(new_enemy.type == "Defend"){new_enemy.heal = 15; new_enemy.health += 15; new_enemy.damage -= 1;}
        }
    }

    //Cursed Mines
    if(factor == "5"){
        //get enemy type
        int eType = (rand() % 4);
        if(eType == 0){new_enemy.type = "Wizard";} //evil wizard
        else if(eType == 1){new_enemy.type = "Ice";} //ice sorcerer
        else if(eType == 2){new_enemy.type = "Unstable";} //unstable mage
        else{new_enemy.type = "Necro";} //necromancer

        if(new_enemy.type == "Wizard" || new_enemy.type == "Unstable"){new_enemy.critc = 20;} //improved crit chance
        else{new_enemy.critc = 15;} //basic crit chance
        new_enemy.dodge = 13; //dodge

        //set stats
        if(levNum < 5){ //levels 1-4
            new_enemy.health = 40 + (rand() % 10); new_enemy.damage = 5 + (rand() % 5);
            new_enemy.ice = 3; new_enemy.fire = 3; new_enemy.poison = 3;
            new_enemy.electric = 3; new_enemy.heal = 8; new_enemy.critd = 5;
            if(new_enemy.type == "Ice"){new_enemy.ice = 5;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 5;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison = 5;} //necromancer buff
        }
        else if(levNum < 10){ //levels 5-9
            new_enemy.health = 50 + (rand() % 7); new_enemy.damage = 5 + (rand() % 5);
            new_enemy.ice = 3 + (rand() % 3); new_enemy.fire = 4; 
            new_enemy.poison = 3 + (rand() % 3); new_enemy.electric = 4;
            new_enemy.heal = 9; new_enemy.critd = 5;
            if(new_enemy.type == "Ice"){new_enemy.ice += 2;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 5;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison += 2;} //necromancer buff
        }
        else if(levNum == 10){ //level 10 mini boss
            new_enemy.health = 65 + (rand() % 10); new_enemy.damage = 6 + (rand() % 6);
            new_enemy.ice = 4 + (rand() % 4); new_enemy.fire = 5; 
            new_enemy.electric = 5; new_enemy.poison = 4 + (rand() % 4);
            new_enemy.heal = 15; new_enemy.critd = 8; new_enemy.critc += 5;
            if(new_enemy.type == "Ice"){new_enemy.ice += 5;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 10;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison += 5;} //necromancer buff
        }
        else if(levNum < 15){ //levels 11-14
            new_enemy.health = 60 + (rand() % 6); new_enemy.damage = 6 + (rand() % 4);
            new_enemy.ice = 4 + (rand() % 3); new_enemy.fire = 5; 
            new_enemy.electric = 5; new_enemy.poison = 4 + (rand() % 3);
            new_enemy.heal = 12; new_enemy.critd = 7;
            if(new_enemy.type == "Ice"){new_enemy.ice += 3;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 7;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison += 3;} //necromancer buff
        }
        else if(levNum < 20){ //levels 15-19
            new_enemy.health = 70 + (rand() % 5); new_enemy.damage = 6 + (rand() % 6);
            new_enemy.ice = 4 + (rand() % 4); new_enemy.fire = 5; 
            new_enemy.electric = 5; new_enemy.poison = 4 + (rand() % 4);
            new_enemy.heal = 15; new_enemy.critd = 8;
            if(new_enemy.type == "Ice"){new_enemy.ice += 4;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 9;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison += 4;} //necromancer buff
        }
        else{ //level 20 final boss
            new_enemy.health = 90 + (rand() % 11); new_enemy.damage = 7 + (rand() % 5);
            new_enemy.ice = 5 + (rand() % 3); new_enemy.fire = 6; 
            new_enemy.electric = 6; new_enemy.poison = 5 + (rand() % 3);
            new_enemy.heal = 25; new_enemy.critd = 10; new_enemy.critc += 10;
            if(new_enemy.type == "Ice"){new_enemy.ice += 5;} //ice sorcerer buff
            if(new_enemy.type == "Unstable"){new_enemy.damage += 12;} //unstable mage buff
            if(new_enemy.type == "Necro"){new_enemy.poison += 5;} //necromancer buff
        }
    }

    //Endless mode
    if(factor == "X"){
        //get enemy type
        int eType = rand()%7;
        if(eType == 0){new_enemy.type = "Wizard";} //evil wizard
        else if(eType == 1){new_enemy.type = "Fire";} //fire mage
        else if(eType == 2){new_enemy.type = "Ice";} //ice sorcerer
        else if(eType == 3){new_enemy.type = "Necro";} //necromancer
        else if(eType == 4){new_enemy.type = "Storm";} //stormcaster
        else if(eType == 5){new_enemy.type = "Unstable";} //stormcaster
        else{new_enemy.type = "Defend";} //defender

        //factor strength based off endless level
        if(levNum < 10){new_enemy.critc = 5; new_enemy.dodge = 5;}
        else if(levNum < 100){new_enemy.critc = 10; new_enemy.dodge = 10;}
        else if(levNum < 250){new_enemy.critc = 20; new_enemy.dodge = 15;}
        else if(levNum < 500){new_enemy.critc = 30; new_enemy.dodge = 20;}
        else if(levNum < 1000){new_enemy.critc = 40; new_enemy.dodge = 25;}
        else{new_enemy.critc = 45; new_enemy.dodge = 30;}
        //boss
        if(levNum%10 == 0){
            new_enemy.health += rand()%(levNum/5); new_enemy.damage += 5;
            new_enemy.heal += rand()%(levNum/10); new_enemy.critd += 5;
            new_enemy.critc += 5; new_enemy.dodge += 2;
        }

        //set stats
        new_enemy.health = 4 + (rand() % levNum); 
        new_enemy.damage = 2 + (rand() % levNum/4);
        new_enemy.ice = 3 + (rand() % levNum/10); 
        new_enemy.fire = 3 + (rand() % levNum/10); 
        new_enemy.poison = 3 + (rand() % levNum/10); 
        new_enemy.electric = 3 + (rand() % levNum/10); 
        new_enemy.heal = 3 + (rand() % levNum/3); 
        new_enemy.critd = 2 + (rand() % levNum/5);
        if(new_enemy.type == "Wizard" || new_enemy.type == "Unstable"){new_enemy.critc += 2;}
        if(new_enemy.type == "Fire"){new_enemy.fire += 1 + (rand() % levNum/10);}
        if(new_enemy.type == "Ice"){new_enemy.ice += 1 + (rand() % levNum/10);}
        if(new_enemy.type == "Necro"){new_enemy.poison += 1 + (rand() % levNum/10);}
        if(new_enemy.type == "Storm"){new_enemy.electric += 1 + (rand() % levNum/10);}
        if(new_enemy.type == "Unstable"){
            new_enemy.damage += 1 + (rand() % levNum/10);
            new_enemy.critd += 1 + (rand() % levNum/20);
        }
        if(new_enemy.type == "Defend"){
            new_enemy.heal += 1 + (rand() % levNum/10); 
            new_enemy.health += 3 + (rand() % levNum/5); 
            new_enemy.damage -= (rand() % levNum/10);
            new_enemy.dodge +=3;
        }

        //check that stats will work (health/damage)
        if(new_enemy.health < (levNum - 40)){new_enemy.health = levNum - 40;}
        if(new_enemy.damage < (levNum - 150)){new_enemy.damage = levNum - 150;}
        if(new_enemy.damage < 1){new_enemy.damage = 10;} //in unlikely chance defender dmg drops below 1, sets to a base dmg
    }

    new_enemy.generate_name();
    
    if((new_enemy.damage - player.shield) < 0){new_enemy.damage = 0;} //apply shield
    else{new_enemy.damage -= player.shield;}

    return new_enemy;
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
