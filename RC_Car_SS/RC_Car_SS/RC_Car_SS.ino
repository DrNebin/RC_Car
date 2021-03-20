// Arduino RC Car (RC_Car_SS) developed and programmed by Devin Namaky 2020 for his children
// This version uses an Arduino Nano on the car.
// Two generic joysticks for a remote. This version is wireless. There are separate INO and other files for two different versions of the controller on the Github. They both interface interchangeably with the car so pick whichever controller version suits you.
// Joysticks can be programmed a variety of ways. This version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed (cycles L, M, H). This is useful if you want to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the battery setup you choose.
// Motor driver occupying PINs D6 thru D8 on the Nano as the below variables indicate.
// Wireless nRF24L01 SPI is on D11 thru D13, and CE / CSN are pins 10 and 9
// This version is driving with one DC motor for the drivetrain on a TB6612FNG, and one servo motor for steering on pin D5.
// All the schematics, code, fritzing, CAD and STL files are on my Github at https://github.com/DrNebin/RC_Car ; Also check out my blog for videos etc http://devinnamaky.com

//--------------DEFINITIONS & LIBRARIES--------------------//
#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(10, 9); // CE, CSN
const byte address[6] = "00001";

byte servoPin = 5;
byte PWMA = 6;
byte AIN1 = 8;
byte AIN2 = 7;
byte motorSpeedA = 0;
byte motorSpeedAMAX = 255; // Adjust for maximum power delivered forward to motor A (0 to 255)
const byte motorSpeedAReverse = 185; // Adjust for maximum power delivered reverse to motor A (0 to 255)
const byte servoNeutral = 65; // Adjust for neutral alignment of steering (0 to 180)
byte servoPosition; // stores the intended angle of the steering to be sent to servo
byte steerLeftAngleMAX = servoNeutral - 37; // enter value for max left turn angle of servo (0 to 90)
byte steerRightAngleMAX = servoNeutral + 37; // enter value for max right turn angle of servo (90 to 180)
unsigned long lastSpeedButtonReadTime = 0;
unsigned long lastControllerReadTime = 0;
unsigned long currentMillis = 0;

Servo steeringServo; // create the servo object

// -------construct NRF data package-----------//
struct Data_Package { // Create a single data package to be received over wireless
    byte joystick1xAxisBytes;
    byte joystick1yAxisBytes;
    byte joystick1Button;
    byte joystick2xAxisBytes;
    byte joystick2yAxisBytes;
    byte joystick2Button;
  };
Data_Package data; // Creates a variable "data" with the above structure of bytes
//--------------------------------------------//

//-----------------SETUP-------------------------------//
void setup() {
  servoPosition = servoNeutral; //startup with neutral alignment
  steeringServo.attach(servoPin);
  steeringServo.write(servoPosition);
  
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  Serial.begin(9600);  //NRF SETUP, OPEN PIPE, START LISTENING
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
    // Reset data on startup to default values
  resetData();
}
//------------------------------------------------------//


//---------------------MAIN LOOP---------------------//
void loop() {
    //read controller data
    readController();
    //set motors
    setMotorSpeeds();
        // check the time
        currentMillis = millis();
        // check speed mode select button, including a 500 ms time period debounce
        // if receiving button data and the button is pressed, and the necessary time has passed
    if ((radio.available()) && (data.joystick2Button == LOW) && ((currentMillis - lastSpeedButtonReadTime) > 500)) {
        // then change the max speed
        if (motorSpeedAMAX == 120) {
            motorSpeedAMAX = 180;} else if (motorSpeedAMAX == 180) {
                motorSpeedAMAX = 255;} else if (motorSpeedAMAX == 255) {
                    motorSpeedAMAX = 120;
            }
        lastSpeedButtonReadTime = millis();
       //  Serial.println(motorSpeedAMAX);  // Serial printing generally commented out to save RAM unless debugging
    }
}
//------------------------------------------------------//

//---------------OTHER COMMAND DEFINITIONS----------------------------//
void resetData() { // Set the signals from the joysticks to neutral initially so the car doesn't move yet
    data.joystick1xAxisBytes = 127;
    data.joystick1yAxisBytes = 127;
    data.joystick2xAxisBytes = 127;
    data.joystick2yAxisBytes = 127;
    data.joystick2Button = 1;
    //     Serial.println("reset data"); 
  }

void readController() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
 /*    Serial.println("joystick1-Y: ");
     Serial.print(data.joystick1yAxisBytes);
     Serial.println("joystick2-Y: ");
     Serial.print(data.joystick2yAxisBytes);
      Serial.println("joystick1-X: ");
      Serial.print(data.joystick1xAxisBytes);
      Serial.println("joystick2-X: ");
      Serial.print(data.joystick2xAxisBytes);
      Serial.println("joystick2-Button: ");
      Serial.print(data.joystick2Button); */
      // Record the last time the controller was successfully read
      lastControllerReadTime = millis();
  }
    // Check the current time
  currentMillis = millis();
    // If the last successful control read is more than 1 second ago, reset the data to not lose control of the car
  if ((currentMillis - lastControllerReadTime) > 1000) {
    resetData();
    }
}

void setMotorSpeeds() {
        // Left joystick Y-axis used for forward and backward control
    if (data.joystick1yAxisBytes <= 123) {
      // Set Motor A direction
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      // Convert the declining Y-axis readings for going backward from 123 to 0 into 0 to max value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joystick1yAxisBytes, 123, 0, 0, motorSpeedAMAX);
         Serial.println(motorSpeedA);
    } else if (data.joystick1yAxisBytes >= 132) {
      // Set Motor A direction
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      // Convert the increasing Y-axis readings for going forward from 138 to 255 into 0 to max value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joystick1yAxisBytes, 132, 255, 0, motorSpeedAReverse);
    } else {
        motorSpeedA = 0;
    }
        if (motorSpeedA < 50) {   // prevent motor stall at low values
        motorSpeedA = 0;
    }
    // convert the right joystick value to an angle for the steering servo
    servoPosition = map(data.joystick2xAxisBytes, 0, 255, steerLeftAngleMAX, steerRightAngleMAX); 
    // eliminate neutral chatter when driving straight
    if ((servoPosition > 88) && (servoPosition < 92)) {
     servoPosition = servoNeutral;
    } 
    // finally write the determined speed and steering position to the motors
    analogWrite(PWMA, motorSpeedA);
    steeringServo.write(servoPosition);
}
//------------------------------------------------------//
