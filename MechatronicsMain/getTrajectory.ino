void getTrajectory(double theta1_final, double theta2_final, float travelTime, char spinFlag, int m1backwardsFlag, int m2backwardsFlag) {

  // --- Timing variables ---
  double t = 0, t_old = 0, deltaT = 0, t0 = 0;
  unsigned long nowMicros, lastMicros;
  double print_time = 0;  // next print timestamp

  // --- Control parameters ---
  double KpTraj = 10.3;  // proportional gain
  double KiTraj = 0;     // Integral Gain
  double KdTraj = 2.3;   // Derivative Gain
  double alpha = 0.07;   // filter weight

  // --- Encoder and motor variables ---
  long counts1, counts2;
  int m1c = 0, m2c = 0;

  double theta1 = 0, theta1_old = 0, omega1 = 0;
  double theta2 = 0, theta2_old = 0, omega2 = 0;
  double omega1f = 0, omega2f = 0;

  double theta1_des = 0, theta2_des = 0;
  double omega1_des = 0, omega2_des = 0;
  double error1 = 0, error2 = 0, error1_old = 0, error2_old = 0;
  bool distNotMet = true;
  float V1m, V2m;

  // --- Initialize timing ---
  lastMicros = micros();
  t0 = lastMicros / 1000000.0;
  t_old = 0.0;

  Serial.println(F("--------------------------------------------------------------------------------------------"));
  Serial.println(F("t(s)\tΔt(s)\tθ1(rad)\tθ2(rad)\tθ1_des\tθ2_des\tθ1_fin\tθ2_fin\tω1\tω2\tV1m\tV2m\terr1\terr2"));
  Serial.println(F("--------------------------------------------------------------------------------------------"));

  Serial.print(0, 2);
  Serial.print('\t');
  Serial.print(deltaT, 4);
  Serial.print('\t');
  Serial.print(theta1, 3);
  Serial.print('\t');
  Serial.print(theta2, 3);
  Serial.print('\t');
  Serial.print(theta1_des, 3);
  Serial.print('\t');
  Serial.print(theta2_des, 3);
  Serial.print('\t');
  Serial.print(theta1_final, 3);
  Serial.print('\t');  // <-- Final target θ₁
  Serial.print(theta2_final, 3);
  Serial.print('\t');  // <-- Final target θ₂
  Serial.print(omega1f, 3);
  Serial.print('\t');
  Serial.print(omega2f, 3);
  Serial.print('\t');
  Serial.print(V1m, 2);
  Serial.print('\t');
  Serial.print(V2m, 2);
  Serial.print('\t');
  Serial.print(error1, 3);
  Serial.print('\t');
  Serial.println(error2, 3);



  while (distNotMet) {
    // --- Compute time step ---
    nowMicros = micros();
    deltaT = (nowMicros - lastMicros) / 1000000.0;
    if (deltaT <= 0) deltaT = 0.0001;
    lastMicros = nowMicros;

    t = (nowMicros / 1000000.0) - t0;

    // --- Read encoders ---
    // Forward is positive for both of the encoders.
    counts1 = myEnc1.read();
    counts2 = myEnc2.read();

    // --- Compute angles and velocities ---
    theta1 = (counts1 * (PI * 2)) / (countsPerRev * GearRatio);
    theta2 = (counts2 * (PI * 2)) / (countsPerRev * GearRatio);

    omega1 = (theta1 - theta1_old) / deltaT;
    omega2 = (theta2 - theta2_old) / deltaT;

    omega1f = alpha * omega1 + (1 - alpha) * omega1f;
    omega2f = alpha * omega2 + (1 - alpha) * omega2f;

    // --- Desired motion profile ---
    omega1_des = fabs(theta1_final / travelTime);
    omega2_des = fabs(theta2_final / travelTime);

    if (theta1_final >= 0) {
      if (theta1_des < theta1_final)
        theta1_des += omega1_des * deltaT;
    } else {
      if (theta1_des > theta1_final)
        theta1_des -= omega1_des * deltaT;
    }

    // --- Increment theta2_des ---
    if (theta2_final >= 0) {
      if (theta2_des < theta2_final)
        theta2_des += omega2_des * deltaT;
    } else {
      if (theta2_des > theta2_final) {
        theta2_des -= omega2_des * deltaT;
      }
    }
    if ((theta1_final >= 0 ? theta1_des >= theta1_final : theta1_des <= theta1_final) && (theta2_final >= 0 ? theta2_des >= theta2_final : theta2_des <= theta2_final)) {
      distNotMet = false;
      Serial1.println("Reached Target ✓");
    }

    // --- Control law ---
    error1 = abs(theta1_des - theta1);
    error2 = abs(theta2_des - theta2);

    float derivative1 = (error1 - error1_old) / deltaT;
    float derivative2 = (error2 - error2_old) / deltaT;
    
    V1m = (KpTraj * error1)  * m1backwardsFlag;
    V2m = (KpTraj * error2)  * m2backwardsFlag;
    // V1m = ((KpTraj * error1) + (KiTraj*error1*deltaT) + (KdTraj*((error1 - error1_old)/deltaT))) * m1backwardsFlag;
    // V2m = ((KpTraj * error2) + (KiTraj*error2*deltaT) + (KdTraj*((error2 - error2_old)/deltaT))) * m2backwardsFlag;

    V1m = constrain(V1m, -10, 10);
    V2m = constrain(V2m, -10, 10);

    m1c = 400 * V1m / 10;
    m2c = 400 * V2m / 10;

    md.setSpeeds(m1c, m2c);

    // --- Print every 0.25 s ---
    // --- Print every 0.25 s ---
    // --- Print every 0.25 s ---
    if (t - print_time > 0.25) {
      // Serial.print(t, 2);
      // Serial.print('\t');
      // Serial.print(deltaT, 4);
      // Serial.print('\t');
      // Serial.print(theta1, 3);
      // Serial.print('\t');
       Serial.println(counts2, 3);
       //Serial.print('\t');
      // Serial.print(theta1_des, 3);
      // Serial.print('\t');
      // Serial.print(theta2_des, 3);
      // Serial.print('\t');
      // Serial.print(theta1_final, 3);
      // Serial.print('\t');  // <-- Final target θ₁
      // Serial.print(theta2_final, 3);
      // Serial.print('\t');  // <-- Final target θ₂
      // Serial.print(omega1f, 3);
      // Serial.print('\t');
      // Serial.print(omega2f, 3);
      // Serial.print('\t');
      // Serial.print(V1m, 2);
      // Serial.print('\t');
      // Serial.print(V2m, 2);
      // Serial.print('\t');
      // Serial.print(error1, 3);
      // Serial.print('\t');
      // Serial.println(error2, 3);  // newline
      print_time = t;
    }
    // --- Update previous states ---
    error1_old = error1;
    error2_old = error2;
    theta1_old = theta1;
    theta2_old = theta2;
    t_old = t;
  }
  spinFlag = 'n';
  md.setSpeeds(0, 0);

  myEnc1.write(0);
  myEnc2.write(0);
}
