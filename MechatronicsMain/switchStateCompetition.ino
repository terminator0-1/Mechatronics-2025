void switchStateCompetition(){
  
  // Take input from UNO
  if (Serial1.available()) {

    String dataString = Serial1.readStringUntil('\n');
    dataString.trim();
    
    if (dataString.length() <= 7) {  // Check to ensure reset string is correct.
      char blocktype = dataString.charAt(0); // current block type being mined.
      String cellStatus = dataString.substring(2, 5);  // status of each cell in case one was missed.
      char pickType = dataString.charAt(6);

      // Serial Communication Update
      switch (blocktype) {
          driveForward(M, M);
          Serial.println("Driving Forward...");
          break;
        case 's':
          driveBackward(M);
          Serial.println("Driving Backward...");
          break
        case 'i':
          turnLeft(M);
          Serial.println("Turning Left...");
          break;
        case 'd':
          turnRight(M);
          Serial.println("Turning Right...");
          break;
      }
    }
  }
}
} 
