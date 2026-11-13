#include "mpu.h"
#include "config.h"
#include <Wire.h>

static MPU6050 mpu(MPU6050_ADDRESS_AD0_LOW, &MPU_I2C);

bool mpuInit() {
  // pins
  MPU_I2C.setSDA(MPU_SDA_PIN);
  MPU_I2C.setSCL(MPU_SCL_PIN);
  MPU_I2C.begin();
  MPU_I2C.setClock(MPU_I2C_CLOCK);

  mpu.initialize();
  if (!mpu.testConnection()) {
    return false;
  }

  // range for rocket
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
  return true;
}

bool mpuRead(MpuData &data) {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Coefficients for ±16g and ±1000°/s
  data.ax = ax / 2048.0f;
  data.ay = ay / 2048.0f;
  data.az = az / 2048.0f;
  data.gx = gx / 32.8f;
  data.gy = gy / 32.8f;
  data.gz = gz / 32.8f;
  return true;
}