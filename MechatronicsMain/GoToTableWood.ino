void goToTableWood() {
  straightTrajectory(-20, 2);

  spinTrajectory(-95, 3);

  circleTrajectory(-40, 88, 4);

  md.setSpeeds(200,200);
  
  // Wait for the switch to be hit.
    bool waitSwitch = true;
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      delay(500);
      md.setSpeeds(0, 0);
      straightTrajectory(-4, .75);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
    }
  }
  spinTrajectory(75, 2);

  md.setSpeeds(200, 200);

  waitSwitch = true;
  // Wait for the switch to be hit.
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      delay(750);
      md.setSpeeds(0, 0);
      straightTrajectory(-15, 1);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
    }
  }
}
