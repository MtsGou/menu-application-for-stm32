/*
 * sys_definitions.c
 *
 *  Created on: 30 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    sys_definitions.c
  * @author  Matheus Gouveia
  * @brief   Definitions of the system, timers and uart used, and constants.
  *
  *
 **/

#include <data_functions.h>
#include <sys_definitions.h>
#include "main.h"

TIM_HandleTypeDef htim3;		/* Timer 3 */
TIM_HandleTypeDef htim4;		/* Timer 4 */
TIM_HandleTypeDef htim16;		/* Timer 16 */

UART_HandleTypeDef huart4;		/* UART 4 to the user menu */
UART_HandleTypeDef huart3;		/* UART 3 other serial communication */

/* BUFFER TO SEND TO UART4 */
uint16_t BUFFER_SERIAL[255];

/* BUFFER TO RECEIVE UART RX DATA */
char BUFFER_RECEIVE_DATA[1];

/* EXAMPLE VARIABLES. PUT YOUR VARIABLES HERE */
volatile float FLOAT_VAR = STANDARD_FLOAT;
volatile uint32_t INT_VAR = STANDARD_INT;
uint8_t STRING_VAR[16] = STANDARD_NAME;

/* BUFFERS FOR NUMERIC VARIABLES */
char INT_VAR_CHAR[8];
char FLOAT_VAR_CHAR[4];

/* FSM */
/* FSM_t sys_state; */
