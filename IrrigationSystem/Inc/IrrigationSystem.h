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
#define MIN_WATER_LEVEL 25
#define N_CHANNELS 2
#define N_SAMPLES 8
#define DMA_BUFF_SIZE  (N_CHANNELS*N_SAMPLES)
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

typedef union
{
	struct {
		uint16_t humidity;
		uint16_t level;
		uint16_t level_warning;
		uint16_t Motor;
	};
	uint16_t sensor[4];
}IrrigationSystem_t;

void IrrigationSystem_init();
uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor);
void Verify_Humidity(IrrigationSystem_t *sensor, uint16_t min_humidity);
uint32_t Read_Level_sensor(IrrigationSystem_t *sensor);
void Verify_Water_Level(IrrigationSystem_t *sensor);
void Turn_On_Motor(uint8_t pwm);
void Turn_Off_Motor();

#endif /* GY_80_ADXL345_H_ */
