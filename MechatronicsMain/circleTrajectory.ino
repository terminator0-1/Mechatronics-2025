void circleTrajectory(float circleRadius, float travelAngle, float travelTime) {

  float theta1_final = 0, theta2_final = 0;
  int m1backwardsFlag = 1, m2backwardsFlag = 1;
  char spinFlag = 'n';

  if (travelAngle > 0) {
    theta1_final = -((travelAngle * (PI / 180.0) * 1.05) * (circleRadius + D)) / rw;
    theta2_final = -((travelAngle * (PI / 180.0) * 1.05) * circleRadius) / rw;
  }else{
  theta1_final = ((travelAngle * (PI / 180.0) * 1.05) * circleRadius) / rw;
  theta2_final = ((travelAngle * (PI / 180.0) * 1.05) * (circleRadius + D)) / rw;
  }
  getTrajectory(theta1_final, theta2_final, travelTime, spinFlag, m1backwardsFlag, m2backwardsFlag);
}
