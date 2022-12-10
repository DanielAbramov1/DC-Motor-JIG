#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "dc_motor_with_enc.h"
#include "decode_packet.h"
#include "main.h"
#include "addressable_led.h"

extern long preMillis;
#define timeout_time 10000 //in mili-sec
#define speed_increase_delay 35 //in mili-sec

extern uint16_t adc_buffer[];
extern motor_controller dc_motor_1;
extern int motor_speed;             //for testing
extern UART_HandleTypeDef huart2;
extern char buf[];

extern led_controller led_indicator;

int upper_ms_pin=0; // 0 - open position, 1 - pressed position
int lower_ms_pin=0; // 0 - open position, 1 - pressed position
int push_button_pin=1;// 1 - open position, 0 - pressed position
int push_flag=0;

int current_check()
{
	float calc_current = (3.3 * (float)adc_buffer[3]) / (1.5 * 1023) ;

	if(calc_current>=dc_motor_1.max_current_in_move)
		dc_motor_1.max_current_in_move=calc_current;
	if(dc_motor_1.max_current_in_move>=dc_motor_1.max_allowed_current)
	{
		sprintf(buf, "MAX CURRENT DETECTED! STOPPING DC MOTOR...\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		spin_motor(&dc_motor_1,0);
		return 1;
	}
	return 0;
}

int motor_timeout_check()
{
	if(HAL_GetTick()-preMillis>=timeout_time)
	{
		preMillis=HAL_GetTick();
		sprintf(buf, "Motor movement timeout... \r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		return 1;
	}
	return 0;
}


void sequence_start()
{
	int speed=100;
	char current_output[5];
	lower_ms_pin=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10);
	upper_ms_pin=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
	push_button_pin=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9);
	if(!push_button_pin)
	{
		set_color(0, 0, 0, 0);
		led_display(&led_indicator);
		push_flag=1;
	}

	if(push_flag)      //start sequence
	{
		sprintf(buf, "Push button was pressed. Starting calibration sequence  \r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);

		while(!upper_ms_pin)
		{
			spin_motor(&dc_motor_1,speed);
			speed++;
			HAL_Delay(speed_increase_delay);
			if(speed>255)
				speed=255;
			if(current_check())
			{
				set_color(255, 0, 0, 0);
				led_display(&led_indicator);
				return;
			}
			if(motor_timeout_check())
			{
				spin_motor(&dc_motor_1,0);
				set_color(255, 100, 0, 0);
				led_display(&led_indicator);
				push_flag=0;// in loop need to reset when timeout
				return;
			}
			upper_ms_pin=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		}
		sprintf(buf, "Upper micro-swith is pressed. motor reached upper position \r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);

		spin_motor(&dc_motor_1,0);
		HAL_Delay(500);
		speed=100;
		preMillis=HAL_GetTick();

		while(!lower_ms_pin)
		{
			spin_motor(&dc_motor_1,-1*speed);
			speed++;
			HAL_Delay(speed_increase_delay);
			if(speed>255)
				speed=255;
			if(current_check())
			{
				set_color(255, 0, 0, 0);
				led_display(&led_indicator);
				return;
			}
			if(motor_timeout_check())
			{
				spin_motor(&dc_motor_1,0);
				set_color(255, 100, 0, 0);
				led_display(&led_indicator);
				push_flag=0;// in loop need to reset when timeout
				return;
			}
			lower_ms_pin=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10);
		}
		sprintf(buf, "Lower micro-swith is pressed. motor reached lower position \r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		spin_motor(&dc_motor_1,0);
		HAL_Delay(500);
		push_flag=0;

		gcvt(dc_motor_1.max_current_in_move,5,current_output);
		sprintf(buf, "\nSequence Finished Successfully , Max Current detected:%s \r\n\n",current_output);
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		set_color(0, 255, 0, 0);
		led_display(&led_indicator);
	}
}

















