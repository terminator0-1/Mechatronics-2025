void dispenceBlock(){
// Assume driving up to table

// md.setSpeeds(100,100);
// readWall(4.5);

// The robot is ready to extend
moveArmU();
//Drop block and return.
delay(500);
myServo1.write(180);
delay(300);
myServo1.write(0);
moveArmD();

// Sequence finished.
}
