void dispenceBlockMining(int rowDeposit) {
  // Assume driving up to table
  bool waitSwitch = true;
  // 1️⃣ HIT SWITCH PRESSED
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      md.setSpeeds(0, 0);
      switch (rowDeposit) {
        case 1:  // Far Row
          straightTrajectory(-8, .5);
          moveArmU();
          delay(250);
          myServo1.write(180);
          delay(500);
          myServo1.write(0);
          delay(250);
          moveArmD();
          break;

        case 2:
          straightTrajectory(-15, 1);
          moveArmU();
          delay(250);
          myServo1.write(180);
          delay(500);
          myServo1.write(0);
          delay(250);
          moveArmD();
          break;

        case 3:
          delay(250);
          myServo1.write(180);
          delay(500);
          myServo1.write(0);
          delay(250);
          break;
      }
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
      break;
    }
  }
}
