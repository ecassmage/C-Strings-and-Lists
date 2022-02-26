//
// Created by evanm on 2021-07-01.
//

#ifndef C_STRINGS_AND_LISTS_ARRSREDUNDENT_H
#define C_STRINGS_AND_LISTS_ARRSREDUNDENT_H
#include "Oldstr.h"

typedef struct{
    unsigned len;
    string *cont;
} str;

str *Str(type_t type, void *line); // Makes String Arrays
string *get(str *String, unsigned index);
char *getString(str *String, unsigned index);
void freeStr(str *String);

/// Arrays START
void append(str *array, type_t type, void *appendVoid);
void appendStr(str *array, string *appendString);
void appendChar(str *array, char *appendChar);
string *popAdv(str *array, unsigned index);
void pop(str *array, unsigned index);
int popStr(str *array, char *word);
int popString(str *array, string *word);
/// Arrays END

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

/**
 * Retrieves the string stored in specific location of String.
 * @param String Takes a string array or str as input.
 * @param index takes the index position of the string user wants.
 * @return returns string at index position given.
 */
string *get(str *String, unsigned index){
    if (index >= len(String)) errorString(0, 3, index, len(String), "string *get(str *String, unsigned index);");
    return &String -> cont[index];
}

/**
 * Same as {@link #get} except will return the char* instead
 * @param String Takes a string array or str as input.
 * @param index takes the index position of the string user wants.
 * @return returns char* at index position given.
 */
char *getString(str *String, unsigned index){
    if (index >= len(String)) errorString(0, 3, index, len(String), "string *get(str *String, unsigned index);");
    return String -> cont[index].string;
}

/**
 * Frees a dynamically allocated string array or str.
 * @param String takes a string array or str*.
 */
void freeStr(str *String){
    freeString(String -> cont);
    free(String);
}

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
            errorString(1, 0, "Expected [CHAR, STRING] got: ", enumFinder(type), "\n\tvoid append(str *array, type_t type, void *appendVoid);\n");  // Error Message Generator
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
    if (index >= len(array) || index < 0) errorString(0, 3, index, len(array), "Negative Wrap-Around Error\n\tstring *pop(str *array, unsigned index)");
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

#endif //C_STRINGS_AND_LISTS_ARRSREDUNDENT_H
