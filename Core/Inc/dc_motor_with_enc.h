/*
 * dc_motor_with_enc.h
 *
 *  Created on: Mar 21, 2020
 *      Author: dans
 */

#ifndef INC_DC_MOTOR_WITH_ENC_H_
#define INC_DC_MOTOR_WITH_ENC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stm32f0xx_hal.h"
//#include "pid_controller.h"


typedef struct
{
	TIM_HandleTypeDef * htim;
	uint32_t Channel;

	GPIO_TypeDef * PORT1;
	uint16_t PIN1;
	GPIO_TypeDef * PORT2;
	uint16_t PIN2;

	uint8_t done;
	uint8_t stall;
	uint8_t stalled_current;
	float max_current_in_move;
	float max_allowed_current;

	int encoder_location, previous_encoder_location;

	int reverse;

}motor_controller;


void motor_init(motor_controller *motor, TIM_HandleTypeDef * htim, uint32_t Channel,
		 GPIO_TypeDef * PORT1, uint16_t PIN1, GPIO_TypeDef * PORT2, uint16_t PIN2, int rev, float max_current);

void spin_motor(motor_controller *motor, int speed);

void motor_mode(motor_controller *motor, int mode);
/*
typedef struct
{
	TIM_HandleTypeDef * htim;
	uint32_t Channel;

	int reverse;
}encoder;

extern void encoder_init(encoder *encoder, TIM_HandleTypeDef * htim, int rev);
extern int encoder_get_location(encoder *enc);
extern void encoder_set_location(encoder *enc, int location);
//extern void motor_go_to(PIDControl *pid, int dest);
extern uint8_t stall_detection(encoder *enc);

*/
#ifdef __cplusplus
}
#endif

#endif /* INC_DC_MOTOR_WITH_ENC_H_ */
