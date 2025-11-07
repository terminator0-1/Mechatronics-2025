void switchState() {


  if (Serial2.available()) {
    String dataString = Serial2.readStringUntil('\n');
    dataString.trim();
    if (dataString.length() <= 7) {
      char Signal = dataString.charAt(0);

      switch (Signal) {
        case 'u':
          moveArmU();
          break;
        case 'd':
          moveArmD();
          break;
        case 'r':
          harvestBlock();
          // Serial2.println("Sensed block: Iron");
          break;
        case 'm':
          dispenceBlock();
          break;
        case 'w':
          readWall(15.0);
          break;
        case 's':
          myServo1.write(180);
          delay(500);
          myServo1.write(0);
        case 'x':
          // Stop Driving Motors
          md.setSpeeds(0, 0);
          // Stop Arm Motor
          armMotor.stop();
          // Set servos to 0.
          myServo1.write(0);
          myServo2.write(0);
          myServo3.write(0);
          //set defaultState = true;
          break;
      }
    }
  }
}
