//
// Created by evanm on 2021-06-30.
//
// I now know what this does. It sets a define that allows you to check in other headers or source files if this specific header is in fact included.
#ifndef C_STRINGS_AND_LISTS_PRINTE_H
#define C_STRINGS_AND_LISTS_PRINTE_H

#include <stdio.h>
#include "Oldstr.h"
#include "Oldlist.h"
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

void experiment(list *ListPrint, unsigned newLine, unsigned type) {
    printf("[");
    for (int i = 0; i < len(ListPrint); i++) {
        if (i != 0) printf(", ");
        switch (ListPrint->list[i].type) {
            case INT:
                (type ? printf("(INT)") : printf("%d", *(int*) ListPrint -> list[i].element)); break;
            case DOUBLE:
                (type ? printf("(DOUBLE)") : printf("%lf", *(double*) ListPrint -> list[i].element)); break;
            case LDOUBLE:
                (type ? printf("(LONGDOUBLE)") : printf("%Lf", *(long double*) ListPrint -> list[i].element)); break;
            case FLOAT:
                (type ? printf("(FLOAT)") : printf("%f", *(float*) ListPrint -> list[i].element)); break;
            case STRING:
                isHere(STRINGS_STR_H, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
                (type ? printf("(STRING)") : printf("'%s'", getStr((string*) ListPrint -> list[i].element)));
                break;
            case CHAR:
                printf("(CHAR)");
                break;
            case CHARp:
                printf("(CHAR*)");
                break;
            case BOOL:
                isHere("_STDBOOL_H", "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
                (type ? printf("(BOOL)") : printf("'%d'", (bool) ListPrint -> list[i].element)));
                #ifdef _STDBOOL_H
                                printf("(BOOL)");
                #else
                                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "<stdbool.h>");
                #endif
                break;
            case LIST:
                printf("(LIST):");
                printListt((list *) ListPrint->list[i].element, 0);
                break;
            case null:
                printf("(NULL)");
                break;

            default:
                errorList(1, 1, "\tvoid printList(list *ListPrint, bool newLine);\n");
        }
    }
    printf("]");
    if (newLine) printf("\n");
}

#endif //C_STRINGS_AND_LISTS_PRINTE_H
