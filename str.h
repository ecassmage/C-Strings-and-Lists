//
// Created by evanm on 2021-07-01.
//

#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct{
    unsigned len;
    char *string;
} str;


// This is a bunch of stuff that list.h and str.h share so they need to be encapsulated between these #ifndef stuff so they don't collide with each other.
// I DON'T BELIEVE THIS WILL WORK ON ANY STRUCTURE NOT FORMATTED LIKE MINE ARE WHERE len IS THE FIRST VARIABLE STORED.
#ifndef LIST_H
unsigned len(void *string){
    if ((str*) string == NULL) return 0;
    return ((str*) string) -> len;
}
typedef enum{  // This is the Building Base of the Lists. Could have used char arrays as well but didn't want to.
    INT,
    DOUBLE, FLOAT, LDOUBLE,
    STRING,
    CHAR,
    CHARp,
    BOOL,
    LIST,
    DEBUG,
    null,
    EMPTY_T  // Basically a Default NULL which isn't actually a NULL. So NULL can be used without limitations.
} type_t;
#endif


void errorString(unsigned num, unsigned Args, ...){
    va_list lis;
    va_start(lis, Args);
#ifdef STRINGS_ERROR_H
    ERROR(num, Args, lis);  // IDK Sort of a Meme function which needs list.h
#endif
    printf("\033[0;31m");
    printf("We Caught an ERROR message in \"str.h\" but \"ERROR.h\" was not included so this message played.\n");
    exit(253);
}



/// Creating String and Str START
str *mkString(const char *line);  // Makes Strings
str *String();  // Makes Strings
/// Creating String and Str END


/// String Manipulation START
char charAt(str *String, unsigned index);
char *getStr(str *String);
/// String Manipulation END


/// Length Measurements START
unsigned strLen(const char *string);

/**
 * Returns length of what is given. I Only Guarantee Works with str and string.
 * @param str Takes a void reference pointer.
 * @return returns an unsigned int for length of string or str.
 */
unsigned len(void *str);
/// Length Measurements END

/// Deluxe <string.h> Rip Off START
signed strNcmp(const char *string1, const char *string2, unsigned num);
/// Deluxe <string.h> Rip Off START


/// Cleaning Protocols START
void freeChar(char *chr);
void freeString(str *String);
/// Cleaning Protocols END

str *mkString(const char *line){
    str *string = (str*) malloc(sizeof(str));
    string -> string = (char*) malloc((strLen(line) + 1) * sizeof(char));
    for (int i = 0; ; i++){
        string -> string[i] = line[i];
        if (line[i] == '\0') break;
    }
    string -> len = strLen(line);
    return string;
}

str *String(){
    str *string = (str*) malloc(sizeof(str));
    string -> string = (char*) malloc(1);
    string -> string[0] = '\0';
    string -> len = 0;
    return string;
}
/// Creating String and Str END


/// Concatenation START
void concatSC(str *stringType, char chr){
    stringType -> string = (char*) realloc(stringType -> string, (len(stringType) + 2) * sizeof(char));
    stringType -> string[len(stringType)] = chr;
    stringType -> len++;
    stringType -> string[len(stringType)] = '\0';
}

void concatSingleStr(str *String, str *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + len(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; charAt(arr, i) != '\0'; i++){
        String -> string[len(String)+i] = charAt(arr, i);
    }
    String -> string[len(String)+i] = '\0';
    String -> len += len(arr);
}

void concatSingle(str *String, const char *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + strLen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        String -> string[len(String)+i] = arr[i];
    }
    String -> string[len(String)+i] = '\0';
    String -> len += strLen(arr);
}

void concat(str *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingle(string, va_arg(varList, char*));
    }
}

void concatStr(str *String, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingleStr(String, va_arg(varList, str*));
    }
}
/// Concatenation END


/// String Manipulation START
char charAt(str *String, unsigned index){
    if (index >= len(String)) errorString(0, 3, index, len(String), "char charAt(string *String, unsigned index)");
    return String -> string[index];
}

char *getStr(str *String){
    return String -> string;
}

void replace(str *stringType, const char *replace, const char *replaceWith){
    str *tempNewString = String();
    for (unsigned i = 0; stringType -> string[i] != '\0'; i++){
        if (charAt(stringType, i) == replace[0] && strNcmp(getStr(stringType) + i, replace, strLen(replace)) == 0){
            concatSingle(tempNewString, replaceWith);  // Checks for a Match at the i index position
            i += strLen(replace) - 1;  // the -1 is because 1 of the Characters being overwritten would have already been counted at end of for loop iteration
        }
        else concatSC(tempNewString, charAt(stringType, i));  // Didn't find match so copying character
    }
    freeChar(stringType -> string);
    stringType -> string = (char*) malloc((len(tempNewString) + 1) * sizeof(char));
    for (int i = 0; ; i++){
        stringType -> string[i] = charAt(tempNewString, i);
        if (charAt(tempNewString, i) == '\0') break;
    }
    stringType -> len = tempNewString -> len;
    freeString(tempNewString);
}
/// String Manipulation END


/// Length Measurements START
unsigned strLen(const char *string){
    for (int i = 0;; i++){
        if (string[i] == '\0') return i;
    }
}

void printFull(str *String){
    if (String == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Memory Address: %p, Length: %d, String: \"%s\"\n", String, len(String), getStr(String));
}
/// Length Measurements END


/// Deluxe <string.h> Rip Off START
signed strNcmp(const char *string1, const char *string2, unsigned num) {
    int i = 0;
    for (; string1[i] != '\0' && string2[i] && i < num; i++) {
        if (string1[i] < string2[i]) {
            return -1;
        } else if (string1[i] > string2[i]) {
            return 1;
        }
    }
    if (i == num) return 0;
    if (strLen(string1) > strLen(string2)) return 1;
    else if (strLen(string1) == strLen(string2)) return 0;
    else return -1;
}
/// Deluxe <string.h> Rip Off END


/// Cleaning Protocols START
void freeChar(char *chr){
    free(chr);
}
void freeString(str *String){
    freeChar(String -> string);
    free(String);
}
/// Cleaning Protocols END


/// Input/Output START
/// Input/Output END






#endif //C_STRINGS_AND_LISTS_STR_H
