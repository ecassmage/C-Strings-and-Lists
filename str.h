//
// Created by evanm on 2021-06-28.
//

/**
 * @author Evan Morrison
 * @version 1.2
 * @since 1.0
 */

#ifndef STRINGS_STR_H
#define STRINGS_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"
#define N NULL  // I dunno a short form for NULL I guess.

typedef enum{
    INT,
    DOUBLE, FLOAT, LDOUBLE,
    STRING,
    STR,
    CHAR,
    CHARp,
    BOOL,
    LIST,
    null
} type_t;

typedef struct{
    unsigned len;
    char *string;
} string;

typedef struct{
    unsigned len;
    string *cont;
} str;

/**
 * This Shall be Abused by me to make a functional language into a pseudo not really OOP Language
 * In Fact Because of looking into this I have figured out how to create a Python List here in C. Maybe I will Do that After.
 */

char *enumFinder(type_t type){
    switch(type){
        case CHAR: return "CHAR";
        case STRING: return "STRING";
        case null: return "null";
        default: return N;
    }
}

/// Creating String and Str START
string *mkString(const char *line);  // Makes Strings
string *newString(type_t type, void *line);  // Makes Strings
string *String();  // Makes Strings

str *Str(type_t type, void *line); // Makes String Arrays
/// Creating String and Str END


/// String Manipulation START
char charAt(string *String, unsigned i);
char *getStr(string *String);
string *get(str *String, unsigned index);
char *getString(str *String, unsigned index);
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
void freeString(string *String);
void freeStr(str *String);
/// Cleaning Protocols END

/// Arrays START
void append(str *array, type_t type, void *appendVoid);
void appendStr(str *array, string *appendString);
void appendChar(str *array, char *appendChar);
string *popAdv(str *array, unsigned index);
void pop(str *array, unsigned index);
int popStr(str *array, char *word);
int popString(str *array, string *word);
/// Arrays END




/// Creating String and Str START
/**
 * Makes The String Based on Char Array Input
 * @param line Takes a Char Pointer Reference to an array.
 * @return Returns a string structure
 */
string *mkString(const char *line){
    string *str = (string*) malloc(sizeof(string));
    str -> string = (char*) malloc((strLen(line) + 1) * sizeof(char));
    for (int i = 0; ; i++){
        str -> string[i] = line[i];
        if (line[i] == '\0') break;
    }
    str -> len = strLen(line);
    return str;
}

string *newString(type_t type, void *line){
    string *str;
    switch (type) {
        case CHAR:
            str = mkString((char*) line);
            break;
        case null:
            str = (string*) malloc(sizeof(string));
            str -> string = (char*) malloc(1);
            str -> string[0] = '\0';
            str -> len = 0;
            break;
        default:
            printf("Dunno What you Talking About\n");
            exit(0);
    }

    return str;
}

string *String(){
    return newString(null, N);
}

str *Str(type_t type, void *line){ // maybe use ... Dunno
    str *string = (str*) malloc(sizeof(str));

    switch (type) {
        case CHAR:
            string -> cont = mkString((char*) line);
            string -> len = 1;
            break;
        case STRING:
            string -> cont = line;
            string -> len = 1;
            break;
        case null:
            string -> cont = NULL;
            string -> len = 0;
            break;
        default:
            printf("Dunno What you Talking About\n");
            exit(0);
    }

    return string;
}
/// Creating String and Str END


/// Concatenation START
void concatSC(string *stringType, char chr){
    stringType -> string = (char*) realloc(stringType -> string, (len(stringType) + 2) * sizeof(char));
    stringType -> string[len(stringType)] = chr;
    stringType -> len++;
    stringType -> string[len(stringType)] = '\0';
}
void concatSingleStr(string *String, string *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + len(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; charAt(arr, i) != '\0'; i++){
        String -> string[len(String)+i] = charAt(arr, i);
    }
    String -> string[len(String)+i] = '\0';
    String -> len += len(arr);
}
void concatSingle(string *String, const char *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + strLen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        String -> string[len(String)+i] = arr[i];
    }
    String -> string[len(String)+i] = '\0';
    String -> len += strLen(arr);
}
void concat(string *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingle(string, va_arg(varList, char*));
    }
}

