void followLine() {
alpha = 0.7;
    double t, t_old, deltaT, print_time, t0d = 0;  // declare some time variables
  while (following) {
    t = micros() / 1000000. - t0;
    qtr.read(sensorValues);  
    deltaT = t-t_old; 
    for (int i = 0; i < 8; i++) {
      Sensor_value_unbiased[i] = sensorValues[i] - sensor_bias[i];
    }

    dTop = 0;
    dBottom = 0;
    for (int i = 0; i < 8; i++) {
      dTop = dTop + Sensor_value_unbiased[i] * d[i];
      dBottom = dBottom + Sensor_value_unbiased[i];
    }
    
    dComp = dTop / dBottom;
      
    error1 = d0 - dComp;
    error2 = dComp - d0;

    omega1f = alpha*omega1 + (1-alpha) * omega1f;
    omega2f = alpha*omega2 + (1-alpha) * omega2f;

    omega1_des = 0;
    omega2_des = 0;

    dErrordt1 = omega1_des - omega1f;
    dErrordt2 = omega2_des - omega2f;

    Kerror = (Kp * error) + (Ki * integralError) + Kd*dErrordt;
      
    V2 = basespeed + Kerror;
    V1 = basespeed - Kerror;

    //prevError = error; // PID Control

    ////////// LINE FOLLOWING CODE
    md.setM1Speed(V1);  // send motor commands
    md.setM2Speed(V2);

    // PRINT STATEMENTS
    // non-blocking way to delay printing
    if ((t - print_time) > 0.25) {

      // This for loop is used to print out variables that are arrays
      for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(Sensor_value_unbiased[i]);
        Serial.print('\t');
      }
      // Print any non-array variables here
      Serial.println(error);
      print_time = t;
    }
    // if (readWallLine(dist) == false){
    //   driveForward(0,0);
    //   following = false;
    //}
  }
}
