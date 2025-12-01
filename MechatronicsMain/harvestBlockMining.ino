void harvestBlockMining(char pick) {

  bool waitSwitch = true;
  // We wont be rejecting blocks now.
  bool reject = false;
  int attempt = 0, collected = 0;
  // Start 
  orient();
  // 1️⃣ HIT SWITCH PRESSED
  while (waitSwitch) {
    if (digitalRead(hitSwitchPin) == 1) {
      Serial2.println("SWITCH HIT");
      md.setSpeeds(0, 0);
      straightTrajectory(-2.25, .25);
      Serial.println("Hit Switch Pressed → STOP");
      waitSwitch = false;
      break;
    }
  }

  while (collected < 3) {
    delay(500);
    char sensedColor = readColor(s2, s3, readPin);
    //bool reject = determineRejection(sensedColor, pick);
    int finalHits = getHits(sensedColor, reject, collected, pick);
    mineServo(finalHits);

    straightTrajectory(-4, .25);
    delay(1000);
    bool silverFishKilled = readMagnet(2.5, collected);

    collected += 1;
    delay(500);
    if (collected <= 2) {
      delay(500);
      myServo2.write(50);
      delay(500);
      myServo2.write(0);

      // correctMagnetBlock();
      
      // If the silverfish was killed this will be true and we wont need to move back forward
      // because we already moved up to kill it.
      if (silverFishKilled == false) {
        straightTrajectory(4, .25);
      }
    }
  }
  Serial2.println("Finished MINING. Going to table");
}

// Block should now be collected and moved to the right.
// blockCount += 1;
