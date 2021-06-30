//
// Created by evanm on 2021-06-28.
//
// Totally Forgot to Add this to this Header. Woops. :)
/**
 * @author Evan Morrison
 * @version 1.3.00
 * @since 1.0
 */

#ifndef STRINGS_ERROR_H
#define STRINGS_ERROR_H

#include <stdlib.h>
#include <stdarg.h>

/**
 * This is an Error Generating Function
 * <p>
 *      Makes it the color of red depending on your console of choice.
 *      0: Index out of Range
 *      1: Incorrect type_t used
 *      2: Failed to Allocate Space
 *      254: Custom Error (Can be Customized Entirely but they need to all be char*)
 *      255: Unknown Error
 * </p>
 * @param num Takes Number to Determine the Error.
 * @param Args Takes number of extra arguments to be sent over.
 * @param ... Takes all the Arguments
 */
void ERROR(unsigned num, unsigned Args, ...){
    va_list lis;
    va_start(lis, Args);
    printf("\033[0;31m");
    switch (num){
        case 0:
            printf("ERROR: Index Out Of Range");  // Out of Range Index Errors;
            if (Args > 0) printf(": [%d]", va_arg(lis, unsigned));
            if (Args > 1) printf(" > len(%d)", va_arg(lis, unsigned));
            if (Args > 2) printf("\n\t%s", va_arg(lis, char*));
            printf("\n");
            break;
        case 1:
            printf("ERROR: incorrect type_t used: %s", va_arg(lis, char*));
            printf("%s", va_arg(lis, char*));
            printf("%s", va_arg(lis, char*));
            printf("\n");
            break;
        case 2:
            printf("ERROR: Failed To Allocate Space\n");
            for (int i = 0; i < Args; i++) printf("%s", va_arg(lis, char*));
            break;
        case 254:
            for (int i = 0; i < Args; i++) printf("%s", va_arg(lis, char*));
            break;
        default:
            printf("ERROR: Unknown Error.");
            for (int i = 0; i < Args; i++) printf("%s", va_arg(lis, char*));
            printf("\n");
            break;
    }
    printf("\033[0m");  // I love ANSI Codes. So nice Did this in Java for one of my labs for some reason for the fun of it.
    exit((int) num);
}
#endif //STRINGS_ERROR_H
