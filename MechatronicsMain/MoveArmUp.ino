void moveArmU(){
   armMotor.backward();
   bool armNotDrop = true;
   while (armNotDrop){
      Serial.println(digitalRead(dropSwitchPin));
      if (digitalRead(dropSwitchPin) == HIGH){
        armMotor.stop();
        armNotDrop = false;
        armMotor.forward();
        delay(100);
        armMotor.stop();
    }
  }
}
