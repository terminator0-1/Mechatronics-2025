//Librarys
#include <Servo.h>
// #include <Encoder.h>
#include <DualTB9051FTGMotorShieldUnoMega.h>
#include <L298N.h>

//Objects
Servo myServo1, myServo2, myServo3;
// PWMServo myServo2;
// Servo myServo3;
// Encoder encLeft(18,19);
// Encoder endRight(20,21);

DualTB9051FTGMotorShieldUnoMega md;
//Pins
const int IRpin = A2;
////Switches/////
const int homeSwitch = 53;
const int dropSwitch = 54;

///// L298N /////
const int enaArm = 46;
const int in1Arm = 22;
const int in2Arm = 23;
L298N armMotor(enaArm, in1Arm, in2Arm);
int M = 400;

// float motorCurrentLeft = A0;
// float motorCuttentRight = A1;

void setup() {
  /////////////PIN STUFF///////////////////////////
  myServo1.attach(11, 1000, 2000);  //Servo ONE pin
  myServo1.write(-30); //Servo one zero position
  myServo2.attach(5, 1000, 2000);  //Servo TWO pin
  myServo3.attach(13, 1000, 2000);
  pinMode(homeSwitch, INPUT);
  pinMode(dropSwitch, INPUT);
  pinMode(IRpin, OUTPUT);

 

  //Initialize Base Motors and set encoders.
  md.init();
  md.enableDrivers();
  armMotor.setSpeed(200);
  // encLeft.write(0);
  // endRight.write(0);
  
  /////////////////////////////////////////////////
  // Open serial communications with computer and wait for port to open:
  Serial.begin(115200);  // make sure to also select this baud rate in your Serial Monitor window
  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");
  // Open serial communications with the other Arduino board
  // Comment out if you are using Mega's serial monitor.
  /////////////////////////////////////////////////
  Serial1.begin(115200);  // this needs to match the mySerial baud rate in UnoSending
  // for wireless comms, it also needs to match the Xbee firmware setting of 115200
  //Send a message to the other Arduino board
  Serial1.print("Hello other Arduino!");
  /////////////////////////////////////////////////
}

void loop() {
  //  * FOR MEGA SERIAL CHANGE SERIAL1 TO SERIAL HERE *
  //////////////////////////////////////////
  if (Serial1.available()) {
    
    String dataString = Serial1.readStringUntil('\n');
    dataString.trim();

  //////////////////////////////////////////
    if (dataString.length() <= 7) { 
      char Signal = dataString.charAt(0);
      // char blocktype = dataString.charAt(0);           // single char
      // String cellStatus = dataString.substring(2, 5);  // substring [2,4)
      // char pickType = dataString.charAt(6);
    
      switch (Signal) {
        case 'F':
          driveForward(M);
          Serial.println("Driving Forward...");
          break;

        case 'B':
          driveBackward(M);
          Serial.println("Driving Backward...");
          break;

        case 'L':
          turnLeft(M);
          Serial.println("Turning Left...");
          break;

        case 'R':
          turnRight(M);
          Serial.println("Turning Right...");
          break;

        case 'U':  // maybe shorthand for "craft"
          moveArmU();
          Serial.println("Moving Arm Up.");
          break;

        case 'D':
          moveArmD();
          Serial.println("Moving Arm Down.");
          break;
        case 'S':
          myServo1.write(100);
          // myServo2.write(150);
          // myServo3.write(150);
          delay(250);
          myServo1.write(0);
          // myServo2.write(0);
          // myServo3.write(0);
          break;
        case 'C':
          // Start LineFollowing
          //followLine();
          break;
        case 'W':
            // Drive up to wall and stop at given distance
            //Have user enter distance
            //int dist = Serial.read();
            readWall(1.30,M);
          break;
        case 'M':
          Serial.println("-------------Menu---------------");
          Serial.println("F - Drive Forward");
          Serial.println("B - Drive Backward");
          Serial.println("L - Turn Left");
          Serial.println("R - Turn Right");
          Serial.println("U - Move Arm Up");
          Serial.println("D - Move Arm Down");
          Serial.println("S - Move Servos");
          Serial.println("C - Follow Line");
          Serial.println("W - Sense Wall");
          break;
      }
    }
  }
}
