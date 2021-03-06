 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Shawky Abo el-ela
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */

void DcMotor_init(void){
	/*set PB0 and PB1 direction as output*/
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_2_ID,PIN_OUTPUT);

	/* the motor stop at the beginning */

	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID,LOGIC_LOW);

}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */

void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	if(state == CW){
		/*the motor will rotate clockwise*/
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID,LOGIC_HIGH);
	}
	else if(state == A_CW ){
		/*the motor will rotate Anti-clockwise*/
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID,LOGIC_LOW);
	}
	else if(state == STOP){
		/*the motor will stop rotating*/
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID,LOGIC_LOW);
	}

	uint8 duty_cycle=(uint8)((uint32)(speed*(256/100)));
    /* send the speed to the PWM*/
	PWM_Timer0_start(duty_cycle);
}
