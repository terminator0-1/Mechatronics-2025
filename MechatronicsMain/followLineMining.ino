void followLineMining(bool pillarFlag, float basespeed) {
  double t, print_time = 0;
  float dError, lasterror;
  unsigned long lastMotorUpdate = 0;
  bool following = true;
  unsigned long distStart = millis();
  int distDelay = 1000;

  // ---------------------------------------------------
  // FIX 1: Reset PID state so no giant first correction
  error = 0;
  lasterror = 0;
  dError = 0;

  // FIX 2: Clear prevDetected flag
  prevDetected = false;

  // FIX 3: Stabilize QTR before starting PID
  for (int k = 0; k < 10; k++) {
    qtr.read(sensorValues);
    for (int i = 0; i < 8; i++) {
      Sensor_value_unbiased[i] = sensorValues[i] - sensor_bias[i];
    }
    delay(2);
  }
  // ---------------------------------------------------

  while (following) {
    // --- Time update ---
    t = micros() / 1000000.0 - t0;

    // --- Read QTR sensors ---
    qtr.read(sensorValues);

    for (int i = 0; i < 8; i++) {
      Sensor_value_unbiased[i] = sensorValues[i] - sensor_bias[i];
    }

    // --- Compute weighted line position ---
    dTop = 0;
    dBottom = 0;

    for (int i = 0; i < 8; i++) {
      dTop += Sensor_value_unbiased[i] * d[i];
      dBottom += Sensor_value_unbiased[i];
    }

    // Compute Error
    dComp = dTop / dBottom;
    error = d0 - dComp;

    Serial.println(error);

    dError = error - lasterror;
    lasterror = error;

    // --- Compute motor commands ---
    int m1c = basespeed + (Kp * error + Kd * dError);
    int m2c = basespeed - (Kp * error + Kd * dError);
    md.setSpeeds(m1c, m2c);

    // Table Hit
    if (pillarFlag == false) {
      bool waitSwitch = true;
      while (waitSwitch) {
        if (digitalRead(hitSwitchPin) == 1) {
          Serial2.println("SWITCH HIT");
          md.setSpeeds(0, 0);
          straightTrajectory(-8, 2);
          Serial.println("Hit Switch Pressed → STOP");
          waitSwitch = false;
          following = false;
        }
      }
    }

    if ((millis() - distStart > distDelay) && (pillarFlag == true)) {
      md.setSpeeds(0, 0);
      delay(250);
      straightTrajectory(-15, 1.5);
      following = false;
      break;
    }
  }
}
