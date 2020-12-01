# RC_Car (Devin Namaky)
My ongoing design for a SMALL RC Car 3D printable on a small resin printer driven by Arduino. Currently included here are the first model schematics, PCB design (PCB prints are of course optional, but help decrease the footprint), and the INO files. I have also added the STL files for 3D printing. RC_Car_RP (Rack and Pinion) version is complete and I am uploading other versions and improvements as I go.

I have a half dozen RC_Car_RP extra PCBs on hand. Contact me at www.devinnamaky.com if you want one. I'd charge you $10 plus shipping.

# The main overarching objectives / themes of this project are
1. A small footprint - My benchmark is to be able to print it on an Original Elegoo Mars Resin bed, ideally with few (or no) supports.
2. Simple design - We will try and minimize the number of parts. Do what you want in a fork, but for my base designs I only want the minimum parts needed to have fun.
3. Highly adaptable parts and electronics (Arduino) - My RC_Car_RP original prototype fit on one single 5x7cm protoboard. V2 (Nano) and subsequent versions can include different steering and drive systems, such as Servo or even Stepper steering, or could incorporate brushless motors or other drive systems.
4. Easy to Build - To make wiring easier and further decrease size, I created the RC_Car_RP PCB. Model 2, RC_Car_SS, will use an Arduino Nano system and use Servo Steering. 

# Absolute limitations for RC_Car
+ Car body width will not be less than 55 mm (so as to accept Seeeduino PCB, 5x7 protoboards, Double Feather setups, and Nano breakouts)
+ Car body length will not be less than 110 mm (gives room for steering motor, 130 style drive motor, and enough space to accept all the boards I just mentioned regarding width)
+ All components must individually fit in the dimensions of the original Elegoo Mars Resin Bed when printed flat (max = 68 mm x 120 mm). Note that the max Z height of the Mars is 150 mm, but we want the option to print as flat as possible and will favor that orientation to decrease materials, time required and print failures. (Although, I acknowledge we are actually shooting to print with supports at about a 20 degree angle, which will decrease deformation.)

# RC_Car_RP (Rack and Pinion)
Code for RC_Car_RP uses the freely available libraries for nRF24 and SPI.

This project originated when I wanted to hack a small RC Car that broke. You can see it here on Reddit: https://www.reddit.com/r/arduino/comments/jjs9hx/my_kids_rc_car_stopped_working_so_i_hacked_it/

Just about any small microcontroller will do, but using here for RC_Car_RP a Seeeduino XIAO for the small footprint. 

This car receives from a controller, the design of which I am including in the project. There are two joysticks. Joystick data can be processed a variety of ways. In this version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. There are three different speed settings it toggles through. This is useful if you want to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the power setup you choose.

The TB6612FNG Motor driver occupies PINs 0 thru 5 on the Seeeduino XIAO. You might notice an unexpected pinout order at pins 0 and 1. This is because I realized late in the game that pin 0 on the XIAO is not PWM.
The Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7 on the XIAO.

This version is driving with two standard hobby 130 style DC motors, one for drivetrain and one for steering. The steering DC motor uses rack and pinion for steering in this first version. This allows the most commonly available and cheapest parts to be used.

Power setup is a 7.4V Lipo. The original was 850 mAh. It was a bit big and GAGA on the power and battery life so I am now using 300 to 400mAh capacity. This also allows the battery to fit on the lower plate with the step down unit. The battery runs on a toggle switch to a LM2596 to drop everything to 5V. The 5V is wired separately to the Seeeduino and the motor driver. Be aware, I did NOT use the VIN on the Seeed since it was not directly accessible by a pin on the PCB. I also wired the 5V to the standby pin of the motor driver so the motor driver is always in an "ON" state when the switch is turned on. Therefore, do NOT give this setup more than 5V from your step down power source or you will likely kill both the motor driver and the Seeeduino.

The power system is another highly modifiable trait of this car obviously. I am looking with future models to power the entire system with AAA rechargeable batteries if I can fit them, which would also give 5 volts without the need for a step converter. The main design change would be fitting a AAA battery holder on the lower body plate, which may be feasible.

The rack and pinion steering system has been difficult to implement for several reasons, but after many prototypes I got it to work. It uses two metal rods of 2 mm in diameter (standard hobby rods) and two springs. I used a two inch spring from the local hardware store and cut it in half. I will be taking some measurements for lengths and updating them here. The rack gear slides along both of the rods, and the springs push against the rack gear from each side to re-center it. On my wish list is to develop a system that uses a torsion spring instead.

The rear gear system is 0.5 module. It uses the standard 8 tooth spur gear that comes with most 130 hobby motors. The middle gear converts from 12 teeth to 26 teeth, and the rear axle gear has 28 teeth. The middle great is supported by a short 2 mm standard hobby pin.

A bill of materials is posted, and a build video is to come.

# 3D Printing Notes
I used the original Elegoo Mars resin printer to print the car. Contrary to popular belief, you can absolutely print robust car parts, even on a resin printer. For many of the parts I used standard resin, especially if they were non-critical like the spoiler, or if I intended for them to be weaker anyway, like the bumper. For parts where strength is needed and for the gears there were two approaches I took that worked. One option is to use ABS-like resin, which I found acceptable. The other is to mix flexible or strength resins to the standard resin. I found 30% of Sirayatech Tenacious mixed with 70% of Standard Shine Tough Grey worked well and I favored that approach. For the standard resins, ABS-like and even the blend you can use pretty normal exposure and support settings if you limit the Tenacious to 30%.

Lastly, the TIRES! At first I tried standard resin and printed the wheel and tire together. As you can imagine there was no grip. Then I tried a "flexible" resin and used 100% Sirayatech Tenacious. Unfortunately, this was far from actually being flexible and still was very smooth and plastic like and did not provide any real traction either. Then I found Wanhao Rubber-like resin, and best of all it came in black. I would disagree that the resin is "rubber-like" in truth regarding flexibility. It's still actually pretty inflexible unless you are printing something thin. But it did provide enough flex to be able to print he tire separately and slip it over the wheel. The best part is that it did provide a rubber-like texture and feel and so it does provide grip and in the end worked well. 

The Wanhao took me four tries to successfully print as I had no real guidance. I found that I had to use 300% of normal exposure for the bottom layers, and 400% of normal exposure time for the remaining layers. My lift distance was 7 mm, bottom lift speed was 25 mm/min, lifting speed was 40 mm/min, and retract speed was 40 mm/min. The rubber-like resin really needs robust support. I had to double the diameter of my medium supports and the amount of contact depth, and I had to add large supports throughout the model. I think with good support I could probably back off on the exposure times a bit. The rubber-like prints take a very long time.

# RC_Car_CONTROLLER
Uses an Arduino NANO with two analog joysticks (right and left). Sends to the nRF24L01 on the car being controlled. I use this controller right now for all my RC projects. It is highly adaptable. I will upload my PCB and INO files for the controller also. I have some plans to improve the controller in the future. When I get around to them I will update the files.

# RC_Car_SS (Servo Steering)
The plan for the version 2 electronics is
+ Arduino Nano
+ Servo Steering with MG90s
+ Adafruit momentary push button breakout
+ nRF24L01
+ AAA rechargeable batteries hopefully

DrNebin
