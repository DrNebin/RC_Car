// Arduino RC Car developed and programmed by Devin Namaky for his children
// Any microcontroller will do, but using here a Seeeduino XIAO for a small footprint (we want a small car to print on a resin printer)
// Two generic joysticks for a remote. This version is wireless. There is a separate INO file for the controller code using a NANO.
// Joysticks can be programmed a variety of ways. This version the left joystick y-axis controls F / R, and the right joystick x-axis controls L / R. The right joystick push button is used to control the max motor speed. This is useful if you wnat to run the car indoor vs outdoor or simply don't want to strip your gears or crash into a wall with too much power depending on the battery setup you choose.
// Motor driver occupying PINs 0 thru 5 on a Seeeduino XIAO as the below variables indicate.
// Wireless nRF24L01 SPI is on 8 thru 10, and CE / CSN are pins 6 and 7
// This version is driving with two DC motors and no servo. The steering DC motor has something akin to rack and pinion for steering for now.

//--------------DEFINITIONS & LIBRARIES--------------------//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(6, 7); // CE, CSN
const byte address[6] = "00001";

int PWMA = 1;
int AIN1 = 2; 
int AIN2 = 0;  
int PWMB = 5;
int BIN1 = 3;
int BIN2 = 4;
int motorSpeedA = 0;
int motorSpeedB = 0;
int steerPower = 125; // Adjust for power delivered to steering
int motorSpeedAMAX = 90; //Adjust for maximum power delivered to motor A
int joystick1xAxis; 
int joystick1yAxis;
int joystick2xAxis; 
int joystick2yAxis;

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
  resetData();
}
//------------------------------------------------------//


//---------------------MAIN LOOP---------------------//
void loop()
{ 
  if ( radio.available()) { 
     radio.read(&data, sizeof(Data_Package)); // Read the signals from the joysticks
     //Serial.println("joystick1-Y: "); // This section blocked out (for debugging if needed)
     //Serial.print(data.joystick1yAxisBytes);
     //Serial.println("joystick2-X: ");
     Serial.println(data.joystick2xAxisBytes);

     int joystick1xAxis = map(data.joystick1xAxisBytes, 0, 255, 0, 1023);
     int joystick1yAxis = map(data.joystick1yAxisBytes, 0, 255, 0, 1023);
     int joystick2xAxis = map(data.joystick2xAxisBytes, 0, 255, 0, 1023);
     int joystick2yAxis = map(data.joystick2yAxisBytes, 0, 255, 0, 1023);
  
  // Left joystick Y-axis used for forward and backward control
  //--------------------
  // Y-axis used for forward and backward control
  if (joystick1yAxis < 470) {
    // Set Motor A backward
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high

    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(joystick1yAxis, 470, 0, 0, motorSpeedAMAX);
  } else if (joystick1yAxis > 550) {
    // Set Motor A forward
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(joystick1yAxis, 550, 1023, 0, motorSpeedAMAX);
  } else {
    motorSpeedA = 0;
  }
    
//--------------
  if (joystick2xAxis < 300) {
    // Set Motor B backward
    digitalWrite(BIN1, HIGH);      
    digitalWrite(BIN2, LOW);   
    motorSpeedB = steerPower;

  } else if (joystick2xAxis > 700) {
    // Set Motor B forward
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    motorSpeedB = steerPower;
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedB = 0;
  }

//-------------------
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  
  analogWrite(PWMA, motorSpeedA); //now that the motor direction is set, drive it at the entered speed// Send PWM signal to motor A
  analogWrite(PWMB, motorSpeedB); //now that the motor direction is set, drive it at the entered speed // Send PWM signal to motor B
} 
} 
//------------------------------------------------------//





//---------------OTHER COMMAND DEFINITIONS----------------------------//
void resetData() { // Set the signals from the joysticks to neutral initially so the motors don't move yet
  data.joystick1xAxisBytes = 127;
  data.joystick1yAxisBytes = 127;
  data.joystick2xAxisBytes = 127;
  data.joystick2yAxisBytes = 127;
  int joystick1xAxis = 500; 
  int joystick1yAxis = 500;
  int joystick2xAxis = 500; 
  int joystick2yAxis = 500;
  }
//------------------------------------------------------//
