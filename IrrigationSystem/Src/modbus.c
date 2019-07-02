/*
 * modbus.c
 *
 *  Created on: 3 de maio de 2017
 *      Author: Heloiza S. and Suzi Y.
 */

#include "modbus.h"

char txDmaBuffer[TX_BUFFER_SIZE];
char RxDmaBuffer[RX_BUFFER_SIZE];
__IO ITStatus UartReady = RESET;

void RTU_package_IrrigationSystem(package_t *pkg, IrrigationSystem_t  *sensors, UART_HandleTypeDef *huart)
{
	uint16_t sensor_reg = 0x05;		/*Initialization with sensor_0 Address */
	uint8_t i;
	uint8_t aux;

	pkg->addr = MODBUS_ADDRESS;
	pkg->cmd = MODBUS_WRITE;
	Read_Humidity_sensor(sensors);
	Read_Level_sensor(sensors);
	Verify_Water_Level(sensors);
	for(i = 0; i < 4; i++){
		modbus_write(pkg, sensor_reg, sensors->sensor[i]);
		pkg->crc = CRC16_2(pkg->package, 6);
		pkg->data = swap_bytes(pkg->data);
		pkg->reg = swap_bytes(pkg->reg);

		txDmaBuffer[0]=pkg->addr;
		txDmaBuffer[1]=pkg->cmd;
		aux = pkg->reg >> 8;
		txDmaBuffer[2]=aux;
		txDmaBuffer[3]=pkg->reg;
		aux = pkg->data >> 8;
		txDmaBuffer[4]=aux;
		txDmaBuffer[5]=pkg->data;
		aux = pkg->crc >> 8;
		txDmaBuffer[6]=aux;
		txDmaBuffer[7]=pkg->crc;

		HAL_UART_Transmit(huart, (uint8_t*)txDmaBuffer, 8, 1000);

		HAL_UART_Receive(huart, (uint8_t*)RxDmaBuffer, 8, 1000);

		sensor_reg++;
	}
	sensors->Motor = 0;
}


uint16_t RTU_Read_package_IrrigationSystem(package_t *pkg, UART_HandleTypeDef *huart, IrrigationSystem_t  *sensors)
{
	uint16_t sensor_reg = 0x01;		/*Initialization with atuador_0 Address */
	uint8_t aux;
	uint16_t data_rx=0;
	pkg->addr = MODBUS_ADDRESS;
	pkg->cmd = MODBUS_READ;

	modbus_write(pkg, sensor_reg, 0x001);
	pkg->crc = CRC16_2(pkg->package, 6);
	pkg->data = swap_bytes(pkg->data);
	pkg->reg = swap_bytes(pkg->reg);

	txDmaBuffer[0]=pkg->addr;
	txDmaBuffer[1]=pkg->cmd;
	aux = pkg->reg >> 8;
	txDmaBuffer[2]=aux;
	txDmaBuffer[3]=pkg->reg;
	aux = pkg->data >> 8;
	txDmaBuffer[4]=aux;
	txDmaBuffer[5]=pkg->data;
	aux = pkg->crc >> 8;
	txDmaBuffer[6]=aux;
	txDmaBuffer[7]=pkg->crc;

	HAL_UART_Transmit(huart, (uint8_t*)txDmaBuffer, 8, 1000);

	HAL_UART_Receive(huart, (uint8_t*)RxDmaBuffer, 8, 1000);

	data_rx = RxDmaBuffer[5];

	return data_rx;
}

void modbus_write(package_t *pkg, uint16_t sensor_reg, uint16_t data)
{
	pkg->data = swap_bytes(data);
	pkg->reg = swap_bytes(sensor_reg);
}

uint16_t CRC16_2(uint8_t *buf, int len)
{
	uint32_t crc = 0xFFFF;
	int i;

	for (i = 0; i < len; i++)
	{
	crc ^= (uint16_t)buf[i]; // XOR byte into least sig. byte of crc
		for (int i = 8; i != 0; i--) { // Loop over each bit
			if ((crc & 0x0001) != 0) { // If the LSB is set
				crc >>= 1; // Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else // Else LSB is not set
				crc >>= 1; // Just shift right
		}
	}
	return crc;
}

/***************************************************************
Call this function to swap the first two bytes with the last two
of a value of type uint16_t
*****************************************************************/
uint16_t swap_bytes(uint16_t data)
{
	uint16_t new_data, data_;
	new_data = data >>8;
	data_ = data <<8;
	new_data |= data_;
	return new_data;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UartReady = SET;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UartReady = SET;
}

void Reset_huart_flag(){
	UartReady = RESET;
}

void Wait_transmit_finish(){
	while (UartReady != SET) {}
}
