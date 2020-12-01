// Arduino RC Car developed and programmed by Devin Namaky for his children
// Any microcontroller will do, but using here a Seeeduino XIAO for a small footprint (we want a small car to print on a resin printer)
// Two generic joysticks for a remote. This version is wireless. There is a separate INO file for the controller code using a NANO.
// Joysticks can be programmed a variety of ways. This version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. This is useful if you wnat to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the battery setup you choose.
// Motor driver occupying PINs 0 thru 5 on a Seeeduino XIAO as the below variables indicate.
// Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7
// This version is driving with two DC motors and no servo. The steering DC motor has something akin to rack and pinion for steering for now.

//--------------DEFINITIONS & LIBRARIES--------------------//
#include <SPI.h>
#include <RF24.h>
RF24 radio(6, 7); // CE, CSN
const byte address[6] = "00001";

byte PWMA = 1;
byte AIN1 = 2;
byte AIN2 = 0;
byte PWMB = 5;
byte BIN1 = 3;
byte BIN2 = 4;
byte motorSpeedA = 0;
byte motorSpeedB = 0;
byte steerPower = 255; // Adjust for power delivered to steering (0 to 255)
byte motorSpeedAMAX = 255; //Adjust for maximum power delivered forward to motor A (0 to 255)
byte motorSpeedAReverse = 255; //Adjust for maximum power delivered reverse to motor A (0 to 255)
unsigned long lastSpeedButtonReadTime = 0;
unsigned long lastControllerReadTime = 0;
unsigned long currentMillis = 0;

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
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
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
    //set motor speeds
    setMotorSpeeds();
        // check speed mode select button, including a 500 ms time period where the button is ignored after being pressed to avoid accidental repeats
        //if receiving button data and the button is pressed, and the necessary time has passed
        //check the time
        currentMillis = millis();
    if ((radio.available()) && (data.joystick2Button == LOW) && ((currentMillis - lastSpeedButtonReadTime) > 500)) {
        // then change the max speed
        if (motorSpeedAMAX == 90) {
            motorSpeedAMAX = 175;} else if (motorSpeedAMAX == 175) {
                motorSpeedAMAX = 255;} else if (motorSpeedAMAX == 255) {
                    motorSpeedAMAX = 90;
            }
        lastSpeedButtonReadTime = millis();
        Serial.println(motorSpeedAMAX);
    }
}
//------------------------------------------------------//

//---------------OTHER COMMAND DEFINITIONS----------------------------//
void resetData() { // Set the signals from the joysticks to neutral initially so the motors don't move yet
    data.joystick1xAxisBytes = 127;
    data.joystick1yAxisBytes = 127;
    data.joystick2xAxisBytes = 127;
    data.joystick2yAxisBytes = 127;
    data.joystick2Button = 1;
         Serial.println("reset data"); //Serial printing generally commented out to save RAM unless debugging
  }

void readController() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
     /* Serial.println("joystick1-Y: ");
     Serial.print(data.joystick1yAxisBytes);
     Serial.print("joystick2-Y: ");
     Serial.print(data.joystick2yAxisBytes);
      Serial.println("joystick1-X: ");
      Serial.print(data.joystick1xAxisBytes);
      Serial.print("joystick2-X: ");
      Serial.print(data.joystick2xAxisBytes); */
      //Serial.println("joystick2-Button: ");
      //Serial.print(data.joystick2Button); 
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
        //--------------------
        // Y-axis used for forward and backward control
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
    
    if (data.joystick2xAxisBytes <= 100) {
      // Set Motor B direction
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      motorSpeedB = steerPower;
    } else if (data.joystick2xAxisBytes >= 150) {
      // Set Motor B direction
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      motorSpeedB = steerPower;
    } else {
        motorSpeedB = 0;
    }
    
    if (motorSpeedA < 20) {
        motorSpeedA = 0;
    }
    if (motorSpeedB < 20) {
        motorSpeedB = 0;
    }
    analogWrite(PWMA, motorSpeedA); //now that the motor direction is set, drive it at the entered speed// Send PWM signal to motor A
    analogWrite(PWMB, motorSpeedB); //now that the motor direction is set, drive it at the entered speed // Send PWM signal to motor B
}
//------------------------------------------------------//
