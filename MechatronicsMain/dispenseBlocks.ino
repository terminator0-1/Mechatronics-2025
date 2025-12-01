void dispenceBlock() {
  // Assume driving up to table
  bool waitSwitch = true;
  // 1️⃣ HIT SWITCH PRESSED
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      md.setSpeeds(0, 0);
      straightTrajectory(-8, .5);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
      break;
    }
  }

  moveArmU();
  delay(250);
  myServo1.write(180);
  delay(500);
  myServo1.write(0);
  delay(250);
  moveArmD();
}
