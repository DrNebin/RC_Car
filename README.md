# RC_Car (Devin Namaky)
My ongoing design for a SMALL RC Car 3D printable on a small resin printer driven by Arduino. Currently included here are the first version (Seeeduino) schematics, PCB design (PCB prints are of course optional, but help decrease the footprint), and the INO files. As I get together a 3D print design I will add that also. Not really ready for prime time, but uploading as I go.

I have a half dozen V1 (Seeed) extra PCBs on hand. Contact me if you want one. I'd charge you $10 plus shipping.

# The main overarching objectives / themes of this project are
1. A small footprint - Our benchmark is to be able to print it on an Elegoo Mars Resin bed, ideally with few (or no) supports.
2. Simple design - We will try and minimize the number of parts. Do what you want in a fork, but for my base designs I only want the minimum parts needed to have fun.
3. Highly adaptable parts and electronics (Arduino) - My V1 (Seeed) original prototype fit on one single 5x7cm protoboard. V2 (Feather) versions can include different steering and drive systems, such as Servo or even Stepper steering, or could incorporate brushless motors or other drive systems.
4. Easy to Build - To make wiring easier and further decrease size, I created the V1 (Seeed) PCB. V2 (Feather) will use the Adafruit Feather system to make the car even easier to build without the need for PCB manufacture, and to further show adaptability. 

# Absolute limitations for RC_Car
+ Car body width will not be less than 55 mm (so as to accept Seeeduino PCB, 5x7 protoboards, Double Feather setups, and Nano breakouts)
+ Car body length will not be less than 110 mm (gives room for steering motor, 130 style drive motor, and enought space to accept all the boards I just mentioned regarding width)
+ All components must fit in the dimensions of an Elegoo Mars Resin Bed when printed flat (max = 68mm x 120mm). Note that the Z height of the Mars is 150mm, but we want to print flat and will favor that orientation to decrease materials, time required and print failures.

# RC_Car_V1_Seeed
I learned about DC Motor control, and how to use the nRF modules from HowToMechatronics so check out that site: https://howtomechatronics.com/category/tutorials/
I am planning to modify and shrink down some components from Carduino V2, particularly for the front and wheel axle printing: https://www.thingiverse.com/thing:4233353

Code for V1 (the Seeeduino version) uses the freely available libraries for nRF24 and SPI.

This project originated when I wanted to hack a small RC Car that broke. You can see it here on Reddit: https://www.reddit.com/r/arduino/comments/jjs9hx/my_kids_rc_car_stopped_working_so_i_hacked_it/

Just about any small microcontroller will do, but using here for V1 (Seeed) a Seeeduino XIAO for the small footprint. 

This car receives from a controller, the design of which I am including the project. There are two joysticks. Joystick data can be processed a variety of ways. In this version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. This is useful if you want to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the battery setup you choose.

The TB6612FNG Motor driver occupies PINs 0 thru 5 on the Seeeduino XIAO. You might notice an unexpected pinout order at pins 0 and 1. This is because I realized late in the game that pin 0 on the XIAO is not PWM.
The Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7 on the XIAO.

This version is driving with two DC motors, one for drivetrain and one for steering. The steering DC motor uses rack and pinion for steering.

Power setup is a 7.4V Lipo. The original was 850mAh. It was a bit big and GAGA on the power and battery life so planning on using around 400mAh capacity. The battery runs on a toggle switch to a LM2596 to drop everything to 5V. The 5V is wired separately to the Seeeduino and the motor driver. Be aware, I did NOT use the VIN on the Seeed since it was not directly accessible by a pin. I also wired the 5V to the standy pin of the motor driver so the motor driver is always in an "ON" state when the switch is turned on. Therefore, do NOT give this setup more than 5V from your step down power source or you will likely kill both the motor driver and the Seeeduino.

# RC_Car_CONTROLLER
Uses an Arduino NANO with two analog joysticks (right and left). Sends to nRF24L01 on the car being controlled. I use this controller right now for all my RC projects. It is highly adaptable. I will upload my PCB and INO files for the controller also.

# RC_Car_V2_Feather
The plan for version 2 electronics when we get there is
+ Adafruit Feather M0 Basic
+ Adafruit DC Motor / Stepper Featherwing
+ ?Header kits ?Featherwing doubler
+ ?Toggle switch vs ?Adafruit push button breakout
+ nRF24L01
Total electronics Cost $40-60

If you are interested in helping let me know.

DrNebin