void concatStr(string *String, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingleStr(String, va_arg(varList, string*));
    }
}
/*
void concatInt(string *String, int num){
    char buffer[33] = {'\0'};
    itoa(num, buffer, 10);  // itoa does not work
    concatSingle(String, buffer);
}*/
/// Concatenation END


/// String Manipulation START
char charAt(string *String, unsigned i){
    return String -> string[i];
}

char *getStr(string *String){
    return String -> string;
}

string *get(str *String, unsigned index){
    if (index >= len(String)) ERROR(0, 3, index, len(String), "\n\tstring *get(str *String, unsigned index);");
    return &String -> cont[index];
}

char *getString(str *String, unsigned index){
    if (index >= len(String)) ERROR(0, 3, index, len(String), "\n\tstring *get(str *String, unsigned index);");
    return String -> cont[index].string;
}

void newReplace(string *stringType, const char *replace, const char *replaceWith){
    string *tempNewString = String();
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

unsigned len(void *str){
    if ((string*) str == N) return 0;
    return ((string*)str) -> len;
}

void printFull(string *String){
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
void freeString(string *String){
    freeChar(String -> string);
    free(String);
}
void freeStr(str *String){
    freeString(String -> cont);
    free(String);
}
/// Cleaning Protocols END


/// Arrays START
void append(str *array, type_t type, void *appendVoid){
    array -> cont = (string*) realloc(array -> cont, (len(array) + 1) * sizeof(string));
    switch(type){
        case CHAR:
            array -> cont[len(array)] = *mkString((char*) appendVoid);
            break;
        case STRING:
            array -> cont[len(array)] = *((string*) appendVoid);
            break;
        default:
            ERROR(1, 0, "Expected [CHAR, STRING] got: ", enumFinder(type), "\n\tvoid append(str *array, type_t type, void *appendVoid);\n");  // Error Message Generator
            break;
    }
    array -> len++;
}

void appendStr(str *array, string *appendString){
    append(array, STRING, appendString);
}
void appendChar(str *array, char *appendChar){
    append(array, CHAR, appendChar);
}

string *popAdv(str *array, unsigned index){
    if (index < 0) index += (int) len(array);
    if (index >= len(array) || index < 0) ERROR(0, 3, index, len(array), "Negative Wrap-Around Error\n\tstring *pop(str *array, unsigned index)");
    string *temp = (string*) malloc((len(getString(array, index)) + 1) * sizeof(string));
    concatSingle(temp, getString(array, index));
    for (index++; index < len(array); index++) array[index-1] = array[index];
    array -> len--;
    array -> cont = (string*) realloc(array -> cont, array -> len * sizeof(string));
    return temp;
}
void pop(str *array, unsigned index){
    string *temp = popAdv(array, index);
    freeString(temp); // why do I do this? Because I want to be able to receive the popped string with popAdv and I don't want an extremely bloated source code with duplicates everywhere.
}
int popStr(str *array, char *word){
    for (int i = 0; i < len(array); i++){
        if (strNcmp(array -> cont[i].string, word, len(&array -> cont[i])) == 0){
            pop(array, i);
            return 1;
        }
    }
    return 0;
}
int popString(str *array, string *word){
    for (int i = 0; i < len(array); i++){
        if (&array -> cont[i] == word){
            pop(array, i);
            return 1;
        }
    }
    return 0;
}
/// Arrays END

/// Input/Output START

void print(const char *format, ...){
    va_list list;
    va_start(list, format);
    string *message = String();
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] == '%' && format[i-1] != '%' && format[i-1] != '\\'/* Probably won't work unless \\% not \% */) {
            switch (format[i + 1]) {
                case 'd':
                    //concatInt(message, va_arg(list, int));  //itoa doesn't work, need to find another around this.
                    break;
                case 'c':
                    concatSC(message, (char) va_arg(list, int));
                    break;
                case 's':
                    concatSingle(message, va_arg(list, char*));
                    break;
                case 'p':
                    concatSingle(message, va_arg(list, char*));
                    break;
                case 'a':
                    break;
            }
        }
    }
}

/// Input/Output END
#endif //STRINGS_STR_H
