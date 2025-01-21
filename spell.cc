#include "spell.h"

Spell::Spell(){name = "spell"; type = "N/A"; effect = 0;}

Spell::Spell(string nm, string tp, int eff){
    name = nm != "" ? nm : "spell";
    type = tp != "" ? tp : "N/A";
    effect = eff > 0 ? eff : 0;
}

