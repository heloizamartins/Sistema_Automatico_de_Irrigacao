/*
 * modbus.c
 *
 *  Created on: 6 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */


#include "modbus.h"


char txDmaBuffer[TX_BUFFER_SIZE];
//char rxDmaBuffer[RX_BUFFER_SIZE];
__IO ITStatus UartReady = RESET;

void RTU_package_IrrigationSystem(package_t *pkg, IrrigationSystem_t  *sensors, UART_HandleTypeDef *huart)
{
	uint16_t sensor_reg = 0x05;		/*Initialization with sensor_0 Address */
	uint8_t i;
	uint8_t aux;

	pkg->addr = MODBUS_ADDRESS;
	pkg->cmd = MODBUS_WRITE;
	Read_Humidity_sensor(sensors);  //depois mudar para generico

	for(i = 0; i < 1; i++){
		modbus_write(pkg, sensor_reg, sensors->humidity);
		pkg->crc = CRC16_2(pkg->package, 6);
		pkg->data = swap_bytes(pkg->data);
		pkg->reg = swap_bytes(pkg->reg);

		Reset_huart_flag();

		HAL_UART_Transmit_IT(huart, &pkg->addr, sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		HAL_UART_Transmit_IT(huart, &pkg->cmd, sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		aux = pkg->reg >> 8;
		HAL_UART_Transmit_IT(huart, &aux, sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		HAL_UART_Transmit_IT(huart, (uint8_t*)(&pkg->reg), sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		aux = pkg->data >> 8;
		HAL_UART_Transmit_IT(huart, &aux, sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		HAL_UART_Transmit_IT(huart, (uint8_t*)(&pkg->data), sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		aux = pkg->crc >> 8;
		HAL_UART_Transmit_IT(huart, &aux, sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		HAL_UART_Transmit_IT(huart, (uint8_t*)(&pkg->crc), sizeof(uint8_t));
		Wait_transmit_finish();
		Reset_huart_flag();

		sensor_reg++;
		HAL_Delay(500);
	}
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
	int16_t new_data, data_;
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