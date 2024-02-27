/*
 * sys_definitions.h
 *
 *  Created on: 30 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    sys_definitions.h
  * @author  Matheus Gouveia
  * @brief   header for sys_definitions.c
  *
  *
  ******************************************************************************
  */

#ifndef INC_SYS_DEFINITIONS_H_
#define INC_SYS_DEFINITIONS_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"

typedef int bool;
#define true 1
#define false 0

#define VERSION            		   "v1.0"
#define FIRMWARE_DATE      		   "30/08/2022"
#define MCU_INFO           		   "STM32 L476RG"

#define LOW 						0x0
#define HIGH 						0x1
#define ON 							0x1
#define OFF 						0x0
#define END_INICIAL  				0x08080000UL /* Endereco salvar flash */
#define END_STG						0x08080000UL

#define FRAME_ACTUATE_RELAY			0x1		 	 /* Opcao preencher buffer feedback -> rele atuado */
#define FRAME_PING					0x2		 	 /* Opcao preencher buffer feedback -> caso PING */
#define FRAME_BATTERY_FAIL			0x3		 	 /* Opcao preencher buffer feedback -> falha bateria */
#define FRAME_BATTERY_RETURN		0x4		 	 /* Opcao preencher buffer feedback -> bateria ok */

#define STANDARD_NAME                   "My Menu"    /* Standard name of application */
#define STANDARD_FLOAT					10.5f		 /* Standard float value */
#define STANDARD_INT                    10           /* Standard integer value */

/*typedef enum {

    IDLE,
    __LAST_STATE,
    __VALID_STATE,
    SYS_FAIL,
    FATAL_FAIL // break and check position
                // with GPS or referential
} FSM_t;

extern FSM_t sys_state; */

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim16;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart3;

/* BUFFER TO SEND TO UART4 */
extern uint16_t BUFFER_SERIAL[255];

/* BUFFER TO RECEIVE UART RX DATA */
extern char BUFFER_RECEIVE_DATA[1];

/* EXAMPLE VARIABLES. PUT YOUR VARIABLES HERE */
extern volatile float FLOAT_VAR;
extern volatile uint32_t INT_VAR;
extern uint8_t STRING_VAR[16];

/* BUFFERS FOR NUMERIC VARIABLES */
extern char INT_VAR_CHAR[8];
extern char FLOAT_VAR_CHAR[4];


#ifdef __cplusplus
}
#endif

#endif /* INC_SYS_DEFINITIONS_H_ */
