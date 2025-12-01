void dispenseWood(){
  moveArmU();
  delay(200);
  myServo1.write(180);
  delay(500);
  myServo1.write(0);
  moveArmD();
  md.setSpeeds(0, 0);
}
