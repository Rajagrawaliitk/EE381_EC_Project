#include <Servo.h>
#include <SoftwareSerial.h>
 
const int voltagePin = A0;
const int airQualityPin = A6;
const int buzzerPin = 7; 
const int servoPin = 8;
const int WifiPin = 6;
int flag = 1;
int val=1;
int aprev = 1;
int anew = 1;
int bprev = 1;
int bnew = 1;
Servo servoMotor; 
SoftwareSerial bt(0, 1); 
 
 
void run();
 
void setup() {
  
  Serial.begin(9600); 
  bt.begin(9600);     
  pinMode(buzzerPin, OUTPUT); 
  servoMotor.attach(servoPin); 
  servoMotor.write(0);
}
 
void loop() {
  if(flag == 0)
  val = 0;
  if(val  == 0){
  run();
  }
  else if(val == 1){
  servoMotor.write(0);
  }
  else if(val == 2){
  servoMotor.write(150);
  }
  else if(val == 3){
  servoMotor.write(150);
  }
  else if(val == 4){
  servoMotor.write(0);
  }
  else if(val == 5){
  servoMotor.write(0);
  }
  else if(val == 6){
  servoMotor.write(150);
  }
  else if(val == 7){
   servoMotor.write(0);
  }
  else if(val == 8){
  servoMotor.write(150);
  }
 
 
  // Bluetooth communication
  if (bt.available()) {
    char command = bt.read();
    
    if (command == '0' && flag) {
      aprev = anew;
      anew = 0;
      if(aprev == anew)
      ;
      else if(bnew == 1)
      val = 3;
      else if( bnew == 0)
      val = 8;
    }
    if(command=='1' && flag ){
      aprev = anew;
      anew = 1;
      if(aprev == anew)
      ;
      else if(bnew == 1)
      val = 4;
      else if(bnew == 0);
      val = 7;
    }
    Serial.print("Received command: ");
    Serial.println(command);
  }
 
  int wifi_input = digitalRead(WifiPin);
  Serial.println(wifi_input);
  if (wifi_input == 0 && flag) {
 
     bprev = bnew;
      bnew = 0;
      if(bnew == bprev)
      ;
      else if(anew == 0)
      val = 6;
      else if (anew == 1)
      val = 2;
 
  }
  if(wifi_input==1 &&flag ){
    bprev = bnew;
    bnew = 1;
    if(bnew == bprev)
      ;
      else if(anew == 0)
      val = 5;
      else if (anew == 1)
      val = 1;
  }
 
  int airQualityValue = analogRead(airQualityPin);
  
  Serial.print("Air Quality: ");
  Serial.print(airQualityValue);
 
  int voltageSensorValue = analogRead(voltagePin);
  
  float voltage = voltageSensorValue * (5.0 / 1023.0);
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
 
  if (airQualityValue > 220 || voltage < 1.0) {
    flag=0;
    run();
  } else {
    digitalWrite(buzzerPin, LOW);
  }
 
  delay(1000); 
}
 
void run() {
  digitalWrite(buzzerPin, HIGH);
  servoMotor.write(150);
}
