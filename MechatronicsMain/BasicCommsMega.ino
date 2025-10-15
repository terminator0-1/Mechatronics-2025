//Librarys
#include <Servo.h>
// #include <Encoder.h>
#include <DualTB9051FTGMotorShieldUnoMega.h>
#include <SharpDistSensor.h>
#include <L298N.h>
#include <QTRSensors.h>

// Library objects
QTRSensors qtr; // create a reflectance sensor object

  // Global variables
const uint8_t SensorCount = 8;       // # of sensors in reflectance array
uint16_t sensorValues[SensorCount];  //reflectance sensor readings
double t, t0, print_time = 0;        // declare some time variables

float sensor_bias[SensorCount] = { 330.8225, 231.0588, 281.4118, 231.0588, 231.0588, 281.448, 231.0588, 327.6741 };  //reflectance sensor readings
int16_t Sensor_value_unbiased[SensorCount];                                                                          //reflectance sensor readings
float d[SensorCount] = { 0, 0.8, 1.6, 2.4, 3.2, 4.0, 4.8, 5.6 };
bool following = true;
float dTop = 0;
float dBottom = 0;
float dComp = 0;
float d0 = 2.8;
float error = 0;
double Kp = 26;           //Proportional Gain for Line Following
double base_speed = 200;  //Nominal speed of robot
int m1c = 0, m2c = 0;  //declare and initialize motor commands

//Objects
Servo myServo1, myServo2, myServo3;
// PWMServo myServo2;
// Servo myServo3;
// Encoder encLeft(18,19);
// Encoder endRight(20,21);
DualTB9051FTGMotorShieldUnoMega md;
//Pins
const float IRpin = A2;
SharpDistSensor distsensor(IRpin,1);

////Switches/////
const int homeSwitch = 53;
const int dropSwitch = 54;

///// L298N /////
const int enaArm = 46;
const int in1Arm = 22;
const int in2Arm = 23;
L298N armMotor(enaArm, in1Arm, in2Arm);
int M = 200;

// float motorCurrentLeft = A0;
// float motorCuttentRight = A1;

void setup() {
  //Line Following
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){28,30,32,34,36,38,40,42},SensorCount);
  t0 = micros()/1000000.;
  distsensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);

  /////////////PIN STUFF///////////////////////////
  myServo1.attach(11, 1000, 2000);  //Servo ONE pin
  myServo1.write(-30); //Servo one zero position
  myServo2.attach(5, 1000, 2000);  //Servo TWO pin
  myServo3.attach(13, 1000, 2000);
  pinMode(homeSwitch, INPUT);
  pinMode(dropSwitch, INPUT);

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
  switchState();
}
