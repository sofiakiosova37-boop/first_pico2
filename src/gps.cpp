#include "gps.h"
#include "config.h"
#include <TinyGPSPlus.h>

static TinyGPSPlus parser;

void gpsInit() {
  GPS_SERIAL.setTX(GPS_TX_PIN);
  GPS_SERIAL.setRX(GPS_RX_PIN);
  GPS_SERIAL.setFIFOSize(256);
  GPS_SERIAL.begin(GPS_BAUD);
}

void gpsUpdate() {
  while (GPS_SERIAL.available()) {
    parser.encode(GPS_SERIAL.read());
  }
}

GpsData gpsGet() {
  GpsData d;
  d.valid = parser.location.isValid() && parser.location.age() < 2000;;
  d.lat   = d.valid ? parser.location.lat() : 0.0;
  d.lng   = d.valid ? parser.location.lng() : 0.0;
  d.alt   = (parser.altitude.isValid() && parser.altitude.age() < 2000)
              ? parser.altitude.meters() : 0.0;
  d.sats  = parser.satellites.isValid() ? parser.satellites.value() : 0;
  return d;
}