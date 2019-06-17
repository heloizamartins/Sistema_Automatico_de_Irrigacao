/*
 * IrrigationSystem.c
 *
 *  Created on: 3 de maio de 2019
 *      Author: Heloiza S. and Suzi Y.
 */


#include "IrrigationSystem.h"
#include "string.h"

uint32_t adcDmaBuffer[DMA_BUFF_SIZE];
//volatile uint32_t adc_value[2*8];
//static uint32_t buffer_adc_humidity[8];
//static uint32_t buffer_adc_cap[8];
//volatile uint32_t cap_value = 0;
//volatile uint32_t humidity_value = 0;

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
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcDmaBuffer, DMA_BUFF_SIZE);
	HAL_ADC_Start_IT(&hadc1);


}

uint32_t Read_Humidity_sensor(IrrigationSystem_t *sensor){
	uint32_t humidity = 0;
	for(uint8_t i = 1; i < DMA_BUFF_SIZE; i = i+2){  //pegar os impares
		humidity+=adcDmaBuffer[i];
	}
	humidity = humidity>>3;
	humidity = 100 - ((humidity*100)/4096);
	sensor->humidity = humidity;
	return humidity;
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
	uint32_t cap = 0;
	for(uint8_t i = 0; i < DMA_BUFF_SIZE; i = i+2){  //pegar os pares
		cap+=adcDmaBuffer[i];
	}
	cap = cap>>3;
	cap = (((cap*1000)/4096)*33)/10; //tensão em mV
	//cap_value = (ADC_MAX_LEVEL-cap_value)*100;
	//cap_value = (cap_value/(ADC_MAX_LEVEL-ADC_MIN_LEVEL))*100;
	//cap_value = 1 - cap_value/100;
	sensor->level= cap;
	return cap;
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
	//static uint8_t i=0;

	//cap_value = 0;
	//humidity_value = 0;

	//adc_value[0] = adcDmaBuffer[0];
	//adc_value[1] = adcDmaBuffer[1];

	/*buffer_adc_cap[0] = adc_value[0];
	buffer_adc_humidity[0] = adc_value[1];

	for(i = 7; i > 0; i--){
		buffer_adc_cap[i] = buffer_adc_cap[i-1]; 			//anda um passo nas amostras anteriores
		buffer_adc_humidity[i] = buffer_adc_humidity[i-1];
		cap_value += buffer_adc_cap[i];
		humidity_value += buffer_adc_humidity[i];
	}
	cap_value += buffer_adc_cap[0];
	humidity_value += buffer_adc_humidity[0];*/

	//cap_value = cap_value - buffer_adc_cap[i] + adc_value[0];
	//humidity_value = humidity_value - buffer_adc_humidity[i] + adc_value[1];
	//i++;
	//buffer_adc_cap[i] = adc_value[0];
	//buffer_adc_humidity[i] = adc_value[1];

	//i&=0x07;

}
