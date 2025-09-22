String Miningstate = "";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

if(Serial.available() > 1){
    String dataString = Serial.readStringUntil("\n");
    // Read each data segment
    char blocktype = dataString.charAt(0);
    String cellStatus = dataString.substring(2,5);
    char pickType = dataString.charAt(6);
    Serial.println(blocktype);
    Serial.println(cellStatus);
    Serial.println(pickType);
    
  switch (blocktype){
    case 'w':
    // Drive to wood pillar
    Miningstate = "wood";
    break;
    case 's':
    // Drive to stone pillar
    Miningstate = "stone";
    break;
    case 'i':
    // Drive to stone/iron pillar
    Miningstate = "iron";
    break;
    case 'd':
    // Drive to stone/iron pillar
    Miningstate = "diamonds";
    break;
    case 'c':
    // Drive to last pillar closest to chest
    Miningstate = "craft";
    break;
    default: 
    Miningstate = "wood";
    break;
    delay(1000);
  }
}else{
}
}
