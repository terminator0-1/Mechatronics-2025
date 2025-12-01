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
char readColor(int s2, int s3, int readPin) {
  bool scanColor = true;
  unsigned long timeStart = millis();
  unsigned long waitingInterval = 5000;  // 1.5 seconds timeout
  char sensedBlock = 'n';

  while (scanColor) {
    delay(50);
    digitalWrite(LEDPin, HIGH);

    float NR, NG, NB, C;
    getNormalized(NR, NG, NB, C);
    digitalWrite(LEDPin, LOW);

    // --- RED Block ---
    if ((NR >= 0.46 && NR <= 0.62) &&
        (NG >= 0.17 && NG <= 0.29) &&
        (NB >= 0.22 && NB <= 0.34)) {

      Serial2.println("Red Block Sensed");
      sensedBlock = 'i';
    }

    // --- BLUE Block ---
    else if ((NR >= 0.01 && NR <= 0.14) &&
             (NG >= 0.23 && NG <= 0.35) &&
             (NB >= 0.66 && NB <= 0.87)) {

      Serial2.println("Blue Block Sensed");
      sensedBlock = 'd';
    }

    // --- YELLOW Block ---
    else if ((NR >= 0.24 && NR <= 0.44) &&
             (NG >= 0.30 && NG <= 0.57) &&
             (NB >= 0.21 && NB <= 0.34)) {

      Serial2.println("Yellow Block Sensed");
      sensedBlock = 's';
    }

    // ---------------- EXIT CONDITIONS ----------------

    // If block sensed → stop scanning
    if (sensedBlock != 'n') {
      scanColor = false;
    }

    // TIMEOUT: no block detected in time
    else if (millis() - timeStart >= waitingInterval) {
      Serial2.println("Color Timeout → Backing up");
      straightTrajectory(-1.5, 0.25);   // backup a little
    }
  }

  return sensedBlock;
}
