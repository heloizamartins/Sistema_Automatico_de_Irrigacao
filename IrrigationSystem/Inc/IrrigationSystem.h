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
void Read_Humidity_sensor(IrrigationSystem_t *sensor);
#endif /* GY_80_ADXL345_H_ */
