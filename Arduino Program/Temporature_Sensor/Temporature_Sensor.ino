const int bigNTCsensor = A0;
const int knownResistor = 10000; // 10KΩ known resistor value
const float Vin = 5.0; // Assuming 5V reference voltage for the Arduino
#define A 0.001125308852122
#define B 0.000234711863267
#define C 0.000000085663516
#define   M_E   2.7182818284590452354

void setup() {
  Serial.begin(9600);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
}

void loop() {
  float sensorValue = analogRead(bigNTCsensor);
  double voltage = sensorValue * (Vin / 1023.0); // Convert analog value to voltage
  double resistance = (knownResistor * voltage) / (Vin - voltage); // Calculate the resistance value
  float R = log(resistance)/log(M_E);
  float Temp = (0.001125308852122 + 0.000234711863267*R + 0.000000085663516*R*R*R);
  Temp = 1/Temp;
  Temp = Temp - 273.15;
  

  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.println(" Ohms");
  Serial.print("Temperaure: ");
  Serial.print(Temp);
  Serial.println(" Celcius");

  if(Temp>50){
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    }
  else if(Temp<40){
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    }
  else{
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    }

  delay(1000);
}
