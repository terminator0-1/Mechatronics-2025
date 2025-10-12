void followLine(){
  //Using the line sensor to follow the line.

  // Lab7Template.ino
// Prof. Stephen Mascaro
// 10/05/23

//  This sketch will be used to perform line localization and line following

// Library imports
#include <QTRSensors.h>
#include <DualTB9051FTGMotorShield.h>

// Library objects
QTRSensors qtr; // create a reflectance sensor object
DualTB9051FTGMotorShield md; // create a motor driver object


// Global variables
const uint8_t SensorCount = 8;  // # of sensors in reflectance array
uint16_t sensorValues[SensorCount];  //reflectance sensor readings
double t, t0, print_time=0; // declare some time variables

float sensor_bias[SensorCount] = {330.8225, 231.0588, 281.4118, 231.0588, 231.0588, 281.448, 231.0588, 327.6741};  //reflectance sensor readings
int16_t Sensor_value_unbiased[SensorCount];  //reflectance sensor readings
float d[SensorCount] = {0, 0.8, 1.6, 2.4, 3.2, 4.0, 4.8, 5.6};

float dTop = 0;
float dBottom = 0;
float dComp = 0;
float d0 = 2.8;
float error = 0;
double Kp=50; //Proportional Gain for Line Following
double base_speed=100; //Nominal speed of robot

int m1c=0, m2c=0;  //declare and initialize motor commands

// Remember to use the correct syntax for initializing an array.
// The array needs to know how large it is along with any initial values
// datatype array[size];
// datatype array2[3] = {0, 0, 0};
 
void setup() {
  // initialize reflectance sensor and motor driver
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){27,29,31,33,35,37,39,41},SensorCount);
  md.init(); 
  md.enableDrivers();

  Serial.begin(9600);
    
  // Uncomment the following code when you get to the relevant section in lab
  // in order to input Kp and base_speed from Serial Monitor
  
  String inString = "";
  Serial.println("Input values for Kp and base_speed with a space between");
  while(Serial.available()==0);
  inString = Serial.readStringUntil(' ');
  Kp = inString.toFloat();
  inString = Serial.readStringUntil(' ');
  base_speed = inString.toFloat();
  
  t0 = micros()/1000000.;
  Serial.print("Kp = ");
  Serial.println(Kp);
  Serial.print("Base Speed = ");
  Serial.println(base_speed);

  t0 = micros()/1000000.; // initialize time
}




void loop() {
 
  t = micros()/1000000.-t0;
  qtr.read(sensorValues); // sensor values will be numbers between 0 and 2500
  
  ////////// LINE LOCALIZATION CODE
  // Remember to use for loops for assigning values to an array, you cannot
  // assign values to multiple array indicies at once
  for (int i = 0; i < 8; i++){
    Sensor_value_unbiased[i] = sensorValues[i] - sensor_bias[i];
        
      }
  // The above structure:
  //      Initializes a temporary variable
  //      Sets a condition to loop while true
  //      Tells the temporary variable how to update after each loop

  dTop = 0;
  dBottom = 0;
  for (int i = 0; i < 8; i++){
    dTop = dTop + Sensor_value_unbiased[i]*d[i];
    dBottom = dBottom + Sensor_value_unbiased[i];
  }
  dComp = dTop / dBottom;
  error = d0 - dComp;
 
 m1c = base_speed + Kp * error;
 m2c = base_speed - Kp * error;

  ////////// LINE FOLLOWING CODE
  md.setSpeeds(m1c,m2c); // send motor commands

  // PRINT STATEMENTS
  // non-blocking way to delay printing  
  if ((t-print_time)>0.25) { 
    
    // This for loop is used to print out variables that are arrays
    for (uint8_t i=0; i < SensorCount; i++)
    {
      Serial.print(Sensor_value_unbiased[i]);
      Serial.print('\t');
    }
    // Print any non-array variables here
    Serial.println(error);
    print_time=t;
  }

}

}
