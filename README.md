# Arduino Sensor Data to Firebase

This Arduino sketch is designed to read sensor data from current and voltage sensors, process the data, and send it to a Firebase Realtime Database using an ESP8266 module. The project consists of the following components:

## Sensor Data Processing (Arduino)
1. **Overview**
   - Reads analog sensor data from current and voltage sensors.
   - Utilizes the `Filters` library for signal processing.
   - Calculates estimated actual current and voltage in amps and volts (A_TRMS and V_TRMS).
   - Sends processed data over the serial port.

2. **Serial Communication**
   - Specifies a byte sequence for framing serial data.
   - Sends sensor data over the serial port.

### Dependencies
- [Filters Library](https://drive.google.com/file/d/1-GQQesQHAufSZpxUi2r6uiLyXSlk8Npp/view?usp=sharing)

### Usage
1. Install the required `Filters` library in your Arduino IDE.
2. Upload the sketch to your Arduino board.
3. Connect current and voltage sensors to the defined pins.
4. Monitor processed data through the serial port.

### Configuration
- Adjust sensor pins and calibration parameters in the code if needed.

## ESP8266 Data Upload to Firebase
1. **Overview**
   - Listens for incoming serial data from the Arduino.
   - Parses the data to extract voltage and current values.
   - Uploads the parsed data to a Firebase Realtime Database.

2. **Firebase Configuration**
   - Specifies the Firebase Realtime Database URL.
   - Defines Wi-Fi credentials for ESP8266.

### Dependencies
- [ESP8266WiFi Library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [ESP8266Firebase Library](https://github.com/mobizt/Firebase-ESP8266)
- [ArduinoJson Library](https://arduinojson.org/)

### Usage
1. Install the required libraries in your Arduino IDE.
2. Upload the sketch to your ESP8266 board.
3. Connect the ESP8266 to your Wi-Fi network.
4. Monitor data uploading to Firebase through the serial port.

### Configuration
- Set the Firebase Realtime Database URL and Wi-Fi credentials.
- Adjust the interval and other parameters as needed.

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
- The code uses the `Filters` library for signal processing.

