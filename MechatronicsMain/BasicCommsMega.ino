//Librarys
#include <Servo.h>
// #include <Encoder.h>
#include <DualTB9051FTGMotorShieldUnoMega.h>
#include <L298N.h>

//Objects
Servo myServo1, myServo2,myServo3;
// PWMServo myServo2;
// Servo myServo3;

// Encoder encLeft(18,19);
// Encoder endRight(20,21);

DualTB9051FTGMotorShieldUnoMega md;
//Pins

///// L298N /////
const int enaArm = 46;
const int in1Arm = 22;
const int in2Arm = 23;
L298N armMotor(enaArm, in1Arm, in2Arm);

//Global Variables
float f = 0.25;
unsigned long t = 0;


String miningState = "wood";

// float motorCurrentLeft = A0;
// float motorCuttentRight = A1;

void setup() {
/////////////PIN STUFF///////////////////////////
myServo1.attach(11,1000,2000); //Servo ONE pin
myServo2.attach(5,1000,2000); //Servo TWO pin
myServo3.attach(13,1000,2000);


//Set Speed of Arm motor.
armMotor.setSpeed(200);

//Initialize Base Motors and set encoders.
md.init();
md.enableDrivers();

// encLeft.write(0);
// endRight.write(0);
/////////////////////////////////////////////////
  // Open serial communications with computer and wait for port to open:
  Serial.begin(57600); // make sure to also select this baud rate in your Serial Monitor window

  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");

  // Open serial communications with the other Arduino board
  Serial1.begin(115200);  // this needs to match the mySerial baud rate in UnoSending
  // for wireless comms, it also needs to match the Xbee firmware setting of 115200

  // Send a message to the other Arduino board
  Serial1.print("Hello other Arduino!");
}

void loop() {
  double t = micros() / 1000000.0;
  //int M = 400 * sin(2 * PI * f * t);
  int M = 400;
  if (Serial.available()) {
    Serial1.println(Serial.readStringUntil('\n'));
  }

  if (Serial1.available()) {
    String dataString = Serial1.readStringUntil('\n');  // read from Serial1 only
    dataString.trim();                                  // remove whitespace/newline

    // Defensive check: make sure string is the correct format.
    if (dataString.length() <= 7) {
      char Signal = dataString.charAt(0);
      // char blocktype = dataString.charAt(0);           // single char
      // String cellStatus = dataString.substring(2, 5);  // substring [2,4)
      // char pickType = dataString.charAt(6);

      // Debug
      Serial.print("User entered ");
      Serial.println(Signal);
      // Serial.println(cellStatus);
      // Serial.println(pickType);

      switch (Signal) {
        case 'F':
          driveForward(M, t);
          Serial.println("Driving Forward...");
          break;

        case 'B':
          driveBackward(M,t);
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
          myServo1.write(150);
          myServo2.write(150);
          myServo3.write(150);
          delay(250);
          myServo1.write(0);
          myServo2.write(0);
          myServo3.write(0);
          break;

        default:
          Serial.println("Unknown command.");
          break;
      }
    } else {
      Serial.println("Data too short!");
    }
  }
}
