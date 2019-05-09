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
		  sensor[0].humidity = 100 - ((sensor[0].humidity*100)/4096);
		  ADCReady = RESET;
	  }
	}
	return values;
}

void Humidity_Sensor_init(ADC_HandleTypeDef* hadc){
	HAL_ADCEx_Calibration_Start(hadc);
	HAL_ADC_Start_DMA(hadc, (uint32_t *)adcDmaBuffer, ADC_DMA_BUFFER_SIZE);
}

void Motor_pwm_init(TIM_HandleTypeDef *htim, uint32_t Channel){
	HAL_TIM_PWM_Start(htim, Channel);
}

void Verify_Humidity(IrrigationSystem_t *sensor, uint8_t min_humidity)
{
	//min_humidity = porcentagem de umidade minima - 0:1:100
	uint32_t humidity;
	humidity = Read_Humidity_sensor(sensor);
	while(humidity < 3500){
		//Turn_On_Motor();
		HAL_Delay(10000);
	}
}

void Turn_On_Motor(uint8_t pwm, TIM_HandleTypeDef *htim, uint32_t Channel)
{
	//PWM - depende do tamanho do reservatório
	__HAL_TIM_SET_COMPARE(htim, Channel, pwm);
	HAL_GPIO_WritePin(LED_Motor_GPIO_Port, LED_Motor_Pin, SET);

}

void Turn_Off_Motor(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	//PWM = 0;
	__HAL_TIM_SET_COMPARE(htim, Channel, 0);
	HAL_GPIO_WritePin(LED_Motor_GPIO_Port, LED_Motor_Pin, RESET);
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	adcDmaBufferIndex=0;
	ADCReady= SET;

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	adcDmaBufferIndex = (ADC_DMA_BUFFER_SIZE / 2);
	ADCReady= SET;

}
