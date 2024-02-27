#include <Filters.h> //This library does a massive work check it's .cpp file

#define Current_sensor A0 //Sensor data pin on A0 analog input
#define Voltage_sensor A1 //Sensor data pin on A1 analog input

float Current_Value; //Here we keep the raw data values of current
float Voltage_Value; //Here we keep the raw data values of voltage
float testFrequency = 50;   // test signal frequency (Hz)
float windowLength = 40.0 / testFrequency;  // how long to average the signal, for statistics
float slope = 0.04965;  // to be adjusted based on calibration testing
float vslope = 0.7070;  // to be adjusted based on calibration testing
//Please check the ACS712 Tutorial video by SurtrTech to see how to get them because it depends on your sensor, or look below

float Amps_TRMS; // estimated actual current in amps
float V_TRMS; // estimated actual voltage in v
byte transdata[5];
byte initbyte = 0x77; //front byte
byte headerbyte = 0x01; //start byte
byte endbyte = 0x88; //end byte

RunningStatistics CurrentStats; // create Current statistics to look at the raw test signal
RunningStatistics VoltageStats; // create Voltage statistics to look at the raw test signal


unsigned long printPeriod = 1000; // in milliseconds
// Track time in milliseconds since last reading
unsigned long previousMillis = 0;

void sendDataToSerial() {
  transdata[0] = initbyte;
  transdata[1] = headerbyte;
  transdata[2] = V_TRMS;
  transdata[3] = Amps_TRMS;
  transdata[4] = initbyte;
  Serial.write(transdata, sizeof(transdata));
}

void readSensorData() {
  while (true) {
    Current_Value = analogRead(Current_sensor); // read the analog in value:
    CurrentStats.input(Current_Value); // log to Stats function

    Voltage_Value = analogRead(Voltage_sensor); // read the analog in value:
    VoltageStats.input(Voltage_Value); // log to Stats function

    //  Amps_TRMS = slope * CurrentStats.sigma();
    //  V_TRMS = vslope * VoltageStats.sigma();
    //  Serial.println(Amps_TRMS);
    //  Serial.println(V_TRMS);

    if ((unsigned long)(millis() - previousMillis) > printPeriod) { //every second we do the calculation
      previousMillis = millis(); // update time

      Amps_TRMS = slope * CurrentStats.sigma();
      V_TRMS = vslope * VoltageStats.sigma();
//      Serial.println(Amps_TRMS);
//      Serial.println(V_TRMS);
      sendDataToSerial();
    }
  }
}

void setup() {
  Serial.begin(9600); // Start the serial port
  pinMode(Current_sensor, INPUT); //Define the pin mode
  pinMode(Voltage_sensor, INPUT); //Define the pin mode
  CurrentStats.setWindowSecs( windowLength ); //Set the window length
  VoltageStats.setWindowSecs( windowLength ); //Set the window length
}

void loop() {
  readSensorData();
  //  if ((unsigned long)(millis() - previousMillis) > printPeriod) { //every second we do the calculation
  //    previousMillis = millis(); // update time
  //        readSensorData();
  //  sendDataToSerial();
  //}
}
