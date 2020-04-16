#include <Arduino.h>

class SpellBook{
  public:
    char spellName[20];
    char casting_time[10];
    char components[10];
    char duration[10];
    uint8_t level;
    char range[10];
    bool ritual;
    char school[10];
    char description[300];

    SpellBook(char n[20],char ct[10],char com[10],char dur[10], uint8_t lv,char r[10],bool ri, char sc[10], char de[300]);
};
