// Uses an Arduino NANO with two analog joysticks (right and left). Sends to nRF24L01 on the car being controlled


//----------------DEFINITIONS AND LIBRARIES---------------------//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int joystick1ButtonPin = 2;
int joystick2ButtonPin = 3;

struct Data_Package {   // Create a single data package to be sent over wireless
  byte joystick1xAxisBytes;
  byte joystick1yAxisBytes;
  byte joystick1Button;
  byte joystick2xAxisBytes;
  byte joystick2yAxisBytes;
  byte joystick2Button;
  };
Data_Package data; // Creates a variable "data" with the above structure of bytes
//------------------------------------------------------//

//----------------------SETUP---------------------------//
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  resetData();
  pinMode(joystick1ButtonPin, INPUT_PULLUP);
  pinMode(joystick2ButtonPin, INPUT_PULLUP);
}
//------------------------------------------------------//

//------------------MAIN LOOP------------------------//
void loop() {
  data.joystick1xAxisBytes = map(analogRead(A0), 0, 1023, 0, 255); // Read Joystick 1 X-axis and map to bytes
  data.joystick1yAxisBytes = map(analogRead(A1), 0, 1023, 0, 255); // Read Joystick 1 Y-axis and map to bytes
  data.joystick2xAxisBytes = map(analogRead(A2), 0, 1023, 0, 255); // Read Joystick 2 X-axis and map to bytes
  data.joystick2yAxisBytes = map(analogRead(A3), 0, 1023, 0, 255); // Read Joystick 2 Y-axis and map to bytes
  data.joystick1Button = digitalRead(joystick1ButtonPin);
  data.joystick2Button = digitalRead(joystick2ButtonPin);
  radio.write(&data, sizeof(Data_Package));   // Send the data package to the receiver

/*     Serial.print("joystick1-Y: "); // This section blocked out (for debugging if needed)
     Serial.print(data.joystick1yAxisBytes);
     Serial.print("joystick2-X: ");
     Serial.print(data.joystick2xAxisBytes);  */
}
//------------------------------------------------------//

//----------------OTHER COMMAND DEFINITIONS--------------//
void resetData() {  //resets joystick values to neutral
  data.joystick1xAxisBytes = 127;
  data.joystick1yAxisBytes = 127;
  data.joystick2xAxisBytes = 127;
  data.joystick2yAxisBytes = 127;
  data.joystick1Button = 1;
  data.joystick2Button = 1;
  }
  //------------------------------------------------------//
