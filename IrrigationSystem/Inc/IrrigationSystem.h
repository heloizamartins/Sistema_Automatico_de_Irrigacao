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

#define ADC_CHANNELS_PER_SAMPLE 1
#define ADC_SAMPLES_PER_BUFFER 8
#define ADC_DMA_BUFFER_SIZE (ADC_SAMPLES_PER_BUFFER*ADC_CHANNELS_PER_SAMPLE)

typedef union
{
	struct {
		uint16_t humidity;
		uint16_t level;
	};
	uint16_t sensor[2];
}IrrigationSystem_t;

void IrrigationSystem_init();
void Humidity_Sensor_init(ADC_HandleTypeDef* hadc);
void Read_sensores(IrrigationSystem_t *sensor);
uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor);
void Verify_Humidity(IrrigationSystem_t *sensor, uint8_t min_humidity);
void Motor_pwm_init(TIM_HandleTypeDef *htim, uint32_t Channel);
void Turn_On_Motor(uint8_t pwm, TIM_HandleTypeDef *htim, uint32_t Channel);
void Turn_Off_Motor(TIM_HandleTypeDef *htim, uint32_t Channel);

#endif /* GY_80_ADXL345_H_ */
