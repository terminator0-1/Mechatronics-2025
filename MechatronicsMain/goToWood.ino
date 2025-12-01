
// ####################################
// Function to go to wood from table.
void goToWood() {
  straightTrajectory(-10, 1);
  spinTrajectory(-95, 1);
  straightTrajectory(30, 2);
  countLines(1, 250);
  spinTrajectory(-98, 1);
  md.setSpeeds(100, 100);

  // Wait for switch to be hit.
  bool waitSwitch = true;
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      md.setSpeeds(0, 0);
      straightTrajectory(-2.25, .5);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
      break;
    }
  }
}
