#define photoR A0
#define boutton A1
#define laser A2


#define SER_Pin 8
#define RCLK_Pin 9
#define SRCLK_Pin 10


#define numOfRegisterPins 1 * 8
 
boolean registers[numOfRegisterPins];

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 
void writeAllHigh(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = HIGH;
  }
  writeRegisters();
} 
//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){
 
  digitalWrite(RCLK_Pin, LOW);
 
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
 
    int val = registers[i];
 
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
 
  }
  digitalWrite(RCLK_Pin, HIGH);
 
}
 
//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}

void setup() {
  pinMode(photoR,INPUT);  
  pinMode(boutton,INPUT); 
  pinMode(laser,OUTPUT);
  digitalWrite(laser,LOW);
  Serial.begin(9600);
  Serial.println("Initialisation...");
  
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
 
  //reset all register pins
  clearRegisters();
  writeRegisters();

  
  delay(2000);

  //COUNTDOWN BEFORE GAME STARTS
  setRegisterPin(0,HIGH);
  setRegisterPin(1,HIGH);
  setRegisterPin(3,HIGH);
  setRegisterPin(4,HIGH);
  setRegisterPin(5,HIGH);
  writeRegisters();
  Serial.println("Début dans 5...");
  delay(1000);
  setRegisterPin(5,LOW);
  writeRegisters();
  Serial.println("4...");
  delay(1000);
  setRegisterPin(4,LOW);
  writeRegisters();
  Serial.println("3...");
  delay(1000);
  setRegisterPin(3,LOW);
  writeRegisters();
  Serial.println("2...");
  delay(1000);
  setRegisterPin(1,LOW);
  writeRegisters();
  Serial.println("1...");
  delay(1000);
  setRegisterPin(0,LOW);
  writeRegisters();
  Serial.println("GO !");
  writeAllHigh();
  delay(200);
  clearRegisters();
  writeRegisters();
}

int nbTouched;
long lastTimeTouched;
void loop() {
  if (digitalRead(boutton)) {
    digitalWrite(laser,HIGH);
  } else {
    digitalWrite(laser,LOW);
  }
  if (analogRead(photoR)<300 && (millis() - lastTimeTouched) > 3000) {
    Serial.println("je suis touché");
    nbTouched++;
    writeAllHigh();
    delay(200);
    clearRegisters();
    writeRegisters();
    delay(200);
    writeAllHigh();
    delay(200);
    clearRegisters();
    writeRegisters();
    delay(200);
    printScore(nbTouched);
    lastTimeTouched = millis();
  }
}

void printScore(int score){
  clearRegisters();
  if(score <3){
    setRegisterPin(score-1,HIGH);
  }else{
    setRegisterPin(score,HIGH);
  }
  writeRegisters();
}
