#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
// ---- MPU6050: I2C1
#define MPU_SDA_PIN   18   // 
#define MPU_SCL_PIN   19   // 
#define MPU_I2C Wire1
#define MPU_I2C_CLOCK 400000

// ---- GPS NEO-6M: UART0 
#define GPS_TX_PIN    0  //
#define GPS_RX_PIN    1   //
#define GPS_SERIAL Serial1 
#define GPS_BAUD      9600

// ---- Common----
#define SERIAL_BAUD   115200
#define MPU_PERIOD_MS 10  

#endif