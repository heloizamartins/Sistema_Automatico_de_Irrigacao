/*
 * modbus.h
 *
 *  Created on: 6 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#ifndef GY_80_MODBUS_H_
#define GY_80_MODBUS_H_

#include <stdint.h>
#include <stdio.h>
#include "IrrigationSystem.h"
#include "stm32f1xx_hal.h"

#define MODBUS_ADDRESS 0x15
#define MODBUS_WRITE 0x01
#define MODBUS_READ 0x02
#define MODBUS_REG_SENSOR0 0x05

#define RX_BUFFER_SIZE	256
#define TX_BUFFER_SIZE 50

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

typedef union{
	struct{
		uint8_t addr;
		uint8_t cmd;
		uint16_t reg;
		uint16_t data;
		uint16_t crc;
	};
	uint8_t package[8];
}package_t;

void RTU_package_IrrigationSystem(package_t *pkg, IrrigationSystem_t  *sensors, UART_HandleTypeDef *huart);
uint8_t RTU_Read_package_IrrigationSystem(package_t *pkg, UART_HandleTypeDef *huart);
void modbus_write(package_t *pkg, uint16_t sensor_reg, uint16_t data);
uint16_t CRC16_2(uint8_t *buf, int len);
uint16_t swap_bytes(uint16_t data);
void Reset_huart_flag();
void Wait_transmit_finish();
#endif /* GY_80_MODBUS_H_ */
