/*
 * ADXL345.c
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */


#include "IrrigationSystem.h"

uint16_t adcDmaBuffer[ADC_DMA_BUFFER_SIZE];
volatile uint8_t adcDmaBufferIndex = 0;
__IO ITStatus ADCReady = RESET;

void IrrigationSystem_init(){

}

void Read_Humidity_sensor(IrrigationSystem_t *sensor){
	uint8_t counter = 0;
	if (ADCReady == SET){
	  if (++(counter) == 25){
		  counter = 0;
		  uint32_t values = 0;
		  for(uint8_t i = 0; i < (ADC_DMA_BUFFER_SIZE/2); i++){
			  values += adcDmaBuffer[adcDmaBufferIndex+i];
		  }
		  sensor[0].humidity = (values/ADC_DMA_BUFFER_SIZE)*2;
		  ADCReady = RESET;

		  //RTU_package_IrrigationSystem(&pkg, (uint16_t)values, &huart1);
	  }
	}
}

void Humidity_Sensor_init(ADC_HandleTypeDef* hadc){
	HAL_ADCEx_Calibration_Start(hadc);
	HAL_ADC_Start_DMA(hadc, (uint32_t *)adcDmaBuffer, ADC_DMA_BUFFER_SIZE);
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	adcDmaBufferIndex=0;
	ADCReady= SET;
	//systemFlags.convReady = 1;
	//HAL_GPIO_TogglePin(DEBUG_3_GPIO_Port, DEBUG_3_Pin);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	adcDmaBufferIndex = (ADC_DMA_BUFFER_SIZE / 2);
	ADCReady= SET;
	//systemFlags.convReady = 1;
	//HAL_GPIO_TogglePin(DEBUG_2_GPIO_Port, DEBUG_2_Pin);
}

