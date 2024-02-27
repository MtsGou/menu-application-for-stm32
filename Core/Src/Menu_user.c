/*
 * Menu_user.c
 *
 *  Created on: 16 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    Menu_user.c
  * @author  Matheus Gouveia
  * @brief   Functions definitions for menu application
  *
  ******************************************************************************
  */

#include <sys_definitions.h>
#include <data_functions.h>
#include <Menu_user.h>
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_it.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Wait for user data (single character) from UART.
  *         If character is 'M', enters Menu. When stm receivers 'X', leaves menu.
  *
  * @param  ms_time:  time waiting for data(ms).
  *
  * @retval void
  */
void Handle_user(int ms_time){

	// After enters menu, MENU_INIT = 1
	static uint8_t MENU_INIT = 0;

	memset(BUFFER_RECEIVE_DATA, 0, strlen(BUFFER_RECEIVE_DATA));
	if (HAL_UART_Receive(&huart4, &BUFFER_RECEIVE_DATA, 1, ms_time) == HAL_OK){

		if(strcmp(BUFFER_RECEIVE_DATA, "M") == 0){
			MENU_INIT = 1;
			print_menu();
		}

		else if (!MENU_INIT){}

		else if(strcmp(BUFFER_RECEIVE_DATA, "A") == 0){
			edit_string();
			print_menu();
			write_UART("\n\r\n\rSTRING_VAR: ");
			write_UART((char *) STRING_VAR);
		}

		else if(strcmp(BUFFER_RECEIVE_DATA, "B") == 0){
			INT_VAR = edit_int(INT_VAR);
			memset(INT_VAR_CHAR, 0, strlen(INT_VAR_CHAR));
			sprintf(INT_VAR_CHAR, "%d", INT_VAR);
			print_menu();
		}

		else if(strcmp(BUFFER_RECEIVE_DATA, "C") == 0){
			FLOAT_VAR = edit_float(FLOAT_VAR);
			memset(FLOAT_VAR_CHAR, 0, strlen(FLOAT_VAR_CHAR));
			ftoa(FLOAT_VAR, FLOAT_VAR_CHAR, 2);
			print_menu();
		}
		else if (strcmp(BUFFER_RECEIVE_DATA, "D") == 0){
			use_default_values();
		}

		else if (strcmp(BUFFER_RECEIVE_DATA, "E") == 0){
			see_parameters();
		}

		else if(strcmp(BUFFER_RECEIVE_DATA, "X") == 0){
			clear_screen();
			write_UART("\r");
			MENU_INIT = 0;
		}
	}

}

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Edit an integer variable.
  *
  * @param  value:  value passed.
  *
  * @retval value
  */
