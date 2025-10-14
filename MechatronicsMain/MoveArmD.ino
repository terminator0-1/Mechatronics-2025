void moveArmD(){
  armMotor.backward();
   //   bool armNotHome = true;
   //   while (armNotHome){
   //      if (digitalRead(homeSwitch) == HIGH){
   //     armMotor.stop();
   //     armNotHome = false;
   //      }
   //   }
   delay(1500);
   armMotor.stop();
  }
   
