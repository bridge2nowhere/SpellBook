#include <CircularBuffer.h>
#include <ArduinoJson.h>
#include "Spell.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <RotaryEncoder.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_SharpMem.h>
#include "custFont.h"

#define ENCODER_BUTT 2
#define ENCODER_1 14
#define ENCODER_2 16

#define SHARP_SCK  15
#define SHARP_MOSI 13
#define SHARP_SS   12

#define BLACK 0
#define WHITE 1

const uint8_t TOME_LENGTH = 5;
CircularBuffer<Spell*, TOME_LENGTH> tome;

///////////////////////////////////////////////////////////////////////////
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
RotaryEncoder encoder(ENCODER_1, ENCODER_2);
Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 144, 168);

///////////////////////////////////////////////////////////////////////////
uint8_t activeSlot = 0;
const uint8_t SPELL_LEVELS = 4;
uint8_t slotsMax[SPELL_LEVELS] = {4,3,3,3};
uint8_t slotsLeft[SPELL_LEVELS] = {4,3,3,3};

//////////////////////////////////////////////////////////////////////////
enum class knobMode : uint8_t
{
  Spells, Slots
};
knobMode knob = knobMode::Slots;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(ENCODER_BUTT, INPUT_PULLUP);
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(0);
  matrix.setBrightness(5);
  matrix.clear();
  display.begin();
  display.clearDisplay();


  parseSpellJson();
  draw_slots(true);
  draw_spells();
}

void loop() {
  Serial.println(tome[0]->range);
  //check encoder
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos){
    if(knob == knobMode::Slots) slotEncoderUpdate(pos,newPos);
    else if(knob == knobMode::Spells) Serial.println("lightning bolt");
    Serial.println(newPos);  
    pos=newPos;
  }
  
  if(knob == knobMode::Slots) draw_slots(true);
  else if(knob == knobMode::Spells) draw_slots(false);


  if (digitalRead(ENCODER_BUTT) == LOW) {
    if(knob == knobMode::Slots) knob = knobMode::Spells;
    else if(knob == knobMode::Spells) knob = knobMode::Slots;
    delay(300);
  }  
}

//////////////////////////////////////////////
void parseSpellJson() {
  const size_t capacity = JSON_ARRAY_SIZE(6) + 6 * JSON_OBJECT_SIZE(9) + 2150;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, F("[{\"name\":\"Mending\",\"casting_time\":\"1 minute\",\"components\":\"V,S,M\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"touch\",\"ritual\":false,\"school\":\"conjuration\",\"description\":\"This spell repairs a single break or tear in an object. As long as the break or tear is no larger than 1 foot in any dimension. This spell can physically repair a magic item or construct, but can't restore magic.\"},{\"name\":\"Sacred Flame\",\"casting_time\":\"1 action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"evocation\",\"description\":\"The target must succeed on a Dexterity saving throw or take 1d8 radiant damage. The target gains no benefit from cover for this saving throw. At higher level 5th level (2d8), 11th level (3d8), and 17th level (4d8).\"},{\"name\":\"Spare the Dying\",\"casting_time\":\"Bonus Action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"Necromancy\",\"description\":\"You touch a living creature that has 0 hit points. The creature becomes stable. This spell has no effect on undead or constructs.\"},{\"name\":\"Thaumaturgy\",\"casting_time\":\"1 Action\",\"components\":\"V\",\"duration\":\"<1min\",\"level\":0,\"range\":\"30 feet\",\"ritual\":false,\"school\":\"Transmutation\",\"description\":\"Create one of effects within range:Voice booms 3x|Change Flames flicker, brighten, dim, or change color|Harmless tremors|Sound from a point|Door or window to fly open or slam shut|Alter the appearance of your eyes.\"},{\"name\":\"Toll the Dead\",\"casting_time\":\"1 Action\",\"components\":\"V,S\",\"duration\":\"Instantaneous\",\"level\":0,\"range\":\"60 feet\",\"ritual\":false,\"school\":\"Necromancy\",\"description\":\"One creature you can see must succeed on a Wisdom saving throw or take 1d8 necrotic damage, or 1d12 necrotic damage if HP missing. At 5th level (2d8 or 2d12), 11th level (3d8 or 3d12), and 17th level (4d8 or 4d12).\"}]"));

  for (int i = 0; i < TOME_LENGTH; i++) {
    JsonObject root = doc[i];   
    Spell* newSpell = new Spell(root["name"], root["casting_time"], root["components"], root["duration"], root["level"], root["range"], root["ritual"], root["school"], root["description"]);
    tome.push(newSpell);
  }
}
////////////////////////////////////////////
void draw_slots(bool showCursor) {
  matrix.clear();
  for (uint8_t lvl = 0; lvl < SPELL_LEVELS; lvl++) {
     for (uint8_t left = 0; left < slotsLeft[lvl]; left++) {
       matrix.drawPixel(2+left, lvl, LED_ON); 
     }
  }
  if (showCursor) matrix.drawPixel(0,activeSlot, LED_ON);
  matrix.writeDisplay();
}


void slotEncoderUpdate(int pos, int newPos) {
  if (pos > newPos) {
    activeSlot++;
    if (activeSlot >= SPELL_LEVELS) activeSlot = 0; 
  }
  else if (pos < newPos) {
    slotsLeft[activeSlot]--;
    if (slotsLeft[activeSlot] > 10) slotsLeft[activeSlot] = slotsMax[activeSlot];
  }
}
//////////////////////////////////////////////////
void draw_spells() {
  display.setRotation(3);
  display.setCursor(0,0);
  //display.clearDisplay();
  display.setTextColor(BLACK);
  
  display.setTextSize(2);
  display.println("Toll the Dead");

  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.println("Level: Cantrip              ");
  display.println("Casting time: 1 Action      ");
  display.println("Range: 60 feet              ");
  display.println("Components: V, S            ");
  display.println("Duration: Instantaneous     ");
 
  display.setFont(&URW_Gothic_L_Book_10);
  
  display.setTextColor(BLACK);
  display.println("You point at one creature\nyou can see within range, ");
  display.println("and the sound of a dolorous");
  display.println("bell fills the air around it"); //28x
  display.println("for a moment. The target");
  display.println("must succeed on a Wisdom");
  display.println("saving throw or take 1d8 target is");
  display.println("missing any of its hit points,"); 
  display.println("it instead takes 1d12 necrotic");
  display.println("damage. necrotic damage. If theThe spell’s damage increases by one die when you reach 5th level (2d8 or 2d12), 11th level (3d8 or 3d12), and 17th level (4d8 or 4d12).");
  display.refresh();
}
