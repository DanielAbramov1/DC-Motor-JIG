/*
 * dc_motor_with_enc.c
 *
 *  Created on: Mar 21, 2020
 *      Author: dans
 */

#include "dc_motor_with_enc.h"

extern TIM_HandleTypeDef htim2;			//encoder timer
extern TIM_HandleTypeDef htim17;		//pid timer




extern char buf[];
extern UART_HandleTypeDef huart2;

extern float current;
//float max_current_in_move = 0.0;

//static uint32_t last_stall_test_tick = 0;

void motor_init(motor_controller *motor, TIM_HandleTypeDef * htim, uint32_t Channel,
		 GPIO_TypeDef * PORT1, uint16_t PIN1, GPIO_TypeDef * PORT2, uint16_t PIN2, int rev, float max_current)
{
	motor->htim = htim;
	motor->Channel = Channel;

	motor->PORT1 = PORT1;
	motor->PIN1 = PIN1;
	motor->PORT2 = PORT2;
	motor->PIN2 = PIN2;

	motor->done = 1;
	motor->stall = 0;
	motor->stalled_current = 0;
	motor->max_current_in_move = 0.0;

	motor->max_allowed_current = max_current;

	motor->encoder_location = 0;
	motor->previous_encoder_location = 0;

	motor->reverse = rev;

	HAL_TIM_PWM_Start(htim, Channel);

}

void spin_motor(motor_controller *motor, int speed)
{
	int spd = motor->reverse * speed;

	if (spd > 0)
	{
		HAL_GPIO_WritePin (motor->PORT1, motor->PIN1, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, spd);
	}
	else if (spd < 0)
	{
		HAL_GPIO_WritePin (motor->PORT1, motor->PIN1, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, -1*spd);
	}
	else
	{
		//HAL_GPIO_WritePin (motor->PORT1, motor->PIN1, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, 0);
	}

}

void motor_mode(motor_controller *motor, int mode)
{
	if (mode == 1)
	{
		HAL_GPIO_WritePin (motor->PORT2, motor->PIN2, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin (motor->PORT2, motor->PIN2, GPIO_PIN_RESET);
	}
}

/*
//-------------------------------------------------------------------- not relevant for the JIG

void motor_go_to(PIDControl *pid, int dest)
{
	pid->setpoint = dest;
	PIDModeSet(pid, AUTOMATIC);

	dc_motor_1.done = 0;

	HAL_TIM_Base_Start_IT(&htim17);
}

void pid_callback(PIDControl *pid1)
{
	dc_motor_1.previous_encoder_location = dc_motor_1.encoder_location;
	dc_motor_1.encoder_location = encoder_get_location(&enc);

	// TODO: stall is reported too often, check if lowering criterion helps
	// Adding current criterion
	if(!dc_motor_1.done && abs(dc_motor_1.encoder_location - dc_motor_1.previous_encoder_location) < 20 && current >= dc_motor_1.max_current_in_move * 0.75)
//	if(!dc_motor_1.done && abs(dc_motor_1.encoder_location - dc_motor_1.previous_encoder_location) < 10)
    {
    	dc_motor_1.stall = 1;

    	sprintf(buf,"DC Motor stalled! Current detected: %0.3f A\r\n", current);
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
    }
    else
    {
    	dc_motor_1.stall = 0;
    }

//	if (current >= dc_motor_1.max_current_in_move)
//	{
//		dc_motor_1.max_current_in_move = current;
//		dc_motor_1.stalled_current = (dc_motor_1.stall)?1:0;
//	}
//	sprintf(buf,"DC Motor current: %.3f A\r\n", current);
//	sprintf(buf,"Current: %.2f\r\n", current);
//	HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);

	pid1->input = dc_motor_1.encoder_location;

	PIDCompute(pid1);
	int tmp = pid1->output;

	spin_motor(&dc_motor_1, tmp);
	if(tmp <0)
		tmp = -1*tmp;


	if(tmp < 50)		//stop the motor
	{
		spin_motor(&dc_motor_1, 0);
		HAL_TIM_Base_Stop(&htim17);
		PIDModeSet(pid1, MANUAL);

		dc_motor_1.done = 1;
		sprintf(buf,"Max current detected in move: %0.3f A\r\n", dc_motor_1.max_current_in_move);
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		if (dc_motor_1.stalled_current)
		{
			sprintf(buf,"Max current detected in stall condition!\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		}
		sprintf(buf,"OK\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);
		dc_motor_1.max_current_in_move = 0.0;
	}


//	sprintf(buf,"setpoint:%d input:%d output:%d current:%d \r\n", (int) pid1->setpoint, (int) pid1->input, (int)pid1->output, (int)current);
//	HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0xFFFF);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM17)
	{
		pid_callback(&pid);
	}
}

//--------------------------------------------------------------------

void encoder_init(encoder *enc, TIM_HandleTypeDef * htim, int rev)
{
	enc-> reverse = rev;

	enc->htim = htim;

	HAL_TIM_Encoder_Start(enc->htim, TIM_CHANNEL_ALL);

}

int encoder_get_location(encoder *enc)
{
	return enc->reverse* htim2.Instance->CNT;	//this is alittle specific but its ok for now
}

void encoder_set_location(encoder *enc, int location)
{
	htim2.Instance->CNT = enc->reverse * location;
}
*/
