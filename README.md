# RC_Car (Devin Namaky)
My ongoing design for a SMALL RC Car 3D printable on a small resin printer driven by Arduino based electronics. Currently included here are two versions with all the schematics, PCB design (PCB prints are of course optional, but help decrease the footprint),  INO sketch files, STL files for printing, CAD files, etc. RC_Car_RP (Rack and Pinion) version uses two DC motors and a Seeeduino XIAO. The RC_Car_SS (Servo Steering) version uses one micro servo and one DC motor and an Arduino Nano. The RC_Car_SS Version is really a better design for several reason I won't belabor but if you want to build one of these cars, build RC_Car_SS.

I have a half dozen extra PCBs on hand. Contact me at https://www.devinnamaky.com if you want one. I'd charge you $10 plus shipping.

# The main overarching objectives / themes of this project are
1. A small footprint - My benchmark is to be able to print it on an Original Elegoo Mars Resin 3D printer (Even the tires!).
2. Simple design - I have tried to minimize the number of parts.
3. Highly adaptable parts and electronics (Arduino-based) - My RC_Car_RP original prototype fit on one single 5x7cm protoboard and uses a Seeeduino XIAO. RC_Car_SS includes Servo steering, a new power setup with a momentary push button, and uses an Arduino Nano since more people have those on hand.
4. Easy to Build - To make wiring easier and further decrease size, I created PCB files and I've uploaded the Gerber files if you want to order your own PCBs, which I do recommend. 

# essential_Requirements for RC_Car
+ Car body width will not be less than 55 mm (so as to accept Seeeduino PCB, 5x7 protoboards, Double Feather setups, and Nano breakouts, etc.)
+ Car body length will not be less than 110 mm (gives room for steering motors, 130 style drive motor, and enough space to accept all the boards I just mentioned regarding width)
+ All components must be able to print on the original Elegoo Mars Resin Bed (68 mm x 120 mm). Note that the max Z height of the Mars is 150 mm. (Although, I acknowledge we are actually shooting to print with supports at about a 20 degree angle, which will decrease deformation.)
+ Must be rechargeable
+ Must be wireless (so I have also designed controllers)
+ It's a car

# RC_Car_RP (Rack and Pinion)
Don't build this version. I recommend you build the RC_Car_SS version.

Code for RC_Car uses the freely available libraries for nRF24 and SPI.

This project originated when I wanted to hack one of my kids small RC Cars that broke. You can see it here on Reddit: https://www.reddit.com/r/arduino/comments/jjs9hx/my_kids_rc_car_stopped_working_so_i_hacked_it/

Just about any small microcontroller will do, but using here for RC_Car_RP a Seeeduino XIAO for the small footprint. 

The TB6612FNG Motor driver occupies PINs 0 thru 5 on the Seeeduino XIAO. You might notice an unexpected pinout order at pins 0 and 1. This is because I realized late in the game that pin 0 on the XIAO is not PWM.
The Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7 on the XIAO.

This version is driving with two standard hobby 130 style DC motors, one for drivetrain and one for steering. The steering DC motor uses rack and pinion for steering in this first version. This allows the most commonly available and cheapest parts to be used.

Power setup is a 7.4V Lipo. The original was 850 mAh. It was a bit big and GAGA on the power and battery life so I am now using 300 to 400mAh capacity. This also allows the battery to fit on the lower plate with the step down unit. The battery runs on a toggle switch to a LM2596 to drop everything to 5V. The 5V is wired separately to the Seeeduino and the motor driver. Be aware, I did NOT use the VIN on the Seeed since it was not directly accessible by a pin on the PCB. I also wired the 5V to the standby pin of the motor driver so the motor driver is always in an "ON" state when the switch is turned on. Therefore, do NOT give this setup more than 5V from your step down power source or you will likely kill both the motor driver and the Seeeduino.

