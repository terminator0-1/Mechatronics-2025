void moveArmD(){
  armMotor.forward();
     bool armNotHome = true;
     while (armNotHome){
      Serial.println(digitalRead(homeSwitchPin));
        if (digitalRead(homeSwitchPin) == HIGH){
         armMotor.stop();
         armNotHome = false;
        }
     }
  }
   
