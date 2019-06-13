/*
 * ADXL345.h
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#ifndef IrrigationSystem_H_
#define IrrigationSystem_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#define ADC_MAX_LEVEL 1700
#define ADC_MIN_LEVEL 1400

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

typedef union
{
	struct {
		uint16_t humidity;
		uint16_t level;
	};
	uint16_t sensor[2];
}IrrigationSystem_t;

void IrrigationSystem_init();
uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor);
uint32_t Read_Level_sensor(IrrigationSystem_t *sensor);
void Verify_Humidity(IrrigationSystem_t *sensor, uint8_t min_humidity);
void Turn_On_Motor(uint8_t pwm, TIM_HandleTypeDef *htim, uint32_t Channel);
void Turn_Off_Motor(TIM_HandleTypeDef *htim, uint32_t Channel);

#endif /* GY_80_ADXL345_H_ */
