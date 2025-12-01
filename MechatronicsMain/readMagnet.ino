// Function for reading magnet -- returns a true or false flag.
bool readMagnet(float startValue, int collected) {
  bool magRead = true;
  bool killedSilverFish = false;
  unsigned long startTime = millis();  // time when the function started

  while (magRead) {
    float nowValue = analogRead(magPin) * (5.0 / 1023.0);
    float nowValue2 = analogRead(magPin2) * (5.0 / 1023.0);

    Serial.println(abs(startValue - nowValue));
    Serial.print('\t');
    // Serial.println(abs(startValue - nowValue2));

    float diff1 = abs(startValue - nowValue);
    float diff2 = abs(startValue - nowValue2);
    

    // Detect sudden change in magnetic field
    if(collected > 0){
       if (diff1 >= .95 && diff1 <= 1.25) {
        magRead = false;
        // We are in the collect block position.
        delay(500);
        straightTrajectory(4, .75);
        killSilverfish('w');  // This would need to be known from the mag sense func and passed in.
        killedSilverFish = true;
        Serial.println("SilverFish Detected...");
        break;
      }
    } else if (collected == 0){
       if ((diff1 >= .95 && diff1 <= 1.25) || (diff2 >= .95 && diff2 <= 1.25)){
        magRead = false;
        // We are in the collect block position.
        delay(500);
        straightTrajectory(4, .75);
        killSilverfish('w');  // This would need to be known from the mag sense func and passed in.
        killedSilverFish = true;
        Serial.println("SilverFish Detected...");
        break;
      }
    }
    // ---- TIMEOUT: 5 seconds ---- -- might remove this if two mag sensors work okay.
    if (millis() - startTime >= 1500) {
      Serial.println("Magnet timeout reached (5s).");
      magRead = false;
      break;
    }
    // Debug print
  }
  return killedSilverFish;
}
