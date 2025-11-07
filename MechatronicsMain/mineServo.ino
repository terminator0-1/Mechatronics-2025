void mineServo(char sensedColor) {
  
  int hits = 0;
  unsigned long hitTime = 130;
  // Serial2.println("Enter block (y,r,b): ");
  // while (!Serial2.available());
  // String block = Serial2.readStringUntil('\n');
  // block.trim();
  // char blockType = block.charAt(0);

  switch (sensedColor) {
    case 'y': hits = 3; break;
    case 'r': hits = 5;  break;
    case 'b': hits = 10;  break;
    default:
      Serial2.println("Invalid block type.");
      return;
  }
  Serial2.println("Mining...");
    for (int i = 0; i < hits; i++) {
    unsigned long startTime = millis();  // mark start of hit

    myServo3.write(-30);
    delay(hitTime);
    myServo3.write(30);
    delay(hitTime);

    // unsigned long elapsed = millis() - startTime;  // total hit duration
    // Serial2.print("Hit #");
    // Serial2.print(i + 1);
    // Serial2.print(" took ");
    // Serial2.print(elapsed);
    // Serial2.println(" ms");
  }

  myServo3.write(0); // stop in neutral
  Serial2.println("Mining complete.");
}
