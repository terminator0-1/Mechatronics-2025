void goToTable() {
  // block count is 3
  straightTrajectory(-5,1);
  
  spinTrajectory(95, 1);

  countLines(1,100);

  straightTrajectory(4,.4);

  spinTrajectory(95, 1);

  followLine(false,200);

}
