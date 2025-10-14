void followLine(float dist) {
  while (following) {
    t = micros() / 1000000. - t0;
    qtr.read(sensorValues);  

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
    error = d0 - dComp;

    m1c = base_speed + Kp * error;
    m2c = base_speed - Kp * error;

    ////////// LINE FOLLOWING CODE
    driveForward(m1c,m2c);  // send motor commands

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
