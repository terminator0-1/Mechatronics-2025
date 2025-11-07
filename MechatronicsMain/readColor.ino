// --- Read average pulse for one color filter ---
float readColoNRrequency(int s2State, int s3State) {
  digitalWrite(s2, s2State);
  digitalWrite(s3, s3State);
  delay(10);
  long totalPulse = 0;
  for (int i = 0; i < numSamples; i++) {
    totalPulse += pulseIn(readPin, LOW) + pulseIn(readPin, HIGH);
  }
  return totalPulse / (2.0 * numSamples);
}

// --- Compute normalized RGB values (colored / clear) ---
void getNormalized(float &NR, float &NG, float &NB, float &C) {
  float R = 1 / readColoNRrequency(LOW, LOW);
  float B = 1 / readColoNRrequency(LOW, HIGH);
  float G = 1 / readColoNRrequency(HIGH, HIGH);
  C = 1 / readColoNRrequency(HIGH, LOW);

  NR = R / C;
  NG = G / C;
  NB = B / C;
}
// --- Main logic function: read + filter + classify ---
void readColorSensor(int s2, int s3, int readPin) {
  bool scanColor = true;
  unsigned long lastCheck = millis();
  int startTime = 3000;
  while (scanColor) {
    digitalWrite(LEDPin, HIGH);  //turn on LED
    float NR, NG, NB, C;
    getNormalized(NR, NG, NB, C);

    Serial.print(NR);
    Serial.print('\t');
    Serial.print(NG);
    Serial.print('\t');
    Serial.println(NB);

    if (millis() - lastCheck > startTime) {
      // --- RED Block ---
      if ((NR >= 0.5 && NR <= 0.7) && (NG >= 0.0 && NG <= 0.3) && (NB >= 0.0 && NB <= 0.3)) {

        Serial2.println("Red Block Sensed");
        scanColor = false;
        mineServo('r');
      }

      // --- BLUE Block ---
      else if ((NR >= 0.0 && NR <= 0.2) && (NG >= 0.2 && NG <= 0.4) && (NB >= 0.5 && NB <= 0.9)) {

        Serial2.println("Blue Block Sensed");
        scanColor = false;
        mineServo('b');
      }

      // --- OTHERWISE YELLOW ---
      else if ((NR > 0.7) && (NG > 0.6)){
        Serial2.println("Yellow Block Sensed");
        scanColor = false;
        mineServo('y');
      }
    }
  }
  digitalWrite(LEDPin, LOW);
}
