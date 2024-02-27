/*
 * Menu_user.h
 *
 *  Created on: 16 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    Menu_user.h
  * @author  Matheus Gouveia
  * @brief   header for menu prototypes
  *
  ******************************************************************************
  */

#ifndef INC_MENU_USER_H_
#define INC_MENU_USER_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"

/* Wait for user data (single character) from UART.
 * If character is 'M', enters Menu. When stm receivers 'X', leaves menu.*/
void Handle_user(int ms_time);

/* Edit an integer variable.*/
uint32_t edit_int(uint32_t value);

/* Edit a float variable. */
float edit_float(float value);

/* Edit a string, waiting for the user. */
void edit_string(void);

/* Cleans a string, eliminating empty/null characters. */
char* clean_data_uart(char* string);

/* Clear screen of the serial monitor. */
void clear_screen(void);

/* Use system default values initially set. */
void use_default_values(void);

/* Prints menu. */
void print_menu(void);

/* See current saved parameters. */
void see_parameters(void);

#endif /* INC_MENU_USER_H_ */
