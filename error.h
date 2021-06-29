//
// Created by evanm on 2021-06-28.
//

#ifndef STRINGS_ERROR_H
#define STRINGS_ERROR_H

#include <stdlib.h>
#include <stdarg.h>

void ERROR(unsigned num, unsigned Args, ...){
    va_list list;
    va_start(list, Args);
    switch (num){
        case 0:
            printf("ERROR: Index Out Of Range");
            if (Args > 0) printf(": [%d]", va_arg(list, unsigned));
            if (Args > 1) printf(" > len(%d)", va_arg(list, unsigned));
            if (Args > 2) printf("%s", va_arg(list, char*));
            printf("\n");
            exit(0);
        case 1:
            printf("ERROR: incorrect type_t used: %s", va_arg(list, char*));
            printf("%s", va_arg(list, char*));
            printf("%s", va_arg(list, char*));
            printf("\n");
            exit(1);
        case 2:
            printf("Failed To Allocate Space\n %s", va_arg(list, char*));
            exit(2);
    }
    exit(0);
}
#endif //STRINGS_ERROR_H
