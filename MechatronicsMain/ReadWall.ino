void readWall(float dist) {
  bool distNotMet = true;
  float timerunning = millis();
  int timeStart = 2000;
  float filtereddist[9];
  while (distNotMet) {
    float filtereddist = distsensor.getDist();
    //float filtereddist2 = kalmanFilter(filtereddist, 0.5);
    float filtereddist3 = (0.02627 * filtereddist1) - 6.215;
    Serial.println(filtereddist3);
    if (filtereddist3< dist * 1.05 & filtereddist3 > dist * 0.99) {
      distNotMet = false;
      driveForward(0, 0);
      Serial.println("Stoppinng");
      timerunning = 0;
    }
  }
}
