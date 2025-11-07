void readMagnet() {
  bool magRead = true;
  float sum = 0.0;
  float prevAvg = 0.0;
  unsigned long lastCheck = millis();

  while (magRead) {
    // Take 10 readings and average
    sum = 0.0;
    for (byte i = 0; i < 10; i++) {
      sum += analogRead(magPin) * (5.0 / 1023.0);
      delay(10);  // small delay for stable sampling
    }

    float avgValue = sum / 10.0;
    Serial.println("Wait..");
    // Compare to previous average after first sample
    if (avgValue > 2.52 || avgValue < 2.4) {
      magRead = false;
      Serial.println("SilverFish Detected...");
    } else {
      prevAvg = analogRead(magPin) * (5.0 / 1023.0);
    }
    // Optional: timeout after 2 seconds to prevent infinite loop
    if (millis() - lastCheck > 500) {
      break;
    }
    //Serial.println(avgValue);
  }
}
