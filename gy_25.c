/*
 * gyro.c
 *
 *  Created on: Aug 30, 2023
 *      Author: hosea
 */
#include <math.h>
#include "gyro.h"

//transmit command
#define tx_start 0xA5 //transmit protocol
#define tx_query_mode 0x51 //transmit command
#define tx_automatic_mode_initialization 0x52
#define tx_automatic_mode_ASCIIoutput 0x53 //for computer assistant view
#define tx_correction_mode_pitch_correction_roll_angle 0x54 //need to stay level when sending
#define tx_correction_mode_heading_0_degree_course_correction 0x55 //heading cleared at any angle

const uint16_t timeout = 100;

//untuk membaca dan menyimpan data
void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	uint8_t data[7];
	HAL_UART_Receive_IT(huart, data, 7);

	Datastruct->Gyro_X_RAW = (int16_t)(data[1] << 8 | data[2]) / 100;
	Datastruct->Gyro_X_RAW = (int16_t)(data[3] << 8 | data[4]) / 100;
	Datastruct->Gyro_X_RAW = (int16_t)(data[5] << 8 | data[6]) / 100;
}

//engine
void query_mode(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	//query mode, return directly to the angle value, to be sent each read.
	HAL_UART_Transmit(huart, tx_start, sizeof(tx_start), timeout);
	HAL_UART_Transmit(huart, tx_query_mode, sizeof(tx_query_mode), timeout);
	void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct);
}

void automatic_mode1(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	//Automatic mode1, send a direct return angle, only initialization.
	HAL_UART_Transmit(huart, tx_start, sizeof(tx_start), timeout);
	HAL_UART_Transmit(huart, tx_automatic_mode_initialization, sizeof(tx_automatic_mode_initialization), timeout);
	void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct);
}

void automatic_mode2(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	//Automatic mode2, ASCII code output, serial port for direct computer assistant View.
	HAL_UART_Transmit(huart, tx_start, sizeof(tx_start), timeout);
	HAL_UART_Transmit(huart, tx_automatic_mode_ASCIIoutput, sizeof(tx_automatic_mode_ASCIIoutput), timeout);
	void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct);
}

void correction_mode1(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	//correction mode1, the pitch correction roll angle of 0 degrees, need to stay level when sending.
	HAL_UART_Transmit(huart, tx_start, sizeof(tx_start), timeout);
	HAL_UART_Transmit(huart, tx_correction_mode_pitch_correction_roll_angle, sizeof(tx_correction_mode_pitch_correction_roll_angle), timeout);
	void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct);

}

void correction_mode2(UART_HandleTypeDef *huart, gy25_t *Datastruct){
	//correction mode2, 0 degree course correction, heading cleared at any angle.
	HAL_UART_Transmit(huart, tx_start, sizeof(tx_start), timeout);
	HAL_UART_Transmit(huart, tx_correction_mode_heading_0_degree_course_correction, sizeof(tx_correction_mode_heading_0_degree_course_correction), timeout);
	void read_data(UART_HandleTypeDef *huart, gy25_t *Datastruct);

}

