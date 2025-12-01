void goToBlockTable(int rowDeposit) {

  switch (rowDeposit) {
    case 1:  // Far Row
      straightTrajectory(-1, .25);
      break;

    case 2:
      straightTrajectory(3, .25);
      break;

    case 3:
      straightTrajectory(-5, .25);
      break;
  }

  spinTrajectory(95, 1);

  countLines(1, 100);

  straightTrajectory(4, .4);

  spinTrajectory(95, 1);

  followLineMining(true, 250);
}
