#include "spell.h"

Spell::Spell(){name = "spell"; type = "N/A"; effect = 0;}

Spell::Spell(string nm, string tp, int eff){
    name = nm != "" ? nm : "spell";
    type = tp != "" ? tp : "N/A";
    effect = eff > 0 ? eff : 0;
}

void Spell::get_card(int hp, int dmg, int fire, int ice, int poison, int electric, int heal){
    int factor, eff;
    string nm, tp;

    //get card name/type
    factor = rand() % 23;
    if(factor < 6){ //attack card
        tp = "attack";
        factor = rand() % 6;
        if(factor < 2){nm = "HEX"; eff = dmg;}
        else if(factor < 4){nm = "JINX"; eff = (1 + dmg);}
        else if(factor < 5){nm = "STRIKE"; eff = (2 + dmg);}
        else{tp = "atk-stun"; nm = "STUNNING STRIKE"; eff = (1 + dmg) / 2;}
    }
    else if(factor < 9){ //fire
        tp = "fire";
        factor = rand() % 6;
        if(factor < 3){nm = "BURN"; eff = (1 + dmg + fire);}
        else if(factor < 5){nm = "FIREBOLT"; eff = (2 + dmg + fire);}
        else{nm = "FIREBALL"; eff = (4 + dmg + fire);}
    }
    else if(factor < 12){ //ice
        tp = "ice";
        factor = rand() % 3;
        if(factor == 0){nm = "ICY WIND"; eff = (dmg + ice); tp = "ice-stun";}
        else if(factor == 1){nm = "FREEZE"; eff = (1 + dmg + ice);}
        else{nm = "ICE STORM"; eff = (2 + dmg + ice);}
    }
    else if(factor < 15){ //poison
        tp = "poison";
        factor = rand() % 6;
        if(factor < 2){nm = "ACID SPRAY"; eff = (1 + dmg + poison);}
        else if(factor < 5){nm = "POISON RAIN"; eff = (2 + dmg + poison);}
        else{nm = "DEATH CLOUD"; eff = (4 + dmg + poison);}
    }
    else if(factor < 19){ //heal
        tp = "heal";
        factor = rand() % 3;
        if(factor == 0){nm = "CURE WOUNDS"; eff = (1 + heal);}
        else if(factor == 1){nm = "HEALING WORD"; eff = (2 + heal);}
        else{nm = "RESTORATION"; eff = (3 + heal);}
    }
    else if(factor < 22){ //electric
        tp = "electric";
        factor = rand() % 4;
        if(factor == 0){nm = "SHOCK"; eff = (dmg + electric); tp = "electric-stun";}
        else if(factor < 3){nm = "ZAP"; eff = (1 + dmg + electric);}
        else{nm = "LIGHTNING BOLT"; eff = (3 + dmg + electric);}
    }
    else{ //drain
        tp = "drain";
        factor = rand() % 3;
        if(factor == 0){nm = "DARK RITUAL"; eff = (1 +((dmg + heal)/2));}
        else if(factor == 1){nm = "LIFE DRAIN"; eff = (2 +((dmg + heal)/2));}
        else{nm = "SOUL STEAL"; eff = (3 +((dmg + heal)/2));}
    }
    name = nm; type = tp; effect = eff;
}
