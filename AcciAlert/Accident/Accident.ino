#include <TinyGPSPlus.h>

#include <WiFi.h>

#include "Wire.h"

#include <MPU6050_light.h>

MPU6050 mpu(Wire);

#define rxPin 16

#define txPin 17

long timer = 0;

int crash = 23;

int vib = 19;

int ledPin = 5;

int push_bottom = 15;

const char* ssid = "SKMOWA_96"; //Wi-Fi SSID

const char* password = "srujan123"; // your WiFi Password

//String vehicleno = "Ba1pa4887"; //user defined vehicle ID

HardwareSerial neogps(1);

TinyGPSPlus gps;

int val = digitalRead(crash);

int vibval = digitalRead(vib);

void setup()

{

  Serial.begin(115200);

  Serial.println("esp32 serial initialize");

  neogps.begin(9600, SERIAL_8N1, rxPin, txPin);

  Serial.println("neogps serial initialize");

  delay(1000);

  WiFi.begin(ssid, password);

  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.print("Connected to WiFi network with IP Address: ");

  Serial.println(WiFi.localIP());

  Wire.begin();

  byte status = mpu.begin();

  Serial.print(F("MPU6050 status: "));

  Serial.println(status);

  while (status != 0) { }    // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));

  delay(100);

  mpu.calcOffsets(true, true); // gyro and accelero

  Serial.println("Done!\n");

  pinMode(crash, INPUT);

  pinMode(vib, INPUT);

}

void loop()

{

  mpu.update();

  int val = digitalRead(crash);

  int vibval = digitalRead(vib);

  int Push_button_state = digitalRead(push_bottom);

  if (WiFi.status() == WL_CONNECTED)

  {

    if (millis() - timer > 1000) // print data every second

    {

      float x = mpu.getAccAngleX();

      float y = mpu.getAccAngleY();

      //float Z = mpu.getAccAngleZ();

// data should use by your own experiment. It's our raw data of MPU 6050

      if ( x >160.00 && y < -50.00 && vibval == 0)

      {

        Serial.println(1);


      }

        //  Serial.println(x,y,z);
    }

  }

}






