/*
 * main.c
 *
 *  Created on: Jul 11, 2022
 *      Author: Admin
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct queue{
	int size, front, rear;
	int *p;
};
void create( struct queue *q, int size){
	q->size=size;
	q->front=q->rear=-1;
	q->p=(int*)malloc(q->size*sizeof(int));
}
void enqueue( struct queue *q, int x){
	if(q->rear==q->size-1)
		printf("Queue is FULL");
	else{
		q->rear++;
		q->p[q->rear]=x;
	}
}
int dequeue(struct queue *q){
	int x=-1;
	if(q->front==q->rear)
		printf("Queue is EMPTY");
	else{
		q->front++;
		x=q->p[q->front];
	}
	return x;
}
void display(struct queue q){
	int i;
	for(i=q.front+1;i<=q.rear;i++){
		printf("%d", q.p[i]);
	}
}

// CIRCULAR QUEUE




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
int main(){
	struct queue q;

	//enqueue(&q, 10);
    char str1[129], str[]="01001000011001010110110001101100011011110010000001010111011011110111001001101100011001000010000000110010001100000011001000110010";
    create(&q, sizeof(str));
    char i=0;
    for(i=0;i<strlen(str);i++){
        enqueue(&q, str[i]-48);
    }
    for(i=0;i<strlen(str);i++){
        str1[i]=q.p[i];
    }
    printf("%s", Binary_To_ASCII(str1));
}
