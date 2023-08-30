/*
 * gyro.h
 *
 *  Created on: Aug 30, 2023
 *      Author: hosea
 */

#ifndef SRC_GYRO_H_
#define SRC_GYRO_H_


#endif /* SRC_GYRO_H_ */
#include <stdint.h>
#include "stm32l4xx_hal_uart.h"

typedef struct
{
    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;

} gy25_t;


/*0xA5 + 0x51: query mode, return directly to the angle value, to be sent each read.
  0xA5 + 0x52: Automatic mode, send a direct return angle, only initialization.
  0xA5 + 0x53: Automatic mode, ASCII code output, serial port for direct computer assistant View.
  0xA5 + 0x54: correction mode, the pitch correction roll angle of 0 degrees, need to stay level when sending.
  0xA5 + 0x55: correction mode, 0 degree course correction, heading cleared at any angle.
(1), due to self-correction at power up the module must be held in a stationary position for at least 3000ms, hand-held of this module is not recommended
(2), module heading will drift after a while without magnetometer.
(3), due to the angle of the Euler angles universal lock problem, roll, pitch, have an impact on each other at 90 degrees.
(4), The module IOs are 5.0V tolerant, the module can be used with 5.0 and 3.3V system and serial adapters without any risk.
*/
void query_mode(UART_HandleTypeDef *huart, gy25_t *Datastruct); //query mode, return directly to the angle value, to be sent each read.
void automatic_mode1(UART_HandleTypeDef *huart, gy25_t *Datastruct); //Automatic mode1, send a direct return angle, only initialization.
void automatic_mode2(UART_HandleTypeDef *huart, gy25_t *Datastruct); //Automatic mode2, ASCII code output, serial port for direct computer assistant View.
void correction_mode1(UART_HandleTypeDef *huart, gy25_t *Datastruct); //correction mode1, the pitch correction roll angle of 0 degrees, need to stay level when sending.
void correction_mode2(UART_HandleTypeDef *huart, gy25_t *Datastruct); //correction mode2, 0 degree course correction, heading cleared at any angle.
