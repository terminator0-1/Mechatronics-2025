void killSilverfish(char sword) {
  
  switch (sword) {
    // Assume wood sword
    case 'w':
      int hits = 10;
      break;
  }
  Serial2.println("Killing Silverfish...");
    for (int i = 0; i < 10; i++) {
    myServo3.write(-60);
    delay(100);
    myServo3.write(60);
    delay(100);
  }
  myServo3.write(0);
}
