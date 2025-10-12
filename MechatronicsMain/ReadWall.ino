1. V = analogRead(IRpin);

2. d_cm = voltage_linear_regression(V); ----> get values from MATLAB fit . Many datapoints of voltage at certain distances. 

3. d_filt = kalmanfilter(d_cm); 


4. To make a even better filter, we can recursively update R and Q based on the the recent varience between points. 

var(X) = sum(xi - sample_avg)^2 / N_samples - 1


We can also combine the moving average with the Kalman filter to ensure that spikes are covered and don't affect the Kalman filter.
structure:

void readWall(float dist, int M) {
  driveForward(M);
  bool running = true; 

  while (running) {
    float measured = analogRead(IRpin) * (300.0 / 1023.0);
    float filtered = kalmanFilter(measured);
    Serial.println(filtered,4);
    if (filtered < dist*1.05 & filtered > dist*0.99) {
      delay(20);
      running = false;
      md.setM1Speed(0);
      md.setM2Speed(0);
      Serial.println("Stoppinng");
    }
  }
}

5. After all is said and done. We need to compare the filtering results. We will compare the filtered_cm to the actual_cm, based on that line we will see what the maximum error is for our filtering and exactly where that occurs.
