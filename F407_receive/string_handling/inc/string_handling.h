/*
 * string_handling.h
 *
 *  Created on: Jun 27, 2022
 *      Author: Admin
 */

#ifndef INC_STRING_HANDLING_H_
#define INC_STRING_HANDLING_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


char *String_To_Binary(char *s);
char *Get_Sub_String(char *str, int index, int count);
char *Append_String(const char *str1, const char *str2);
char *Char_To_String(char c);
int Binary_To_Decimal(char *bin);
char *Binary_To_ASCII(char *bin);


#endif /* INC_STRING_HANDLING_H_ */
