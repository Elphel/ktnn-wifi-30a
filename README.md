# ktnn-wifi-30a

Simple custom firmware for KTNNKG wifi 30A module. 

Connects as client to the provided wifi hotspot (must be IEEE802.11 b/g/n (2.4MHz)) with a hardcoded ip address.

## hardware setup

* WIFI module is marked as PSF-B01
* The pinout matches with [this one](https://www.itead.cc/wiki/PSF-B85). **Note the bottom view.**
* **Soldering is required**
* Programming cable - [this one](https://www.amazon.com/gp/product/B07784SHF7/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1) with 3.3V used for VCC

## build and upload
Arduino 1.8.9:
* Board: **Generic ESP8285 Module**
* Upload speed: **921600**
* CPU frequency: **80 MHz**
* Crystal frequency: **26 MHz**
* Flash size: **1M (No SPIFFs)**
* Reset method: **ck**

Short GPIO0 to GND and power on to boot in the programming mode.

Upload the sketch. Check the serial output.

Power off, disconnect the programming cable, connect input wires, power on.

http://ip/on

http://ip/off
