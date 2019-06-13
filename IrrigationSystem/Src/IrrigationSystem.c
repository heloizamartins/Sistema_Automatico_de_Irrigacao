/*
 * IrrigationSystem.c
 *
 *  Created on: 3 de maio de 2019
 *      Author: Heloiza S. and Suzi Y.
 */


#include "IrrigationSystem.h"

uint32_t adcDmaBuffer[2];
volatile uint32_t adc_value[2];

void IrrigationSystem_init(){
	//Motor PWM Init
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	//Timer 2 capture compare 2 event for ADC1
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 2000);

	//PWM for capacitor charging and discharging
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_4);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 15750);

	//ADC Init
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcDmaBuffer, 2);
	HAL_ADC_Start_IT(&hadc1);

}

uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor){
	uint32_t humidity_value = 0;

	for(uint8_t i = 0; i < 32; i++){
	  humidity_value += adc_value[1];
	}
	humidity_value /= 32;
	humidity_value = 100 - ((humidity_value*100)/4096);
	sensor->humidity = humidity_value;
	return humidity_value;
}

void Verify_Humidity(IrrigationSystem_t *sensor, uint8_t min_humidity)
{
	//min_humidity = porcentagem de umidade minima - 0:1:100
	uint32_t humidity;
	humidity = Read_Humidity_sensor(sensor);
	while(humidity < min_humidity){
		Turn_On_Motor(180);
		HAL_Delay(10000);
		Read_Humidity_sensor(sensor);
	}
	Turn_Off_Motor();
}

uint32_t Read_Level_sensor(IrrigationSystem_t *sensor){
	uint32_t cap_value=0;

	for(uint8_t i=0; i<32; i++){
	  cap_value += adc_value[0];
	}

	cap_value /= 32;
	//cap_value = (((cap_value*1000)/4095)*33)/10;
	cap_value = (ADC_MAX_LEVEL-cap_value)*100;
	cap_value = cap_value/(ADC_MAX_LEVEL-ADC_MIN_LEVEL);
	cap_value = 1 - cap_value/100;
	sensor->level= cap_value;
	return cap_value;
}

void Verify_Water_Level(IrrigationSystem_t *sensor)
{
	uint32_t water_level;
	water_level = Read_Level_sensor(sensor);
	if(water_level <= MIN_WATER_LEVEL){
		sensor->level_warning = 1;
	}else
		sensor->level_warning = 0;
}

void Turn_On_Motor(uint8_t pwm)
{
	//PWM - depende do tamanho do reservatório
	pwm = 200-pwm;  //há inversor
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
	HAL_GPIO_WritePin(LED_MOTOR_GPIO_Port, LED_MOTOR_Pin, SET);

}

void Turn_Off_Motor()
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 200);
	HAL_GPIO_WritePin(LED_MOTOR_GPIO_Port, LED_MOTOR_Pin, RESET);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	adc_value[0] = adcDmaBuffer[0];
	adc_value[1] = adcDmaBuffer[1];
}
