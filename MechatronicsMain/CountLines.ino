void countLines(int numToCount, const unsigned long stopDelay) {
  bool detected = false;
  const int blackThreshold = 2300;
  int countLines = 0;
  unsigned long detectTime = 0;

  // Set initial speed
  md.setSpeeds(175, 175);

  // Small delay to not read current line 
  delay(500);

  while (!detected) {
    // ----- Read sensors -----
    qtr.read(sensorValues);
    for (int i = 0; i < 8; i++) {
      Sensor_value_unbiased[i] = sensorValues[i] - sensor_bias[i];
    }

    // ----- Check if ANY sensor sees black -----
    bool isBlack = false;
    for (int i = 0; i < 8; i++) {
      if (Sensor_value_unbiased[i] > blackThreshold) {
        isBlack = true;
        break;
      }
    }

    // ----- Count rising edge -----
    if (isBlack) {
      countLines++;
      Serial.print("Detected Line #");
      Serial.println(countLines);

      if (countLines == numToCount) {
        detected = true;
        detectTime = millis();   // record moment of detection
      }
    }

    prevDetected = isBlack;

    // ----- After detecting the target line -----
    if (detected) {
      // keep moving until time has passed
      if (millis() - detectTime >= stopDelay) {
        md.setSpeeds(0, 0);
        return;
      }
    }
  }
}
