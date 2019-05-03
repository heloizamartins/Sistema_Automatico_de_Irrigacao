/*
 * IrrigationSystem.c
 *
 *  Created on: 3 de maio de 2019
 *      Author: Heloiza S. and Suzi Y.
 */


#include "IrrigationSystem.h"

uint16_t adcDmaBuffer[ADC_DMA_BUFFER_SIZE];
volatile uint8_t adcDmaBufferIndex = 0;
__IO ITStatus ADCReady = RESET;

void IrrigationSystem_init(){

}

uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor){
	uint8_t counter = 0;
	uint32_t values = 0;
	while(ADCReady != SET);
	while (ADCReady == SET){
	  if (++(counter) == 25){
		  counter = 0;
		  values = 0;
		  for(uint8_t i = 0; i < (ADC_DMA_BUFFER_SIZE/2); i++){
			  values += adcDmaBuffer[adcDmaBufferIndex+i];
		  }
		  sensor[0].humidity = (values/ADC_DMA_BUFFER_SIZE)*2;
		  ADCReady = RESET;

		  //RTU_package_IrrigationSystem(&pkg, (uint16_t)values, &huart1);
	  }
	}
	return values;
}

void Humidity_Sensor_init(ADC_HandleTypeDef* hadc){
	HAL_ADCEx_Calibration_Start(hadc);
	HAL_ADC_Start_DMA(hadc, (uint32_t *)adcDmaBuffer, ADC_DMA_BUFFER_SIZE);
}

void Verify_Humidity(IrrigationSystem_t *sensor, uint8_t min_humidity)
{
	//min_humidity = porcentagem de umidade minima - 0:1:100
	uint32_t humidity;
	humidity = Read_Humidity_sensor(sensor);
	while(humidity < 3500){
		Turn_On_Motor();
		HAL_Delay(10000);
	}
}

void Turn_On_Motor()
{
	//PWM - depende do tamanho do reservatório
	HAL_GPIO_WritePin(LED_Motor_GPIO_Port, LED_Motor_Pin, SET);
}

void Turn_Off_Motor()
{
	//PWM = 0;
	HAL_GPIO_WritePin(LED_Motor_GPIO_Port, LED_Motor_Pin, RESET);
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
