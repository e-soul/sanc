# Simple Accurate Network Clock (SANC)
This is a small and easy to assemble DIY device. It consists of only 4 elements.

- [Feather M0](https://www.adafruit.com/product/3010) microcontroller
- [FeatherWing OLED](https://www.adafruit.com/product/2900) monochrome display
- [Lithium Ion Polymer Battery](https://www.adafruit.com/product/2750) 3.7v 350mAh
- [Male](https://www.adafruit.com/product/3002) and [Female](https://www.adafruit.com/product/2940) short headers

#### How to assemble

###### 1. Solder the female headers onto the controller and the male headers onto the display 
![Components](https://github.com/e-soul/sanc/raw/master/img/1801380425-IMG_2638.JPG)
###### 2. Stack the two boards and attach the battery 
![Assembled](https://github.com/e-soul/sanc/raw/master/img/3162864886-IMG_2642.JPG)
###### 3. Launch Arduino IDE (or your favourite AVR tool) and install the code from this repo. Don't forget to put your SSID, passphrase and time zone in `main.ino`
###### 4. Enjoy your new clock!

#### Power
The code is optimised to last at least 24 hours on battery. To recharge the battery just connect the controller to USB power, it will automatically recharge the battery for about 1 hour.

#### Details
For more details on how it works study the code.