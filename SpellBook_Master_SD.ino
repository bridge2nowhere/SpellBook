#include <CircularBuffer.h>
#include <ArduinoJson.h>
#include "Spell.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <RotaryEncoder.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_SharpMem.h>
#include "custFont.h"
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <SPI.h>
#include <SD.h>
#include <StreamUtils.h>


#define ENCODER_BUTT 9
#define ENCODER_1 6
#define ENCODER_2 5

#define SHARP_SCK  13
#define SHARP_MOSI 12
#define SHARP_SS   11

#define BLACK 0
#define WHITE 1



const uint8_t MAX_TOME_LENGTH = 120;
CircularBuffer<Spell*, MAX_TOME_LENGTH> tome;

///////////////////////////////////////////////////////////////////////////
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
RotaryEncoder encoder(ENCODER_1, ENCODER_2);
Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);

///////////////////////////////////////////////////////////////////////////
uint8_t activeSlot = 0;
uint8_t activeSpell = 0;
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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  
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
  //Serial.println(tome[0]->range);
  //check encoder
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos){
    if(knob == knobMode::Slots) slotEncoderUpdate(pos,newPos);
    else if(knob == knobMode::Spells) spellEncoderUpdate(pos,newPos);
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

 
  
  File spellJSON = SD.open("TOME2.TXT");

  if (spellJSON) {
    //deserializeJson(doc, spellJSON);
    ReadLoggingStream loggingStream(spellJSON, Serial);
    ReadBufferingStream bufferingStream(spellJSON, 64);
    deserializeJson(doc, loggingStream);
    
  }
  else {
    Serial.println("error opening txt");
  }

  
  for (int i = 0; i < doc.size(); i++) {
    JsonObject root = doc[i];   
    Spell* newSpell = new Spell(root["name"], root["casting_time"], root["components"], root["duration"], root["level"], root["range"], root["ritual"], root["school"], root["description"]);
    tome.push(newSpell);
    Serial.println(i);
    Serial.println(newSpell->spellName);
  }

  //free(pBuffer);
  Serial.println(tome[1]->spellName);
  
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


void spellEncoderUpdate(int pos, int newPos) {
  if (pos > newPos) {
    activeSpell++;
    if (activeSpell > tome.size()) activeSpell = 0; 
  }
  else if (pos < newPos) {
    activeSpell--;
    if (activeSpell < 0) activeSpell = tome.size()-1;
  }
  draw_spells();
}
//////////////////////////////////////////////////
void draw_spells(){
  display.clearDisplay();
  display.setRotation(2);
   
  
  display.setTextColor(BLACK);
  display.setFont(&FreeSansBold12pt7b);
  //display.setTextSize(2);
  display.setCursor(0,18);
  display.print(tome[activeSpell]->level);
  display.print("  -  ");
  display.print(tome[activeSpell]->spellName);
  if(tome[activeSpell]->ritual) display.println("     RITUAL");
  else display.println("");

  display.setFont(&FreeSansBold9pt7b);
  display.setTextWrap(false);
  //display.setTextColor(WHITE,BLACK);
  
  //display.print("Level: ");
  //display.print(tome[activeSpell]->level);
  
  display.setCursor(0,36);
  display.print("Cast time: ");
  display.print(tome[activeSpell]->casting_time);
  
  display.setCursor(200,36);
  display.print("Range: ");
  display.println(tome[activeSpell]->range);
  
  display.setCursor(0,52);
  display.print("Components:");
  display.print(tome[activeSpell]->components);

  display.setCursor(200,52);
  display.print("Duration:");
  display.println(tome[activeSpell]->duration);

  
  display.setTextWrap(false);

  display.setTextSize(1);
  display.setFont(&URW_Gothic_L_Book_14);
  
  display.setTextColor(BLACK);
  display.println("You point at one creature you can see within range, ");
  display.println("and the sound of a dolorous");
  display.println("bell fills the air around it"); //28x
  display.println("for a moment. The target");
  display.println("must succeed on a Wisdom");
  display.println("saving throw or take 1d8 target is");
  display.println("missing any of its hit points,"); 
  display.println("it instead takes 1d12 necrotic");
  display.println("damage. necrotic damage. If theThe spell’s damage increases by one die when you reach 5th level (2d8 or 2d12), 11th level (3d8 or 3d12), and 17th level (4d8 or 4d12).");
  display.refresh();
  delay(500);
}
