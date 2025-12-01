void straightTrajectory(float finalDist, float travelTime) {
  md.setSpeeds(0,0);

  float theta1_final = 0, theta2_final = 0;
  float m1backwardsFlag = 0, m2backwardsFlag = 0;
  char spinFlag = 'n';
  
  if (finalDist < 0) {
    m1backwardsFlag = -1;
    m2backwardsFlag = -1;
    theta1_final = (finalDist / rw);
    theta2_final = theta1_final;
  } else {
    m1backwardsFlag = 1;
    m2backwardsFlag = 1;
    theta1_final = (finalDist / rw);
    theta2_final = theta1_final;
  }
  getTrajectory(theta1_final, theta2_final, travelTime,spinFlag, m1backwardsFlag, m2backwardsFlag);
}