uint32_t edit_int(uint32_t value){

	char data_rcv[10];
	char* command;
	int change = 1;
	uint32_t Standard = value;
	char value_CHAR[10];

	write_UART("\r\n");
	write_UART("\r\nw - INCREASE\r\n");
	write_UART("\r\ns - DECREASE\r\n");
	write_UART("\r\nA - SAVE\r\n");
	write_UART("\r\nX - RETURN TO MENU\r\n\r\n");

	IntToString(value, value_CHAR, 10);
	write_UART(value_CHAR);
	write_UART("\r");

	while(1){

		memset(data_rcv, 0, strlen(data_rcv));
		memset(command, 0, strlen(command));

		if(HAL_UART_Receive(&huart4, &data_rcv, 1,100) == HAL_OK){

			command = data_rcv;
			command = clean_data_uart(command);

			if(strcmp(command, "w") == 0){
				value += change;
				memset(value_CHAR, 0, strlen(value_CHAR));
				IntToString(value, value_CHAR, 10);
				write_UART(value_CHAR);
				write_UART("\r");
			}

			else if (strcmp(command, "s") == 0){
				value -= change;
				memset(value_CHAR, 0, strlen(value_CHAR));
				IntToString(value, value_CHAR, 10);
				write_UART(value_CHAR);
				write_UART("\r");
			}

			else if(strcmp(command, "A") == 0){
				write_UART("\n\rSaved! ");
				break;
			}

			else if(strcmp(command, "X") == 0){
				value = Standard;
				break;
			}

		}
	}
	memset(command, 0, strlen(command));
	return value;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Edit a float variable.
  *
  * @param  value:  value passed.
  *
  * @retval value
  */
float edit_float(float value){

	char rcvd_data[10];
	char* command;
	float change = 0.01;
	float Standard = value;
	char value_CHAR[6];

	write_UART("\r\n\r\n");
	write_UART("\r\nw - INCREASE\r\n");
	write_UART("\r\ns - DECREASE\r\n");
	write_UART("\r\na - <-- CHOOSE DECIMAL TO THE LEFT\r\n");
	write_UART("\r\nd - --> CHOOSE DECIMAL TO THE RIGHT\r\n");
	write_UART("\r\nA - SAVE\r\n");
	write_UART("\r\nX - RETURN TO MENU\r\n");
	write_UART("\r\n");

	ftoa(value, value_CHAR, 2);
	write_UART(value_CHAR);
	write_UART("\r");

	while(1){

		memset(rcvd_data, 0, strlen(rcvd_data));
		memset(command, 0, strlen(command));

		if(HAL_UART_Receive(&huart4, &rcvd_data, 1,100) == HAL_OK){

			command = rcvd_data;
			command = clean_data_uart(command);

			if(strcmp(command, "w") == 0){
				value += change;
				memset(value_CHAR, 0, strlen(value_CHAR));
				IntToString(value, value_CHAR, 10);
				write_UART(value_CHAR);
				write_UART("\r");
			}

			else if (strcmp(command, "s") == 0){
				value -= change;
				memset(value_CHAR, 0, strlen(value_CHAR));
				IntToString(value, value_CHAR, 10);
				write_UART(value_CHAR);
				write_UART("\r");
			}

			else if (strcmp(command, "d") == 0){
				change = change/10;
				if (change < 0.01){ change = 0.01;}
			}

			else if (strcmp(command, "a") == 0){
				change = change*10;
				if (change > 10){ change = 10;}
			}

			else if(strcmp(command, "A") == 0){
				write_UART("\n\rSaved! ");
				break;
			}

			else if(strcmp(command, "X") == 0){
				value = Standard;
				break;
			}
		}

	}
	memset(command, 0, strlen(command));
	return value;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Edit a string, waiting for the user.
  *
  * @param  none
  *
  * @retval value
  */
void edit_string(void){

	char data_received[10];
	char* command;
	uint8_t NEW_STRING[20];

	write_UART("\n\r");
	write_UART("\r\nPRESS > TO SAVE\r\n");
	write_UART("X - RETURN TO MENU\r\n");
	write_UART("\r\n");
	memset(NEW_STRING, 0, strlen(NEW_STRING));

	while (1){

		memset(data_received, 0, strlen(data_received));
		memset(command, 0, strlen(command));

		if(HAL_UART_Receive(&huart4, &data_received, 1,100) == HAL_OK){

			command = data_received;
			command = clean_data_uart(command);

			if (strcmp(command, ">") == 0){
				memset(STRING_VAR, 0, strlen(STRING_VAR));
				strcat(STRING_VAR, NEW_STRING);
				break;
			}

			else if (strcmp(command, "X") == 0){
				break;
			}

			else if (strlen(command)){
				write_UART(command);
				strcat(NEW_STRING, command);
			}
		}

	}
	memset(command, 0, strlen(command));
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Cleans a string, eliminating empty/null characters.
  *
  * @param  *string: String to be cleaned.
  *
  * @retval *string
  */
char* clean_data_uart(char* string){

	int error_index = 1;

	while (error_index < strlen(string)){
		error_index = strcspn(string, "\r\n\t  ");
		memmove(&string[error_index], &string[error_index + 1], strlen(string) - error_index);
	}

	return string;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Clear screen of the serial monitor.
  *
  * @param  none
  *
  * @retval void
  */
void clear_screen(){
	for (int times = 0; times < 60; times++){
		write_UART("\n\r");
	}
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Use system default values initially set.
  *
  * @param  none
  *
  * @retval void
  */
void use_default_values(){

	memset(STRING_VAR, 0, strlen(STRING_VAR));
	strcat(STRING_VAR, STANDARD_NAME);
	FLOAT_VAR = STANDARD_FLOAT;
	INT_VAR = STANDARD_INT;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Prints menu.
  *
  * @param  none
  *
  * @retval void
  */
void print_menu(){

	write_UART("\r\n\r\nMENU\r\n");
	write_UART("\n\rSELECT       Shift + key\n\r");
	write_UART("\n\rEDIT STRING VARIABLE           A");
	write_UART("\n\rEDIT INT VARIABLE              B");
	write_UART("\n\rEDIT FLOAT VARIABLE            C");
	write_UART("\n\rUSE DEFAULT VALUES             D");
	write_UART("\n\rSEE CURRENT PARAMETERS         E");
	write_UART("\n\rLEAVE MENU                     X");
	write_UART("\r");
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  See current saved parameters.
  *
  * @param  none
  *
  * @retval void
  */
void see_parameters(){

	write_UART("\n\r");
	write_UART("\r\nSTRING VARIABLE:");
	write_UART((char *)STRING_VAR);
	write_UART("\r\nINT VARIABLE:");
	write_UART(INT_VAR_CHAR);
	write_UART("\r\nFLOAT VARIABLE:");
	write_UART(FLOAT_VAR_CHAR);

}
