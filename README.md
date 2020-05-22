# SpellBook

![image](https://user-images.githubusercontent.com/38335227/82676829-db814480-9bfb-11ea-97d4-c40af538b854.png)

Tabletop SpellBook for Dungeons and Dragons 5e.

This Arduino project keeps track of spell slots and spell text without having to have a phone out, spell cards, or a stack of paper/book.

# Hardware
* [Adafruit M0 Adalogger](https://www.adafruit.com/product/2796)
* [Adafruit Sharp Memory Display Breakout Board](https://www.adafruit.com/product/3502)
* [Adafruit 8x8 Mini Led Matrix with I2C backpack](https://www.adafruit.com/product/871)
* [2.7" Sharp Memory Display](https://www.digikey.com/product-detail/en/sharp-microelectronics/LS027B7DH01A/425-2908-ND/5054067) replacing the one that comes on the breakout board
* [KY-040 Rotary Encoder](https://www.aliexpress.com/item/33041814942.html?spm=a2g0o.productlist.0.0.12173473cLL3s7&algo_pvid=9b27a9bb-06be-46e5-8421-f77e4601a24b&algo_expid=9b27a9bb-06be-46e5-8421-f77e4601a24b-3&btsid=0ab6f83a15901575144411782e0634&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
* [19mm Push Button](https://www.aliexpress.com/item/4000072167036.html?spm=a2g0s.9042311.0.0.64814c4dvVELMQ)
* MicroSD card

# Software
* Currently, spells data is stored in a JSON file on an SD card and parsed into spell objects in the program.
* The rotary encoder rotation moves through slots and levels (depending on rotation direction)
* When you click the encoder button it will switch to the spell side, where rotation rotates through the spells.

# 3D Printed Shell & 
* 3D printed shell is in two parts. The base still needs some work, I would like to line up the USB to the hole in the back.
* M3 Thumb Screws [amazon link](https://www.amazon.com/gp/product/B06XQBPD4Z/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1)
* 50mm donut semiprecious gemstone pendant for the knob [eBay link](https://www.ebay.com/itm/50mm-Round-Donut-Ring-Gemstone-Pendant-Loose-Beads-1pc-6-Materials-Selectable/390793341631?ssPageName=STRK%3AMEBIDX%3AIT&var=660219589840&_trksid=p2060353.m2749.l2649)
* 18x25mm semiprecious oval cabochons for the upper back panel [amazon link](https://www.amazon.com/gp/product/B07WZXCKFW/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1)
* 
![image](https://user-images.githubusercontent.com/38335227/82676911-01a6e480-9bfc-11ea-9411-a797c4ffbcaf.png)
![image](https://user-images.githubusercontent.com/38335227/82676941-0ec3d380-9bfc-11ea-9f65-5e3f2b848600.png)



# Future Plans
* Add a way to do long rests
* Adding a way to mark spells as prepared prepare spells to shorten the list.
