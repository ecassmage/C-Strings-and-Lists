//
// Created by evanm on 2021-06-28.
//

/**
 * @author Evan Morrison
 * @version 1.4.00
 * @since 1.0
 */

#ifndef STRINGS_STR_H
#define STRINGS_STR_H "STRINGS_STR_H"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//#include "error.h"
#define N NULL  // I dunno a short form for NULL I guess. I Initially Thought This was an amazing idea but now I think it is stupid and am going to leave it here.

/**
 * This Shall be Abused by me to make a functional language into a pseudo not really OOP Language
 * In Fact Because of looking into this I have figured out how to create a Python List here in C. Maybe I will Do that After.
 */
typedef enum{  // This is the Building Base of the Lists. Could have used char arrays as well but didn't want to.
    INT,
    DOUBLE, FLOAT, LDOUBLE,
    STRING,
    STR,
    CHAR,
    CHARp,
    BOOL,
    LIST,
    DEBUG,
    null,
    EMPTY_T  // Basically a Default NULL which isn't actually a NULL. So NULL can be used without limitations.
} type_t;

typedef struct{
    unsigned len;
    char *string;
} string;



char *enumFinder(type_t type){
    switch(type){
        case CHAR: return "CHAR";
        case STRING: return "STRING";
        case null: return "null";
        default: return N;
    }
}

void errorString(unsigned num, unsigned Args, ...){
    va_list lis;
    va_start(lis, Args);
#ifdef STRINGS_ERROR_H
    ERROR(num, Args, lis);
#endif
    printf("\033[0;31m");
    printf("We Caught an ERROR message in \"str.h\" but \"ERROR.h\" was not included so this message played.\n");
    exit(253);
}

/// Creating String and Str START
string *mkString(const char *line);  // Makes Strings
string *newString(type_t type, void *line);  // Makes Strings
string *String();  // Makes Strings


/// Creating String and Str END


/// String Manipulation START
char charAt(string *String, unsigned index);
char *getStr(string *String);
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
/// Cleaning Protocols END





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

/**
 * Creates a new String Either feeding a char array into it or nothing. More of an Experiment more then anything.
 * @param type takes a type_t enumerator. This Wants either CHAR or null.
 * @param line takes either a char* or just a null.
 * @return returns the new string.
 */
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

/**
 * Creates an empty string.
 * @return returns the empty string.
 */
string *String(){
    return newString(null, N);
}

/// Creating String and Str END


/// Concatenation START

/**
 * Concatenates Single Chars. Mostly for internal Use Only.
 * @param stringType Takes the string you want to concatenate onto.
 * @param chr takes a char user wants to add to the string.
 */
void concatSC(string *stringType, char chr){
    stringType -> string = (char*) realloc(stringType -> string, (len(stringType) + 2) * sizeof(char));
    stringType -> string[len(stringType)] = chr;
    stringType -> len++;
    stringType -> string[len(stringType)] = '\0';
}

/**
 * Concatenates a single string. Same as the Others but is meant to merge two strings together.
 * @param String Takes the string you want to concatenate onto.
 * @param arr Takes a string user wants to add to the string.
 */
void concatSingleStr(string *String, string *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + len(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; charAt(arr, i) != '\0'; i++){
        String -> string[len(String)+i] = charAt(arr, i);
    }
    String -> string[len(String)+i] = '\0';
    String -> len += len(arr);
}

/**
 * Concatenates a single char*. Same as the Others but is meant to merge a char* to a string.
 * @param String Takes the string you want to concatenate onto.
 * @param arr Takes a char* user wants to add to the string.
 */
