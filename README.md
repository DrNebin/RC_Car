# RC_Car (Devin Namaky)
My ongoing design for a SMALL RC Car 3D printable on a small resin printer driven by Arduino. Currently included here are the first version (Seeeduino) schematics, PCB design (PCB prints are of course optional, but help decrease the footprint), and the INO files. I have also added the STL files for 3D printing. V1 (Seeed) version is complete and I am uploading other versions and improvements as I go.

I have a half dozen V1 (Seeed) extra PCBs on hand. Contact me at www.devinnamaky.com if you want one. I'd charge you $10 plus shipping.

# The main overarching objectives / themes of this project are
1. A small footprint - My benchmark is to be able to print it on an Original Elegoo Mars Resin bed, ideally with few (or no) supports.
2. Simple design - We will try and minimize the number of parts. Do what you want in a fork, but for my base designs I only want the minimum parts needed to have fun.
3. Highly adaptable parts and electronics (Arduino) - My V1 (Seeed) original prototype fit on one single 5x7cm protoboard. V2 (Feather) and subsequent versions can include different steering and drive systems, such as Servo or even Stepper steering, or could incorporate brushless motors or other drive systems.
4. Easy to Build - To make wiring easier and further decrease size, I created the V1 (Seeed) PCB. V2 (Feather) will use the Adafruit Feather system to make the car even easier to build without the need for PCB manufacture, and to further show adaptability. 

# Absolute limitations for RC_Car
+ Car body width will not be less than 55 mm (so as to accept Seeeduino PCB, 5x7 protoboards, Double Feather setups, and Nano breakouts)
+ Car body length will not be less than 110 mm (gives room for steering motor, 130 style drive motor, and enough space to accept all the boards I just mentioned regarding width)
+ All components must individually fit in the dimensions of the original Elegoo Mars Resin Bed when printed flat (max = 68mm x 120mm). Note that the max Z height of the Mars is 150mm, but we want the option to print as flat as possible and will favor that orientation to decrease materials, time required and print failures. (Although, I acknoledge we are actually shooting to print with supports at about a 20 degree angle, which will decrease deformation.)

# RC_Car_V1_Seeed
I learned about DC Motor control, and how to use the nRF modules from HowToMechatronics so check out that site: https://howtomechatronics.com/category/tutorials/

Code for V1 (the Seeeduino version) uses the freely available libraries for nRF24 and SPI.

This project originated when I wanted to hack a small RC Car that broke. You can see it here on Reddit: https://www.reddit.com/r/arduino/comments/jjs9hx/my_kids_rc_car_stopped_working_so_i_hacked_it/

Just about any small microcontroller will do, but using here for V1 (Seeed) a Seeeduino XIAO for the small footprint. 

This car receives from a controller, the design of which I am including the project. There are two joysticks. Joystick data can be processed a variety of ways. In this version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. This is useful if you want to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the power setup you choose.

The TB6612FNG Motor driver occupies PINs 0 thru 5 on the Seeeduino XIAO. You might notice an unexpected pinout order at pins 0 and 1. This is because I realized late in the game that pin 0 on the XIAO is not PWM.
The Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7 on the XIAO.

This version is driving with two standard hobby 130 style DC motors, one for drivetrain and one for steering. The steering DC motor uses rack and pinion for steering in this first version. This allows the most commonly available and cheapest parts to be used.

Power setup is a 7.4V Lipo. The original was 850mAh. It was a bit big and GAGA on the power and battery life so I am now using 300 to 400mAh capacity. This also allows the battery to fit on the lower plate with the step down unit. The battery runs on a toggle switch to a LM2596 to drop everything to 5V. The 5V is wired separately to the Seeeduino and the motor driver. Be aware, I did NOT use the VIN on the Seeed since it was not directly accessible by a pin on the PCB. I also wired the 5V to the standby pin of the motor driver so the motor driver is always in an "ON" state when the switch is turned on. Therefore, do NOT give this setup more than 5V from your step down power source or you will likely kill both the motor driver and the Seeeduino.

The power system is another highly modifiable trait of this car obviously. I am looking with the future version to power the entire system with 4 x AAA rechargeable batteries if I can fit them, which would also give 5 volts without the need for a step converter. The main design change would be fitting a AAA battery holder on the lower body plate, which may be feasible.

The rack and pinion steering system has been difficult to implement for several reasons, but after many prototypes got it to work. It uses two metal rods of 2 mm in diameter (standard hobby rods) and two springs. I used a two inch spring from the local hardware store and cut it in half. I will be taking some measurements for lengths and updating them here. The rack gear slides along both of the rods, and the springs push against the rack gear from each side to re-center it.

The rear gear system is 0.5 module. It uses the standard 8 tooth spur gear that comes with most 130 hobby motors. The middle gear converts from 12 teeth to 26 teeth, and the rear axle gear has 28 teeth. The middle great is supported by a short 2 mm standard hobby pin.

A bill of materials and build video are to come.

# 3D Printing Notes

# RC_Car_CONTROLLER
Uses an Arduino NANO with two analog joysticks (right and left). Sends to the nRF24L01 on the car being controlled. I use this controller right now for all my RC projects. It is highly adaptable. I will upload my PCB and INO files for the controller also. I have some plans to improve the controller in the future. When I get around to them I will update the files.

# RC_Car_V2_Feather
The plan for the version 2 electronics is
+ Adafruit Feather M0 Basic
+ Adafruit DC Motor / Stepper Featherwing
+ ?Header kits ?Featherwing doubler
+ ?Toggle switch vs ?Adafruit push button breakout
+ nRF24L01

DrNebin
