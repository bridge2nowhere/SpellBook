#include "Spell.h"

Spell::Spell(const char* n,const char* ct,const char* com,const char* dur, uint8_t lv,const char* r,bool ri, const char* sc, const char* p0, const char* p1, const char* p2, const char* p3) {
    strncpy(spellName, n, sizeof(spellName)-1);
    spellName[sizeof(spellName) - 1] = '\0';
    
    strncpy(casting_time, ct, sizeof(casting_time)-1);
    casting_time[sizeof(casting_time) - 1] = '\0';
    
    strncpy(components, com, sizeof(components)-1);
    components[sizeof(components) - 1] = '\0';
    
    strncpy(duration, dur, sizeof(duration)-1);
    duration[sizeof(duration) - 1] = '\0';
    
    level = lv;
    
    strncpy(range, r, sizeof(range)-1);
    range[sizeof(range) - 1] = '\0';
    
    ritual = ri;
    
    strncpy(school, sc, sizeof(school)-1);
    school[sizeof(school) - 1] = '\0';

    strncpy(page0, p0, sizeof(page0)-1);
    page0[sizeof(page0) - 1] = '\0';
       
    strncpy(page1, p1, sizeof(page1)-1);
    page1[sizeof(page1) - 1] = '\0';

    strncpy(page2, p2, sizeof(page2)-1);
    page2[sizeof(page2) - 1] = '\0';

    strncpy(page3, p3, sizeof(page3)-1);
    page3[sizeof(page3) - 1] = '\0';

    
}
