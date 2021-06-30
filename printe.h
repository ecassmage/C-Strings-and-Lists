//
// Created by evanm on 2021-06-30.
//

#ifndef C_STRINGS_AND_LISTS_PRINTE_H
#define C_STRINGS_AND_LISTS_PRINTE_H

#include <stdio.h>
#include "str.h"
#include "list.h"
#include <stdarg.h>

char *convertIntToChar(long num){
    int i = 0;
    unsigned neg = 0;
    if (num < 0){
        i++;
        num *= -1;
        neg = 1;
    }
    for (int j = 1; j < num; i++, j*=10);
    char *temp = (char*) malloc((i+1) * sizeof(char));
    temp[i--] = '\0';
    for (;num >= 10; i--){
        temp[i] = (char) ((num - ((num / 10) * 10)) + 48);
        num = num / 10;
    }
    temp[i] =(char) (num + 48);
    if (neg) temp[0] = '-';
    return temp;
}

char *convertDoubleToChar(double num){
    int intNumber = (int) num;
    double OnlyDecimal = num - intNumber;
    for (; OnlyDecimal != (double) ((long) OnlyDecimal); OnlyDecimal *= (double) 10);
    char *integer = convertIntToChar(intNumber);
    char *decimal = convertIntToChar((long) OnlyDecimal);
    char *full = (char*) malloc((strLen(integer) + strLen(decimal) + 2) * sizeof(char));
    for(intNumber = 0; integer[intNumber] != '\0'; intNumber++) full[intNumber] = integer[intNumber];// Reuse Variables
    full[intNumber++] = '.';
    for(int i = 0; decimal[i] != '\0'; intNumber++, i++) full[intNumber] = decimal[i];// Reuse Variables
    full[intNumber] = '\0';
    return NULL;
}

void print(const char *format, ...){
    va_list listOfOutputs;
    va_start(listOfOutputs, format);
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] == '%' && format[i-1] != '%' && format[i-1] != '\\'/* Probably won't work unless \\% not \% */) {
            switch (format[i + 1]) {
                case 'd':   printf("%d", va_arg(listOfOutputs, int)); break;
                case 'l':   if (format[i + 2] == 'f'){
                            printf("%lf", va_arg(listOfOutputs, double));
                            i++;
                    } else  printList(va_arg(listOfOutputs, list*), false); break;
                case 'f':   printf("%f", va_arg(listOfOutputs, double)); break;
                case 'c':   printf("%c", (char) va_arg(listOfOutputs, int)); break;
                case 's':   printf("%s", va_arg(listOfOutputs, char*)); break;
                case 'a':   break;

                default:    continue;

            }
            i++;
        }
        else{
            printf("%c", format[i]);
        }
    }
}


#endif //C_STRINGS_AND_LISTS_PRINTE_H
