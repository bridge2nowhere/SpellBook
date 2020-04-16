#include <CircularBuffer.h>
#include <ArduinoJson.h>
#include "SpellBook.h"

const uint8_t TOME_LENGTH = 6;
CircularBuffer<SpellBook*, TOME_LENGTH> tome;


void setup() {
  Serial.begin(9600);
  const size_t capacity = JSON_ARRAY_SIZE(6) + 6 * JSON_OBJECT_SIZE(9) + 2150;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, F("[{\"name\":\"Mending\",\"casting_time\":\"1 minute\",\"components\":\"V,S,M\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"touch\",\"ritual\":false,\"school\":\"conjuration\",\"description\":\"This spell repairs a single break or tear in an object. As long as the break or tear is no larger than 1 foot in any dimension. This spell can physically repair a magic item or construct, but can’t restore magic.\"},{\"name\":\"Sacred Flame\",\"casting_time\":\"1 action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"evocation\",\"description\":\"The target must succeed on a Dexterity saving throw or take 1d8 radiant damage. The target gains no benefit from cover for this saving throw. At higher level 5th level (2d8), 11th level (3d8), and 17th level (4d8).\"},{\"name\":\"Spare the Dying\",\"casting_time\":\"Bonus Action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"Necromancy\",\"description\":\"You touch a living creature that has 0 hit points. The creature becomes stable. This spell has no effect on undead or constructs.\"},{\"name\":\"Spare the Dying\",\"casting_time\":\"Bonus Action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"Necromancy\",\"description\":\"You touch a living creature that has 0 hit points. The creature becomes stable. This spell has no effect on undead or constructs.\"},{\"name\":\"Thaumaturgy\",\"casting_time\":\"1 Action\",\"components\":\"V\",\"duration\":\"<1min\",\"level\":0,\"range\":\"30 feet\",\"ritual\":false,\"school\":\"Transmutation\",\"description\":\"Create one of effects within range:Voice booms 3x|Change Flames flicker, brighten, dim, or change color|Harmless tremors|Sound from a point|Door or window to fly open or slam shut|Alter the appearance of your eyes.\"},{\"name\":\"Tholl the Dead\",\"casting_time\":\"1 Action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"Necromancy\",\"description\":\"One creature you can see must succeed on a Wisdom saving throw or take 1d8 necrotic damage, or 1d12 necrotic damage if HP missing. At 5th level (2d8 or 2d12), 11th level (3d8 or 3d12), and 17th level (4d8 or 4d12).\"}]"));

  for (int i = 0; i < TOME_LENGTH; i++) {
    JsonObject root = doc[i];

    const char* root_name = root["name"]; // "Mending"
    const char* root_casting_time = root["casting_time"]; // "1 minute"
    const char* root_components = root["components"]; // "V,S,M"
    const char* root_duration = root["duration"]; // "Instantaneous"
    int root_level = root["level"]; // 0
    const char* root_range = root["range"]; // "touch"
    bool root_ritual = root["ritual"]; // false
    const char* root_school = root["school"]; // "conjuration"
    const char* root_description = root["description"]; // "This spell repairs"
    
    Serial.println(root_name);
    SpellBook* newSpell = new SpellBook(root_name.as<const char*>, root_casting_time, root_components, root_duration, root_level, root_range, root_ritual, root_school, root_description);
    tome.push(newSpell);
  }


}

void loop() {}
