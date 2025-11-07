void straightTrajectory(float finalDist, float travelTime) {

  //Serial2.println("Enter Final Distance (cm): ");

  // while (!Serial2.available());
  // float finalDist = Serial2.parseFloat() * 1.08;
  // Serial2.readStringUntil('\n');  // clear buffer

  // Serial2.println("Enter Velocity (s): ");
  // while (!Serial2.available());
  // travelTime = finalDist / Serial2.parseFloat();
  // Serial2.readStringUntil('\n');  // clear buffer

  float theta1_final = 0, theta2_final = 0;
  float m1backwardsFlag = 0, m2backwardsFlag = 0;
  char spinFlag = 'b';
  if (finalDist < 0) {
    m1backwardsFlag = -1;
    m2backwardsFlag = -1;
    theta1_final = finalDist / rw;
    theta2_final = -theta1_final;
  } else {
    m1backwardsFlag = 1;
    m2backwardsFlag = 1;
    theta1_final = finalDist / rw;
    theta2_final = -theta1_final;
  }
  getTrajectory(theta1_final, theta2_final, travelTime, spinFlag, m1backwardsFlag, m2backwardsFlag);
}


//  if (theta1_des < theta1_final) {
//       theta1_des = theta1_des + omega1_des * deltaT;
//     }
//     if (theta2 < theta2_final) {
//       theta2_des = theta2_des + omega2_des * deltaT;
//     }
