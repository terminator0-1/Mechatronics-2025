void spinTrajectory(double &theta1_final, double &theta2_final, float &travelTime, int &m1backwardsFlag, int &m2backwardsFlag) {
  Serial.print("Spin");
  Serial2.println("Enter Spin Angle (deg)");
  while (!Serial2.available());
  float spinAngle = Serial2.parseFloat() * (PI / 180.0) * 1.08;
  Serial2.readStringUntil('\n');  // clear buffer

  Serial2.println("Enter Travel Time (deg): ");
  while (!Serial2.available());
  travelTime = Serial2.parseFloat();
  Serial2.readStringUntil('\n');  // clear buffer

  if (spinAngle < 0) {
    m1backwardsFlag = -1;
    m2backwardsFlag = 1;
    theta1_final = (spinAngle * (D / 2.0)) / rw;
    theta2_final = -theta1_final;
  } else {
    m1backwardsFlag = 1;
    m2backwardsFlag = -1;
    theta1_final = (spinAngle * (D / 2.0)) / rw;
    theta2_final = -theta1_final;
  }
}
