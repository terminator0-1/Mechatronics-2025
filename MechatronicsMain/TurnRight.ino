void turnRight(int M){
  md.setM1Speed(-M);
  md.setM2Speed(M);

  delay(2000);

  md.setM1Speed(0);
  md.setM2Speed(0);
  // position = encLeft.read();
  //  if (position >= 500){
  //   md.setSpeed(0);
  //   encLeft.write(0);
  //   Serial.println("Robot has turned right.")
  // }
}
