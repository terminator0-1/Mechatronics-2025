void moveArmU(){
   armMotor.forward();
  //  bool armNotHome = true;
  //  while (armNotHome){
  //    if (digitalRead(dropSwitch) == HIGH){
  //   armMotor.stop();
  //   armNotHome = false;
  //   }
  // }
   delay(1500);
   armMotor.stop();
}
