#include <Arduino.h>
#include "config.h"
#include "mpu.h"
#include "gps.h" 

static bool mpuOk = false;

void setup() {
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  Serial.begin(SERIAL_BAUD);
  while (!Serial && millis() < 3000) {}  // monitor connection

  mpuOk = mpuInit();
  if (!mpuOk) Serial.println("MPU6050 not found! Check connection.");
  gpsInit();
  Serial.println("ms,ax,ay,az,gx,gy,gz,lat,lng,alt,sats");
}

void loop() {
  gpsUpdate();
  uint32_t now = millis();
  static uint32_t last = 0;
  if (!mpuOk) {
    if (now - last >= 2000) {
      last = now;
      mpuOk = mpuInit();
      if (mpuOk) {
        Serial.println("MPU6050 reconnected!");
      }
    }
  }

  static uint32_t lastMpuTime = 0;
  if (now - lastMpuTime < MPU_PERIOD_MS) return;
  lastMpuTime = now;

  MpuData d= {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  if (mpuOk) {
    mpuRead(d);
  }
  GpsData g = gpsGet();

  Serial.print(now);       Serial.print(',');
  Serial.print(d.ax, 3);   Serial.print(',');
  Serial.print(d.ay, 3);   Serial.print(',');
  Serial.print(d.az, 3);   Serial.print(',');
  Serial.print(d.gx, 2);   Serial.print(',');    
  Serial.print(d.gy, 2);   Serial.print(',');
  Serial.print(d.gz, 2);   Serial.print(',');
  Serial.print(g.lat, 6);  Serial.print(',');
  Serial.print(g.lng, 6);  Serial.print(',');
  Serial.print(g.alt, 1);  Serial.print(',');
  Serial.println(g.sats);
    }