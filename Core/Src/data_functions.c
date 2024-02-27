/*
 * data_functions.c
 *
 *  Created on: 16 de ago de 2022
 *      Author: matheus.gouveia
 */

/**
  ******************************************************************************
  * @file    data_functions.c
  * @author  Matheus Gouveia
  * @brief   Contains functions for sending data, data conversions and auxiliar functions.
  *
  ******************************************************************************
  */

#include <data_functions.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys_definitions.h>
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_it.h"

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief Send serial data to TX - UART4.
  *
  * @param  none
  *
  * @retval void
  */
void UART_SERIAL_SEND_TX(){

	/* Send data to UART4 */
	HAL_UART_Transmit(&huart4, BUFFER_SERIAL, strlen(BUFFER_SERIAL), 50);

	/* Erase Buffer */
	memset(BUFFER_SERIAL,0,strlen(BUFFER_SERIAL));

}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Converts Int to String (this was written by Lukás Chmela)
  *
  *
  * @param  value:      input integer value.
  * @param  *result:	pointer to result string
  * @param  base:		base (decimal, binary, hex).
  *
  * @retval *result
  */
char* IntToString(uint32_t value, char* result, int base) {

    /* check that the base if valid */
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    uint32_t tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
        		[35 + (tmp_value - value * base)];
    } while ( value );

    /* Apply negative sign */
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;

}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Write data on uart 4.
  *
  * @param  *data:  data to send TX.
  *
  * @retval void
  */
void write_UART(char *data){

	HAL_UART_Transmit(&huart4, data, strlen(data),100);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* The following functions can be found in https://www.geeksforgeeks.org/ */

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Reverses a string 'str' of length 'len'
  *
  * @param  *str: string to reverse.
  * @param  len:  string length.
  *
  * @retval void
  */
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Converts a given integer x to string str[].
  *
  * @param  x: integer
  * @param  str[]:  string array.
  * @param  d:  number of digits required in the output.
  *
  * @retval i
  */
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @brief  Converts a floating-point/double number to a string.
  *
  * @param  n: float
  * @param  *res:  string pointer.
  * @param  afterpoint:  digits after dot.
  *
  * @retval void
  */
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

