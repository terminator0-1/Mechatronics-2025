// Library and Object Setup
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // RX, TX

// Variable Intialization
unsigned long time = 0;
unsigned long time_old = 0;



void setup()  
{
  // Open serial communications with computer and wait for port to open:
  Serial.begin(115200);  // make sure to also select this baud rate in your Serial Monitor window

  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");

  // Open serial communications with the other Arduino board
  mySerial.begin(115200);  // this needs to match the Serial1 baud rate in MegaReceiving
  // for wireless comms, it also needs to match the Xbee firmware setting of 115200

  // Send a message to the other Arduino board
  mySerial.print("Hello other Arduino!");

}


void loop(){
  if (Serial.available()) {
    mySerial.println(Serial.readStringUntil('\n'));
  }

  if (mySerial.available()) {
    Serial.println(mySerial.readStringUntil('\n'));
    
  }
}
