#ifndef MPU_H
#define MPU_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

struct MpuData {
  float ax, ay, az;  // for acceleration
  float gx, gy, gz;  // angular velocity
};

bool mpuInit();
bool mpuRead(MpuData &data);

#endif // MPU_H 
