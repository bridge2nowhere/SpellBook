# SpellBook

Tabletop SpellBook for Dungeons and Dragons 5e.

This Arduino project keeps track of spell slots and spell text without having to have a phone out, spell cards, or a stack of paper/book.

# Hardware
* Adafruit M0 Adalogger
* Adafruit Sharp Memory Display Breakout Board
* Adafruit 8x8 Mini Led Matrix
* MicroSD card for JSON spell file
* 2.7" Sharp Memory Display (replacing the one that comes on the breakout board)
* KY-040 Rotary Encoder
* 19mm Push Button

# Software
* Currently, spells data is stored in a JSON file on an SD card and parsed into spell objects in the program.
* The rotary encoder rotation moves through slots and levels (depending on rotation direction)
* When you click the encoder button it will switch to the spell side, where rotation rotates through the spells.

# 3D Printed Shell & 
* I used a 50mm donut semiprecious gemstone pendant for the knob
* I used 18x25mm semiprecious oval cabochons for the upper back panel

# Future Plans
* Add a way to do long rests
* Adding a way to mark spells as prepared prepare spells to shorten the list.
