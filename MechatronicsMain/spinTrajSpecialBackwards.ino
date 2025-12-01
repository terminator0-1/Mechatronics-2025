void spinTrajectorySpecialBackward(float spinAngle, float travelTime) {

  // Serial.print("Spin");
  // Serial2.println("Enter Spin Angle (deg)");
  // while (!Serial2.available());
  // float spinAngle = Serial2.parseFloat() * (PI / 180.0) * 1.08;
  // Serial2.readStringUntil('\n');  // clear buffer

  // Serial2.println("Enter Travel Time (deg): ");
  // while (!Serial2.available());
  // travelTime = Serial2.parseFloat();
  // Serial2.readStringUntil('\n');  // clear buffer

  float theta1_final = 0, theta2_final = 0;
  int m1backwardsFlag = 0, m2backwardsFlag = 0;
  char spinFlag = 'i';

   if (spinAngle < 0) {
    m1backwardsFlag = 1;
    m2backwardsFlag = 1;
     theta1_final = 0;
    theta2_final = ((spinAngle*(PI / 180.0)) * (D / 2.0)) / rw;
  } else {
    m1backwardsFlag = 1;
    m2backwardsFlag = -1;
    theta1_final = 0;
    theta2_final = ((spinAngle * (PI / 180.0)) * (D / 2.0)) / rw;
  }
  getTrajectory(theta1_final, theta2_final, travelTime,spinFlag, m1backwardsFlag, m2backwardsFlag);
}
