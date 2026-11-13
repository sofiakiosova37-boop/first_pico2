#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

struct GpsData {
  double lat, lng, alt;
  uint8_t sats;
  bool valid;
};

void gpsInit();
void gpsUpdate();          
GpsData gpsGet();

#endif