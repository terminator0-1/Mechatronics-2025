void spinTrajectorySpecial(float spinAngle, float travelTime) {
  float theta1_final = 0, theta2_final = 0;
  int m1backwardsFlag = 0, m2backwardsFlag = 0;
  char spinFlag = 'i';

   if (spinAngle < 0) {
    m1backwardsFlag = -1;
    m2backwardsFlag = 1;
     theta1_final = -((spinAngle*(PI / 180.0)) * (D / 2.0)) / rw;
    theta2_final = 0;
  } else {
    m1backwardsFlag = 1;
    m2backwardsFlag = -1;
    theta1_final = 0;
    theta2_final = ((spinAngle * (PI / 180.0)) * (D / 2.0)) / rw;
  }
  getTrajectory(theta1_final, theta2_final, travelTime,spinFlag, m1backwardsFlag, m2backwardsFlag);
}