void concatSingle(string *String, const char *arr){
    String -> string = (char*) realloc(String -> string, (len(String) + strLen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        String -> string[len(String)+i] = arr[i];
    }
    String -> string[len(String)+i] = '\0';
    String -> len += strLen(arr);
}

/**
 * Concatenates as many char* as you want. will need to specify how many you want concatenated.
 * @param string Takes a string user wants concatenated onto.
 * @param num Takes an unsigned integer for however many char* user wants to concatentate onto @param string.
 * @param ... Takes the char* wanted to be concatenated onto @param String.
 */
void concat(string *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingle(string, va_arg(varList, char*));
    }
}

/**
 * Same as concat except for it concatenates strings instead of char*.
 * @param String Takes a string user wants concatenated onto.
 * @param num Takes an unsigned integer for however many char* user wants to concatentate onto @param string.
 * @param ... Takes the strings wanted to be concatenated onto @param String.
 */
void concatStr(string *String, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingleStr(String, va_arg(varList, string*));
    }
}
/*  Broken so Defunct
void concatInt(string *String, int num){
    char buffer[33] = {'\0'};
    itoa(num, buffer, 10);  // itoa does not work
    concatSingle(String, buffer);
}*/
/// Concatenation END


/// String Manipulation START

/**
 * retrieves the char at specific index position.
 * @param String Takes string user wants char from
 * @param index takes index position
 * @return returns char at specific index position.
 */
char charAt(string *String, unsigned index){
    if (index >= len(String)) errorString(0, 3, index, len(String), "char charAt(string *String, unsigned index)");
    return String -> string[index];
}

/**
 * Retrieves the char* of the string. Mostly for working with the string through functions not in this or associated headers.
 * @param String Takes the String user wants to extract char* from.
 * @return returns the char* which was extracted from String.
 */
char *getStr(string *String){
    return String -> string;
}


/**
 * searches through stringType and replaces {@param replace} with {@param replaceWith} everytime it finds a section matching {@param replace}.
 * @param stringType Takes a string to search through and replace sections if {@param replace} is found.
 * @param replace Takes a char* to replace when found.
 * @param replaceWith Takes a char* for what to replace {@param replace} with.
 */
void replace(string *stringType, const char *replace, const char *replaceWith){
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

/**
 * returns the length of a char*. Just a copy of <string.h> for some reason I don't like using it so I just made my own.
 * @param string takes a char*.
 * @return returns length of char*.
 */
unsigned strLen(const char *string){
    for (int i = 0;; i++){
        if (string[i] == '\0') return i;
    }
}

/**
 * returns the length of the string. It just retrieves the structs saved size so it will always be accurate even without a '\0'
 * <p>
 *  This is as close to overloading as you can get here as the structs I write are set up to have their length as the first variable in them.
 *  This allows for string, str and list to all use this function despite it only technically working with string.
 * </p>
 * @param str Takes a string to look at
 * @return returns the length of what was sent over.
 */
unsigned len(void *str){
    if ((string*) str == N) return 0;
    return ((string*)str) -> len;
}

/**
 * prints Some information of a string.
 * Don't bother using this as it is mostly for debugging.
 * @param String Takes the string wanted to be looked at.
 */
void printFull(string *String){
    if (String == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Memory Address: %p, Length: %d, String: \"%s\"\n", String, len(String), getStr(String));
}
/// Length Measurements END


/// Deluxe <string.h> Rip Off START

/**
 * compares sections of string. Just a copy of strncmp from <string.h> for some reason I don't like using it so I just made my own.
 * @param string1 takes char* 1.
 * @param string2 takes char* 2.
 * @param num takes number of characters wanted to be compared too.
 * @return returns -1 if string1 is smaller, 0 if string1 == string2 and 1 if string2 is smaller.
 */
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

/**
 * Frees a dynamically allocated char*
 * @param chr takes a char*
 */
void freeChar(char *chr){
    free(chr);
}

/**
 * Frees a dynamically allocated string.
 * @param String takes a string*.
 */
void freeString(string *String){
    freeChar(String -> string);
    free(String);
}


/// Cleaning Protocols END


/// Input/Output START



/// Input/Output END
#endif //STRINGS_STR_H
