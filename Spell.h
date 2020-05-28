#include <Arduino.h>


class Spell{
  public:
    char spellName[21];
    char casting_time[13];
    char components[11];
    char duration[15];
    uint8_t level;
    char range[11];
    bool ritual;
    char school[15];
    char page0[420];
    char page1[420];
    char page2[420];
    char page3[420];

    Spell(const char* n,const char* ct,const char* com,const char* dur, uint8_t lv,const char* r,bool ri, const char* sc, const char* p0, const char* p1, const char* p2, const char* p3);
};
