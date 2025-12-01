void harvestWood(char pick) {
  delay(100);
  Serial.println("Harvesting Wood...");
  int hitWood;

    switch(pick){
    case 'w':
    hitWood = 5;
    break;
    
    case 's':
    hitWood = 4;
    break;

    case 'i':
    hitWood = 2;
    break;

    case 'd':
    hitWood = 1;
    break;
  }

  for (int i = 1; i <= 2; i++) {
    delay(200);
    // Move back in place only for first and second block.
    if (i == 1) {
      mineServo(hitWood-1);
    } else {
      mineServo(hitWood+1);
    }

    straightTrajectory(-4, .25);
    delay(1000);
    myServo2.write(50);
    delay(500);
    myServo2.write(0);

    // Harvest again.
    if (i == 1) {
      straightTrajectory(4, .25);
    }

    Serial2.println("Finished MINING. Going to table");
  }
}

