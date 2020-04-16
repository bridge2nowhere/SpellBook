#include "SpellBook.h"

SpellBook::SpellBook(char n[20],char ct[10],char com[10],char dur[10], uint8_t lv,char r[10],bool ri, char sc[10], char de[300]) {
    strcpy(spellName, n);
    strcpy(casting_time, ct);
    strcpy(components, com);
    strcpy(duration, dur);
    level = lv;
    strcpy(range, r);
    ritual = ri;
    strcpy(school, sc);
    strcpy(description, de);
}
