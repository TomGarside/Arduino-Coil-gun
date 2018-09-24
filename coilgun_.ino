//Program controls a two stage coilgun with IR sensors 
//reports the times when the sensors are tripped
//along with aditional info calculated from results 
//By Thomas Garside 2017 

//Functions
int calibrate(int);
void printResults(int , int , int );

//Pins
int sensorOne = 0;
int sensorTwo = 1;
int coilOne = 3;
int coilTwo = 4;

//variables
int thresholdOne = 0;
int thresholdTwo = 0;
int startTime = 0;
int midTime = 0;
int endTime = 0;
int OFFSET = 10; 

void setup() {
  pinMode(coilOne,OUTPUT);
  pinMode(coilTwo,OUTPUT);
  Serial.begin(9600);
   
  // initialize gun
  Serial.println("\n\nCalibrating...");
  for(int e=1;e<6;e++){//allows reading from sensors to stabilize 
    delay(1000);
    Serial.print("...");
    Serial.print(6-e);
    
  }
  
  thresholdOne = calibrate(sensorOne);
  Serial.println("\nSensor One Calibrated:");
  Serial.println(thresholdOne);

  thresholdTwo = calibrate(sensorTwo);
  Serial.println("\nSensor Two Calibrated:");
  Serial.println(thresholdTwo);
  
  //fires coilgun and records times
  startTime = millis();
  digitalWrite(coilOne, HIGH);
  
  int sensone=analogRead(sensorOne);
  while ( sensone >= thresholdOne) {
    sensone=analogRead(sensorOne);
    
    }
  midTime = millis();
  digitalWrite(coilOne, LOW);
  digitalWrite(coilTwo, HIGH);
  
  
 int sensTwo=analogRead(sensorTwo);
  while ( sensTwo >= thresholdTwo) {
    sensTwo=analogRead(sensorTwo);
    
    }
    
  digitalWrite(coilTwo, LOW);
  endTime = millis();
 printResults(startTime, midTime, endTime);
}

void loop() {}

//Calibrates minimum value to trigger coil lowsest of 1000 readings - OFFSET
int calibrate(int sens) {
  int low = 0;
  for (int e = 0; e < 1000; e++) {
    int val = analogRead(sens);
    if (val < low){
    low = val;}
    return val-OFFSET;
  }
}
// Calculates results and prints on serial
void printResults(int startTime, int midTime, int endTime) {
  float mass = 0.008;//kg 
  float watts = 25;
  float distance =0.09 ;//m between sensor one and two 
  float Speed = distance/(float(endTime-midTime)/1000);
  float Kinetic = (mass/2)*Speed*Speed;
  float electric = watts*(float(endTime-startTime)/1000);
 
  
  Serial.print("\nStart time           : ");
  Serial.print(startTime);
  Serial.print(" ms");
  Serial.print("\nSensor one trip time : ");
  Serial.print(midTime);
  Serial.print(" ms");
  Serial.print("\nSensor two trip time : ");
  Serial.print(endTime);
  Serial.print(" ms");
  Serial.print("\nSpeed                : ");
  Serial.print(Speed);
  Serial.print(" m/s");
  Serial.print("\nKinetic energy       : ");
  Serial.print(Kinetic);
  Serial.print(" j");
  Serial.print("\nElectrical energy    : ");
  Serial.print(electric);
  Serial.print(" j");
  Serial.print("\n\nPlease reload then reset for another shot");
}



