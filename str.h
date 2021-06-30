//
// Created by evanm on 2021-06-28.
//

/**
 * @author Evan Morrison
 * @version 1.3.00
 * @since 1.0
 */

#ifndef STRINGS_STR_H
#define STRINGS_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"
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
char charAt(string *String, unsigned index);
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

/**
 * Makes a string Array.
 * <p>
 *      Will Take Either a char*,
 *      an already made string or
 *      a null
 * </p>
 * @param type takes a type_t Either CHAR, STRING or null.
 * @param line Takes a Line either char*, string or NULL.
 * @return returns the string array as a str.
 */
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
    if (index >= len(String)) ERROR(0, 3, index, len(String), "char charAt(string *String, unsigned index)");
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
 * Retrieves the string stored in specific location of String.
 * @param String Takes a string array or str as input.
 * @param index takes the index position of the string user wants.
 * @return returns string at index position given.
 */
string *get(str *String, unsigned index){
    if (index >= len(String)) ERROR(0, 3, index, len(String), "string *get(str *String, unsigned index);");
    return &String -> cont[index];
}

/**
 * Same as {@link #get} except will return the char* instead
 * @param String Takes a string array or str as input.
 * @param index takes the index position of the string user wants.
 * @return returns char* at index position given.
 */
char *getString(str *String, unsigned index){
    if (index >= len(String)) ERROR(0, 3, index, len(String), "string *get(str *String, unsigned index);");
    return String -> cont[index].string;
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

/**
 * Frees a dynamically allocated string array or str.
 * @param String takes a string array or str*.
 */
void freeStr(str *String){
    freeString(String -> cont);
    free(String);
}
/// Cleaning Protocols END


/// Arrays START

/**
 * appends a string to a string array or str.
 * <p>
 *      Can Take Either a CHAR or a STRING.
 * </p>
 * @param array takes the string array or str wanted to be added too.
 * @param type Takes type either CHAR or STRING.
 * @param appendVoid Takes either a string or char*.
 */
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

/**
 * Quick append a string to array.
 * @param array takes the string array or str wanted to be added too.
 * @param appendString Takes a string.
 */
void appendStr(str *array, string *appendString){
    append(array, STRING, appendString);
}

/**
 * Quick append a char* to array.
 * @param array takes the string array or str wanted to be added too.
 * @param appendChar Takes a char*.
 */
void appendChar(str *array, char *appendChar){
    append(array, CHAR, appendChar);
}

/**
 * Pops the string at the index position. If index is out of bounds function will push an error.
 * <p>
 *      Will returns the popped string. If you do not want the popped string use {@link #pop(str*, char*}
 * </p>
 * @param array Takes string array or str holding element wanting to be popped.
 * @param index Takes unsigned integer for index position.
 * @return returns the popped string if wanted.
 */
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

/**
 * Pops a string at certain index position. Will not return string and will instead free it from memory.
 * @param array Takes a string array or str.
 * @param index takes unsigned integer for index.
 */
void pop(str *array, unsigned index){
    string *temp = popAdv(array, index);
    freeString(temp); // why do I do this? Because I want to be able to receive the popped string with popAdv and I don't want an extremely bloated source code with duplicates everywhere.
}

/**
 * Pops Based on char* instead of index position. will pop first element found which might be an issue.
 * @param array takes a string array or str.
 * @param word takes a char*.
 * @return returns 1 if function managed to pop an element. returns 0 if it could not find word.
 */
int popStr(str *array, char *word){
    for (int i = 0; i < len(array); i++){
        if (strNcmp(array -> cont[i].string, word, len(&array -> cont[i])) == 0){
            pop(array, i);
            return 1;
        }
    }
    return 0;
}

/**
 * Pops Based on string instead of index position. will pop first element found which might be an issue.
 * @param array takes a string array or str.
 * @param word takes a char*.
 * @return returns 1 if function managed to pop an element. returns 0 if it could not find word.
 */
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

/**
 * Prints Fancy Stuff Does not work probably, Not sure I started working on it, ran into a problem and so never completed it.
 * @param format
 * @param ...
 */
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
