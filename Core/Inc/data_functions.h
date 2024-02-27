/*
 * data_functions.h
 *
 *  Created on: 16 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    data_functions.h
  * @author  Matheus Gouveia
  * @brief   Header for data_functions.c
  *
  *
  ******************************************************************************
  */

#ifndef INC_DATA_FUNCTIONS_H_
#define INC_DATA_FUNCTIONS_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"

/* Send serial data to TX - UART4.*/
void UART_SERIAL_SEND_TX(void);

/* Converts Int to String */
char* IntToString(uint32_t value, char* result, int base);

/* Write data on uart 4. */
void write_UART(char *data);

/* Bellow functions from GeeksforGeeks */

/* Reverses a string 'str' of length 'len'. */
void reverse(char* str, int len);

/* Converts a given integer x to string str[]. */
int intToStr(int x, char str[], int d);

/* Converts a floating-point/double number to a string. */
void ftoa(float n, char* res, int afterpoint);

#endif /* INC_DATA_FUNCTIONS_H_ */
