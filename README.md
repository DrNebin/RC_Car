# RC_Car
My ongoing design for a SMALL RC Car 3D printable on a small resin printer driven by Arduino. Currently included here are the schematics, PCB design (PCB prints are of course optional, but help decrease the footprint), and the INO files. As I get together a 3D print design I will add that also.

Not really ready for prime time, but uploading as I go. Gonna optimize the code more and allow controller joysticks to adjust power of the motors.

I learned to use the nRF modules from HowToMechatronics so check out that site. There are some good tutorials there.

Code uses the freely available libraries for nRF24 and SPI.

I used what I have so far to hack a small RC Car. You can see it here on Reddit: https://www.reddit.com/r/arduino/comments/jjs9hx/my_kids_rc_car_stopped_working_so_i_hacked_it/

Car README:
// Arduino RC Car developed and programmed by Devin Namaky for his children
// Any microcontroller will do, but using here a Seeeduino XIAO for a small footprint (we want a small car to print on a resin printer)
// Two generic joysticks for a remote. This version is wireless. There is a separate INO file for the controller code using a NANO.
// Joysticks can be programmed a variety of ways. This version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. This is useful if you wnat to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the battery setup you choose.
// Motor driver occupying PINs 0 thru 5 on a Seeeduino XIAO as the below variables indicate.
// Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7
// This version is driving with two DC motors and no servo. The steering DC motor has something akin to rack and pinion for steering for now.

CONTROLLER README:
// Uses an Arduino NANO with two analog joysticks (right and left). Sends to nRF24L01 on the car being controlled


DrNebin
