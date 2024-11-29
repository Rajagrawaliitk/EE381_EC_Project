#include<SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial bt(1,0);
// Define the analog pins for voltage and air quality measurements, buzzer pin, and servo pin
const int voltagePin = A0;
const int airQualityPin = A6;
const int buzzerPin = 7; // Connect the buzzer to digital pin 7 (D7)
const int servoPin = 8;

Servo servoMotor; // Create a servo object

// Function prototype
void run();
void sendATCommand(String command);

void setup() {
  //bt.begin(9600);
  Serial.begin(9600); // Initialize serial communication;/bt.begin(9600);
   pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  servoMotor.attach(servoPin); // Attach servo to its pin
  servoMotor.write(0);
  //sendATCommand("AT+NAME?\r\n");
}

void loop() {
  // Check if there's any data available from Bluetooth module
  if (bt.available() > 0) {
    char command = bt.read(); // Read the incoming command
    if (command == '0') {
      // If command is '1', call the run function

      //run();
    }
  }

  // Read the air quality from the analog pin
  int airQualityValue = analogRead(airQualityPin);
  
  // Print air quality to Serial Monitor
  Serial.print("Air Quality: ");
  Serial.print(airQualityValue);
  Serial.println(" PPM");

  // Read the voltage from the analog pin
  int voltageSensorValue = analogRead(voltagePin);
  
  // Convert the sensor value to voltage (assuming 5V reference)
  float voltage = voltageSensorValue * (5.0 / 1023.0);
  
  // Print the voltage to the Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Check if PPM is greater than 250 or voltage is less than 2V
  if (airQualityValue > 250 || voltage < 1.0) {
    // Call the run function
    run();
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
    // Rotate the servo motor to 0 degrees
    //servoMotor.write(0);
  }

  delay(1000); // Delay for 1 second before reading again
}

// Function to execute the code inside the if condition
void run() {
  // Activate the buzzer
  Serial.print("I am here");
  digitalWrite(buzzerPin, HIGH);
  // Rotate the servo motor to 150 degrees
  servoMotor.write(150);
}

void sendATCommand(String command) {
  bt.print(command);
  delay(500); // Wait for the module to respond
  while (bt.available()) {
    char c = bt.read();
    Serial.print(c); // Print response to serial monitor
  }
  Serial.println(); // Add a new line after the response
}