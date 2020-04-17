#include <Arduino.h>


class Spell{
  public:
    char spellName[21];
    char casting_time[13];
    char components[11];
    char duration[11];
    uint8_t level;
    char range[11];
    bool ritual;
    char school[11];
    char description[300];

    Spell(const char* n,const char* ct,const char* com,const char* dur, uint8_t lv,const char* r,bool ri, const char* sc, const char* de);
};

/*
 * 
 * 
//////////////////////////////////////////////
#include <Arduino.h>
#include "Spell.h"

class SpellBook {
  public:
    char spellName[20];
    char casting_time[10];

    SpellBook(const char* n, const char* ct);
};

SpellBook::SpellBook(const char* n, const char* ct) {
  strncpy(spellName, n, sizeof(spellName) - 1);
  spellName[sizeof(spellName) - 1] = '\0';
  strncpy(casting_time, ct, sizeof(casting_time) - 1);
  casting_time[sizeof(casting_time) - 1] = '\0';
}

 */
