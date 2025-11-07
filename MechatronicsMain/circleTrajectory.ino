void circleTrajectory(double &theta1_final, double &theta2_final, float &travelTime){
Serial2.println("Enter Circle Radius (cm): ");
while (!Serial2.available());
float circleRadius = Serial2.parseFloat();
Serial2.readStringUntil('\n');  // clear buffer

Serial2.println("Enter Travel Angle (deg): ");
while (!Serial2.available());
float travelAngle = Serial2.parseFloat() * (PI/180) * 1.08;
Serial2.readStringUntil('\n');  // clear buffer

Serial2.println("Enter Velocity (cm/s): ");
while (!Serial2.available());
travelTime = (travelAngle * circleRadius) / Serial2.parseFloat();
Serial2.readStringUntil('\n');  // clear buffer

//Both thetas are positive.
theta1_final = (travelAngle * circleRadius) / rw;
theta2_final = (travelAngle * (circleRadius + D)) / rw;
// theta1_final = (travelAngle * (circleRadius/2)) / rw;
// theta2_final = (travelAngle * ((circleRadius/2) * D)) / rw;

}