The rack and pinion steering system has been difficult to implement for several reasons, but after many prototypes I got it to work. It uses two metal rods of 2 mm in diameter (standard hobby rods) and two springs. I used a two inch spring from the local hardware store and cut it in half. I will be taking some measurements for lengths and updating them here. The rack gear slides along both of the rods, and the springs push against the rack gear from each side to re-center it. On my wish list was to develop a system that uses a torsion spring instead.

The rear gear system is 0.5 module. It uses the standard 8 tooth spur gear that comes with most 130 hobby motors. The middle gear converts from 12 teeth to 26 teeth, and the rear axle gear has 28 teeth. The middle great is supported by a short 2 mm standard hobby pin.

A bill of materials is posted.

# RC_Car_SS (Servo Steering)
This version is much improved and the one I recommend to build. It uses an Arduino Nano, an Adafruit momentary power switch, and an MG90s servo for the steering. Check out the Github folders for all the sketch files, schematics, fritzing file, Gerber files, chitubox files, STL files... everything really. I don't think Github will let me upload the Fusion 360 files but I'll give it a try. No Bill of Materials or instructions yet. Maybe I'll get to that one day.

# 3D Printing Notes
I used the original Elegoo Mars resin printer to print the car. Contrary to popular belief, you can absolutely print robust car parts, even on a resin printer. For many of the parts I used standard resin, especially if they were non-critical like the spoiler, or if I intended for them to be weaker anyway, like the bumper. For parts where strength is needed and for the gears there were two approaches I took that worked. One option is to use ABS-like resin, which I found acceptable. The other is to mix flexible or strength resins to the standard resin. I found 30% of Sirayatech Tenacious mixed with 70% of Standard Shine Tough Grey worked well and I favored that approach. For the standard resins, ABS-like and even the blend you can use pretty normal exposure and support settings if you limit the Tenacious to 30%.

Lastly, the TIRES! At first I tried standard resin and printed the wheel and tire together. As you can imagine there was no grip. Then I tried a "flexible" resin and used 100% Sirayatech Tenacious. Unfortunately, this was far from actually being flexible and still was very smooth and plastic like and did not provide any real traction either. Then I found Wanhao Rubber-like resin, and best of all it came in black. I would disagree that the resin is "rubber-like" in truth regarding flexibility. It's still actually pretty inflexible unless you are printing something thin. But it did provide enough flex to be able to print he tire separately and slip it over the wheel. The best part is that it did provide a rubber-like texture and feel and so it does provide grip and in the end worked well. 

The Wanhao took me four tries to successfully print as I had no real guidance. I found that I had to use 300% of normal exposure for the bottom layers, and 400% of normal exposure time for the remaining layers. My lift distance was 7 mm, bottom lift speed was 25 mm/min, lifting speed was 40 mm/min, and retract speed was 40 mm/min. The rubber-like resin really needs robust support. I had to double the diameter of my medium supports and the amount of contact depth, and I had to add large supports throughout the model. I think with good support I could probably back off on the exposure times a bit. The rubber-like prints take a very long time.

# RC_Car_CONTROLLER
Version 1 of the controller uses an Arduino NANO with two analog joysticks (right and left). Sends to the nRF24L01 on the car being controlled. You can use this controller for any RC project. It is highly adaptable. 

There are two joysticks. Joystick data can be processed a variety of ways. In this version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. There are three different speed settings it toggles through. This is useful if you want to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the power setup you choose.

Version 2 of the controller has many improvements and is the version I recommend you build. Version 2 is smaller, has a much larger broadcast range, uses a Lipo battery and even recharges it. It uses an Adafruit Itsy Bitsy 32u4 (3 volt version) with a Lipoly backpak. This particular board ends up being cool because it avoids the need for a step down unit and drives enough current to power the longer range nRF24L01+. It uses two joysticks again, but this time they are specifically the COM-09032 and directly soldered / connected to the PCB (no wires). You can get them from Sparkfun. Don't buy what looks like them on eBay. They will be the wrong size if you do.

Last note on Version 2 is that the Fritzing object has a bug that has a square copper connection for the positive lead on the capacitor, and a round one for the negative. The silkscreen includes a small negative sign that warns you of this. You can omit the capacitor if you have to.

DrNebin
