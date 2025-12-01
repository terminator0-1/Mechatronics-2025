void switchState() {
  if (Serial2.available()) {
    String dataString = Serial2.readStringUntil('\n');
    dataString.trim();
    if (dataString.length() <= 7) {
      char Signal = dataString.charAt(0);

      switch (Signal) {
        // Craft Stone Pick
        case 's':
          FullCompetitionCode(0);
          break;

          // Craft Iron Pick
        case 'i':
          FullCompetitionCode(1);
          break;

          // Keep Mining with iron pick, silverfish now a problem.
        case 'm':
          followLine(true, 200);
          while (1) {
            FullCompetitionCodeMining();
          }
          break;

          // Start Sequence Test.
        case 'f':
          followLine(true, 200);
          orient();
          goToTable();
        break;

        case 'g':
          correctMagnetBlock();
        break;
        // Magnet Test
        case 'h':
          bool test = true;
          while (test) {
            bool kick = readMagnet(2.0, 1);
            if (kick) {
              myServo1.write(90);
              delay(250);
              myServo1.write(0);
              test = false;
            }
          }
          break;
      }
    }
  }
}
