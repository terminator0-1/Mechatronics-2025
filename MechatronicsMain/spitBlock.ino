// If the block recieved is not desired--> call this.
void spitBlock(){
  bool waitSwitch = true;
  //Drive Backwards
  delay(1000);
  straightTrajectory(-15,2);

  // Turn to the left
  spinTrajectory(-95,2);

  // Command Servo only for first block.
  delay(200);
  myServo1.write(90);
  delay(200);
  myServo1.write(0);

  // Reverse Sequence -- spin -- drive
  spinTrajectory(95,2);

  md.setSpeeds(100,100);

  // 1️⃣ HIT SWITCH PRESSED
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      md.setSpeeds(0, 0);
      straightTrajectory(-2, .25);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
    }
  }

  //Continue Mining assuming in the correct spot. 
}
