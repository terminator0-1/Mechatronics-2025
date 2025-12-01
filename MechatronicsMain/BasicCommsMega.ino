//Librarys
#include <Servo.h>
#include <Encoder.h>
#include <DualTB9051FTGMotorShieldUnoMega.h>
#include <SharpDistSensor.h>
#include <L298N.h>
#include <QTRSensors.h>

// Line Following
QTRSensors qtr; // create a reflectance sensor object

// Line Following
const uint8_t SensorCount = 8;       // # of sensors in reflectance array
uint16_t sensorValues[SensorCount];  //reflectance sensor readings
float sensor_bias[SensorCount] = {0.0,0.0,5.07,10.10,15.71,20.62,24.53,26.50};
int16_t Sensor_value_unbiased[SensorCount];                                                                         
float d[SensorCount] = {.3,1.3,2.0,2.8,3.7,4.4,5.2,6.0};
bool following = true;
float dTop = 0,dBottom = 0,dComp = 0,error=0;
float d0 = 3.1;

double Kp = 100;           //Proportional Gain for Line Following
double Kd = .8;           // Derivative Gain for Line Following

int m1c = 0, m2c = 0;  //declare and initialize motor commands

int lineCount = 0;
bool prevDetected = false;
const int blackThreshold = 2400;  // adjust if needed
 

const int s0 = 33, s1 = 35, s2 = 37, s3 = 39;
int readPin = 41, LEDPin = 31;

const int numSamples = 8;
float R[numSamples], G[numSamples], B[numSamples], C[numSamples]; // raw pulse time samples
float RF, GF, BF, CF; // filtered data

long counts1, counts2, counts3;  // encoder counts

// SERVO
Servo myServo1, myServo2, myServo3;

Encoder myEnc1(18,19);
Encoder myEnc2(20,21);

// Encoders
double t0 = 0;  // declare some time variables
int countsPerRev = 64;
float rw = 4.15;
float D = 25.8;
float GearRatio = 100;


DualTB9051FTGMotorShieldUnoMega md;
//Pins
const float magPin = A3;
const float magPin2 = A4;
const float IRpin = A2;
SharpDistSensor distsensor(IRpin,10);

////Switches/////
const int homeSwitchPin = 25;
const int dropSwitchPin = 27;
const int hitSwitchPin = 50;

///// L298N /////
const int enaArm = 46;
const int in1Arm = 24;
const int in2Arm = 23;
L298N armMotor(enaArm, in1Arm, in2Arm);
int M = 200;

// Initial Setup
void setup() {

  //Line Following
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){28,30,32,34,36,38,40,42},SensorCount);
  t0 = micros() / 1000000.;

  /////////////PIN STUFF//////////////////////////////////////
  myServo1.attach(49);  //Servo ONE pin
  myServo2.attach(51);  //Servo TWO pin
  myServo3.attach(5); // Servo THREE pin

  myServo1.write(0);
  myServo2.write(0);
  myServo3.write(0);

  // Declare Pinmodes
  pinMode(homeSwitchPin, INPUT_PULLUP);
  pinMode(dropSwitchPin, INPUT_PULLUP);
  pinMode(hitSwitchPin, INPUT_PULLUP);

  //Initialize Base Motors and set encoders.
  md.init();
  md.enableDrivers();
  armMotor.setSpeed(210);
  myEnc1.write(0);
  myEnc2.write(0);

  // Color Sensor Initialization
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(readPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(s0, HIGH); // s1 and s0 choose frequency scaling
  digitalWrite(s1,LOW);
  
  // Open serial communications with Xbee
  Serial.begin(115200);  // make sure to also select this baud rate in your Serial Monitor window
  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");
  // Open serial communications with the other Arduino board
  // Comment out if you are using Mega's serial monitor.
  /////////////////////////////////////////////////
  Serial2.begin(115200);  // this needs to match the mySerial baud rate in UnoSending
  // for wireless comms, it also needs to match the Xbee firmware setting of 115200
  //Send a message to the other Arduino board
  Serial2.print("Hello other Arduino!");
  /////////////////////////////////////////////////
}

// Main Loop
void loop() {

  // Wait here for UNO input
  // GOAL: Wood
  // PICK: Wood
  // SWORD: Wood

  switchState();
}


// FUNCTION CHECKLIST
// - Distance Sensor working accuratley ✔️
// - Arm can move up and down using switches ✔️
// - Servos extend properly✔️
// - Mine Block Servo working ✔️
// - Read Magnets ✔️
// - Read Block colors ✔️
// - Encoders Working with PD control ✔️
// - Line Following working with PD control ✔️

// COMPETITION CHECKLIST
// - MINING ✔️
// - DISPENSING ✔️
// - CRAFTING ✔️
// - CRAFTING --> MINING *requires reset.✔️
// - MINING --> SilverFish 


