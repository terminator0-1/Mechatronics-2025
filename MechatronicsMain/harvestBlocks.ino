void harvestBlock(){
// Placed infront of pillar 
readColorSensor(s2, s3, readPin);

// Once Block has been mined, move into position.
straightTrajectory(-2.5,.25);
// Move back in place

// Once it has moved back into place we will delay for 1 second to wait
//senseMagnetic();
delay(2000);

// Move Servo over
myServo2.write(70);
delay(200);
myServo2.write(0);

// Block should now be collected and moved to the right. 
// blockCount += 1;
}
