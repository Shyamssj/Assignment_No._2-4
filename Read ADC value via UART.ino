// Define analog input pins
const int pinA0 = A0;
const int pinA1 = A1;
const int pinA2 = A2;
const int pinA3 = A3;

// Define variables for storing ADC values
int valueA0 = 0;
int valueA1 = 0;
int valueA2 = 0;
int valueA3 = 0;

// Define default sampling speed
int samplingSpeed = 100; // Default sampling speed is 100ms

void setup() {
  // Initialize UART communication
  Serial.begin(9600);

  // Set analog input pins as input
  pinMode(pinA0, INPUT);
  pinMode(pinA1, INPUT);
  pinMode(pinA2, INPUT);
  pinMode(pinA3, INPUT);
}

void loop() {
  // Read ADC values of analog input pins
  valueA0 = analogRead(pinA0);
  valueA1 = analogRead(pinA1);
  valueA2 = analogRead(pinA2);
  valueA3 = analogRead(pinA3);

  // Transmit ADC values via UART communication
  Serial.print("ADC Values: ");
  Serial.print(valueA0);
  Serial.print(",");
  Serial.print(valueA1);
  Serial.print(",");
  Serial.print(valueA2);
  Serial.print(",");
  Serial.println(valueA3);

  // Delay for the sampling speed
  delay(samplingSpeed);
  
  // Check for UART commands
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case '1':
        samplingSpeed = 10;
        break;
      case '2':
        samplingSpeed = 100;
        break;
      default:
        break;
    }
  }
}
