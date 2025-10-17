void switchState() {
  if (Serial1.available()) {

    String dataString = Serial1.readStringUntil('\n');
    dataString.trim();
    
    if (dataString.length() == 1) {
      char Signal = dataString.charAt(0);
    
      Serial.println(Signal);
      switch (Signal) {
        case 'a':
          driveForward(M, M);
          Serial.println("Driving Forward...");
          break;

        case 'b':
          driveBackward(M);
          Serial.println("Driving Backward...");
          break;

        case 'l':
          turnLeft(M);
          Serial.println("Turning Left...");
          break;
        case 'r':
          turnRight(M);
          Serial.println("Turning Right...");
          break;
        case 'u':  // maybe shorthand for "craft"
          moveArmU();
          Serial.println("Moving Arm Up.");
          break;

        case 'd':
          moveArmD();
          Serial.println("Moving Arm Down.");
          break;
        case 's':
          myServo1.write(100);
          // myServo2.write(150);
          // myServo3.write(150);
          delay(250);
          myServo1.write(0);
          // myServo2.write(0);
          // myServo3.write(0);
          Serial.println("Servo Moved");
          break;
        case 'c':
          // Start LineFollowing
          followLine();
          break;
        case 'w':
          // Measure distance towards wall
          Serial.println("Hello");
          float dist = 20.0;
          driveForward(M,M);
          readWall(dist);
          break;
      }
    }
  }
}
