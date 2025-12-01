void mineServo(int hits) {
  unsigned long hitTime = 150;

  for (int i = 0; i < hits; i++) {
    myServo3.write(-60);
    delay(hitTime);
    myServo3.write(60);
    delay(hitTime);
    Serial.println("Servo Hit");
  }
  myServo3.write(0);  // stop in neutral
  Serial2.println("Mining complete.");
}
