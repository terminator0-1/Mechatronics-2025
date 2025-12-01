void correctMagnetBlock() {
  const int stopped = 250;
  unsigned long timeStart = millis();

  armMotor.forward();

  while (millis() - timeStart < stopped) {
    // wait until 250 ms passes
  }
  // Arm will stop away from magnetic
  armMotor.stop();
  myServo2.write(60);
  delay(200);
  myServo2.write(0);
  moveArmD();
}
