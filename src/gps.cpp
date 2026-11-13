#include "gps.h"
#include "config.h"
#include <TinyGPSPlus.h>

static TinyGPSPlus parser;

void gpsInit() {
  GPS_SERIAL.setTX(GPS_TX_PIN);
  GPS_SERIAL.setRX(GPS_RX_PIN);
  GPS_SERIAL.begin(GPS_BAUD);
}

void gpsUpdate() {
  while (Serial1.available()) {
    parser.encode(Serial1.read());
  }
}

GpsData gpsGet() {
  GpsData d;
  d.valid = parser.location.isValid();
  d.lat   = parser.location.lat();
  d.lng   = parser.location.lng();
  d.alt   = parser.altitude.meters();
  d.sats  = parser.satellites.isValid() ? parser.satellites.value() : 0;
  return d;
}