void orient() {

  spinTrajectory(-30,.5);
  delay(100);
  straightTrajectory(10,.5);
  delay(100);
  spinTrajectory(30,.5);
  delay(100);
  md.setSpeeds(150, 150);

  Serial2.println("Done Orienting");
}
