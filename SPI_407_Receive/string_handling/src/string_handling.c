/*
 * string_handling.c
 *
 *  Created on: Jun 27, 2022
 *      Author: Admin
 */

#include "string_handling.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
char *String_To_Binary(char *s)
{
    if (s == NULL)
        return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len * 8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for (size_t i = 0; i < len; ++i)
    {
        char ch = s[i];
        for (int j = 7; j >= 0; --j)
        {
            if (ch & (1 << j))
            {
                strcat(binary, "1");
            }
            else
            {
                strcat(binary, "0");
            }
        }
    }
    return binary;
}
char *Get_Sub_String(char *str, int index, int count)
{
    int strLen = strlen(str);
    int lastIndex = index + count;

    if (index >= 0 && lastIndex > strLen)
        return "";

    char *subStr = malloc(count + 1);

    for (int i = 0; i < count; i++)
    {
        subStr[i] = str[index + i];
    }

    subStr[count] = '\0';

    return subStr;
}

char *Append_String(const char *str1, const char *str2)
{
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int strLen = str1Len + str2Len + 1;
    char *str = malloc(strLen);

    for (int i = 0; i < str1Len; i++)
        str[i] = str1[i];

    for (int i = 0; i < str2Len; i++)
        str[(str1Len + i)] = str2[i];

    str[strLen - 1] = '\0';

    return str;
}

char *Char_To_String(char c)
{
    char *str = malloc(2);
    str[0] = c;
    str[1] = '\0';

    return str;
}

int Binary_To_Decimal(char *bin)
{
    int binLength = strlen(bin);
    double dec = 0;

    for (int i = 0; i < binLength; ++i)
    {
        dec += (bin[i] - 48) * pow(2, ((binLength - i) - 1));
    }

    return (int)dec;
}

char *Binary_To_ASCII(char *bin)
{
    char *ascii = "";
    int binLen = strlen(bin);

    for (int i = 0; i < binLen; i += 8)
    {
        ascii = Append_String(ascii, Char_To_String((char)Binary_To_Decimal(Get_Sub_String(bin, i, 8))));
    }

    return ascii;
}
