void harvestBlock(char pick) {
  bool waitSwitch = true;
  bool silverFishKilled = false;
  int attempt = 0, collected = 0;
  // Start
  followLine(true, 250);

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
    // If mining mode, dont reject blocks, instead sense for silverfish.
    char sensedColor = readColor(s2, s3, readPin);
    bool reject = determineRejection(sensedColor,pick);
    int finalHits = getHits(sensedColor, reject, collected, pick);
    mineServo(finalHits);

    straightTrajectory(-4, .25);
    delay(1000);

    if(reject == true){
      spitBlock();
    } else{
    }
    // Serial2.println(attempt);
    // Serial2.println(collected);
    // Move back in place only for first and second block.

    if (reject == true) {
      attempt += 1;
    } else {
      collected += 1;
    }
    if (collected <= 2 && reject == false) {
      delay(500);
      myServo2.write(50);
      delay(500);
      myServo2.write(0);
      // Harvest again.
      if (silverFishKilled == false) {
        straightTrajectory(4, .25);
      }
    }
  }

  Serial2.println("Finished MINING. Going to table");
}

// Block should now be collected and moved to the right.
// blockCount += 1;
