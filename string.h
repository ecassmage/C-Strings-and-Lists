//
// Created by evanm on 2021-06-09.
//

/**
 * I Fervently hate C char[] which take the place of the strings found in other languages like python and java,
 * which hide this annoying bit of coding in the background, so I have decided to bring
 * Python string sort of to C for myself since I like working with strings quite a bit.
 *
 * This Allows for a far more versatile string in c. Similar to languages like python and java in my opinion.
 *
 * @author Evan Morrison
 * @version 1.3.3
 * @since 1.0.0
 */

#ifndef MAIN_C_STRING_H
#define MAIN_C_STRING_H

#include <stdlib.h>
#include <stdarg.h>

typedef struct overheadString{
    unsigned int lenArr;
} overheadString;


/**
 * Structure for str holds information like the char array and length of string. as well as some array information.
 */
typedef struct str{
    char *stringContainer;
    unsigned int len;
    overheadString *lenFo;
} str;

void ERROR(char errorMessage[]){
    printf("ERROR: %s\n", errorMessage);
    exit(0);
}

/**
 * Writes string, Would be Private if I New how to make it Private.
 * @param container Takes a str which which contain the character array
 * @param positionStart Takes an int for index position inside str which will begin writing str.
 * @param word takes char array for word wanted to be added.
 * @return returns int for where ptr inside str finished at.
 */
int strWrite(str *container, int positionStart, const char word[]);

/**
 * Writes a String to str structure.
 * <p>
 *  This Writes a String taking an input of a char array before then writing the information needed to a str structure.
 * <\p>
 * @param newStr takes a char array for the str.
 * @return returns a malloc written string.
 */
str* String(char newStr[]);

/**
 * returns char at indexed position.
 * @param string takes str wanted to look at.
 * @param index takes index for position wanted to get
 * @return returns char at position specified by @param index
 */
char charAt(str *string, unsigned int index);

/**
 * replaces char at specific @param index inside @param string with @param chr.
 * @param string takes a str you want to replace char inside.
 * @param index takes index of char location.
 * @param chr takes chr wanted to replace with.
 */
void replaceChar(str *string, unsigned int index, char chr);

/**
 * returns length of string
 * @param string takes str of what you want length of.
 * @return returns length of @param string.
 */
unsigned len(str *string);

/**
 * sets length of an array of strings.
 * <p>
 *  I wish I knew how to private this as well. Don't use this unless you know what you are doing. It will break arrays potentially and cause reading of non allocated memory.
 * </p>
 * @param string takes a str.
 * @param num takes an unsigned int of length of array
 */
void setLenArr(str **string, unsigned num);

/**
 * measures length of char array. replacement for strlen from <string.h>
 * <p>
 *  I wanted to keep <string.h> out of these headers since it is very similar to the name of this and while nothing would happen from this I still didn't like this.\n
 *  A \0 is needed or this is most likely going to go well past the end of the array.
 * </p>
 * @param string Takes char array of what is wanted to be measured.
 * @return returns unsigned int of char array length.
 */
unsigned strLen(const char *string);

/**
 * does what strncmp does but without <string.h> being needed
 * @param string1 takes a char array to compare
 * @param string2 takes a char array to compare
 * @param num takes an int that caps amount of chars to be compared
 * @return
 */
signed strnCmp(const char *string1, const char *string2, unsigned num);

/**
 * Measures length of string or something.
 * <p>
 *  IDK why this is even here as it effectively is the same as len, but I'm not gonna do anything with it. I think this is just because I copy pasted replace from another str header I was working on
 *  until it got too old and I no longer had the desire to work on it anymore. and this was something that got pulled along with it.
 * </p>
 * @param string takes a str
 * @return returns length of str
 */
unsigned int measureLength(str *string);

/**
 * Makes a copy of the str.
 * @param string takes a str to copy
 * @return returns copied string
 */
str *copyStr(str *string);

/**
 * splits string into array
 * @param stringToSplit takes str to split
 * @param characterToSplitAt takes splitting char
 * @return returns array of strings
 */
str **split(str *stringToSplit, char characterToSplitAt);

/**
 * concatenates a single char array to a string
 * @param string takes a str to take @param arr
 * @param arr takes a char array to concatenate
 */
void concatSingle(str *string, char arr[]);

/**
 * concatenates a single char to a string
 * @param string takes a str to take @param chr
 * @param chr takes a char to concatenate
 */
void concatSingleChar(str *string, char chr);

/**
 * Concatenates many char arrays to a str
 * @param string takes a str to take the char arrays
 * @param num takes an int which defines how many char arrays are wanted to be concatenated.
 * @param ... takes theoretically infinite numbers of char arrays to concatenate.
 */
void concat(str *string, int num, ...);

/**
 * Finds an instance of char specified.
 * @param string takes a str to look through.
 * @param instance takes a char for what user is looking for.
 * @return returns number of instances found.
 */
int findInstance(str *string, char instance);

/**
 * Replaces string with new string information.
 * <p>
 *  Just changes out the old char array the str was holding with the new char array.
 * </p>
 * @param string takes a str.
 * @param newString takes a char array.
 */
void replaceStr(str *string, char newString[]);

/**
 * replaces all chars found in str with new char
 * <p>
 *  This will replace words/letters/symbols/whatever else is legal with a new word/letter/symbol/whatever else is legal.
 * </p>
 * @param string takes a str to parse through.
 * @param replace takes a char array to find and replace in @param string.
 * @param replaceWith takes a char array to replace @param replace with.
 */
void replace(str *string, char replace[], char replaceWith[]);

/**
 * Gets the char array of a str.
 * @param string takes a str.
 * @return returns @param string char array.
 */
char *getStr(str *string);

/**
 * clears the Str char array.
 * @param string takes a str to clean up
 */
void clearStr(str *string);

/**
 * deallocates str structure. for cleaning if needed.
 * @param string
 */
void deleteStr(str *string);

overheadString *getArrInfo(str **array){
    return array[0] -> lenFo;
}

int strWrite(str *container, int positionStart, const char word[]){
    int c = 0;
    while (word[c] != '\0') {
        container -> stringContainer[positionStart + c] = word[c];
        c++;
    }
    return c;
}

str *StringArr(char newStr[], overheadString *lengthSizes){
    str *string = (str*) malloc(sizeof(str));
    string -> stringContainer = (char*) malloc((strLen(newStr) + 1) * sizeof(char));
    string -> lenFo = lengthSizes;
    if (string == NULL) ERROR("Unable to allocate Memory");
    string -> len = strWrite(string, 0, newStr);
    string -> lenFo -> lenArr++;
    string -> stringContainer[len(string)] = '\0';
    return string;
}

str* String(char newStr[]){
    overheadString *temp = (overheadString*) malloc(sizeof(overheadString));
    temp -> lenArr = 0;
    return StringArr(newStr, temp);
}

char charAt(str *string, unsigned int index){
    if (index > string -> len)
        ERROR("IndexOutOfRange");
    return string -> stringContainer[index];
}

void replaceChar(str *string, unsigned int index, char chr){
    string -> stringContainer[index] = chr;
}

unsigned len(str *string){
    return string -> len;
}

unsigned lenArray(str **string){
    return string[0] -> lenFo -> lenArr;
}

void setLenArr(str **string, unsigned num){
    string[0] -> lenFo -> lenArr = num;
}

void upLenArr(str **arr) {
    arr[0] -> lenFo -> lenArr++;
}
void downLenArr(str **arr) {
    arr[0] -> lenFo -> lenArr--;
}

unsigned strLen(const char *string){
    unsigned int i = 0;
    for (; string[i] != '\0'; i++);
    return i;
}

signed strnCmp(const char *string1, const char *string2, unsigned num){
    int i = 0;
    for (; string1[i] != '\0' && string2[i] && i < num; i++){
        if (string1[i] < string2[i]){
            return -1;
        }
        else if (string1[i] > string2[i]){
            return 1;
        }
    }
    if (i == num) return 0;
    if (strLen(string1) > strLen(string2)) return 1;
    else if (strLen(string1) == strLen(string2)) return 0;
    else return -1;
}

unsigned int measureLength(str *string){
    unsigned int c = 0;
    while (string -> stringContainer[c] != '\0') c++;
    return c;
}

str *copyStr(str *string){
    str *newString = (str*) malloc(sizeof(str));
    newString -> stringContainer = (char*) malloc((len(string) + 1) * sizeof(char));
    for (int i = 0; charAt(string, i) != '\0'; i++){
        replaceChar(newString, i, charAt(string, i));
    }
    newString -> len = string -> len;
    newString -> stringContainer[len(newString)] = '\0';
    return newString;
}

str **split(str *stringToSplit, char characterToSplitAt){
    str **stringArr = (str**) malloc(findInstance(stringToSplit, characterToSplitAt) * sizeof(str*));
    str *strTemp = (str*) malloc(sizeof(char));
    strTemp = String("");
    int strFoundToSplit = 0;
    for (int i = 0; charAt(stringToSplit, i) != '\0'; i++){
        if (charAt(stringToSplit, i) != characterToSplitAt){
            concatSingleChar(strTemp, charAt(stringToSplit, i));
        }
        else{
            stringArr[strFoundToSplit] = copyStr(strTemp);
            clearStr(strTemp);
            strTemp = String("");
            strFoundToSplit++;
        }
    }
    stringArr[strFoundToSplit] = copyStr(strTemp);
    deleteStr(strTemp);
    return stringArr;
}

void concatSingle(str *string, char arr[]){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + strLen(arr) + 1) * sizeof(char));
    unsigned int i = 0;
    for (; arr[i] != '\0'; i++){
        string -> stringContainer[len(string)+i] = arr[i];
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += strLen(arr);
}

void concatStr(str *string, str *stringConcat){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + len(stringConcat) + 1) * sizeof(char));
    unsigned i = 0;
    for (; charAt(stringConcat, i) != '\0'; i++){
        string -> stringContainer[len(string)+i] = charAt(stringConcat, i);
    }
    string -> stringContainer[len(string)+i] = '\0';
    string -> len += len(stringConcat);
}

void concatSingleChar(str *string, char chr){
    string -> stringContainer = (char*) realloc(string -> stringContainer, (len(string) + 2) * sizeof(char));
    string -> stringContainer[len(string)] = chr;
    string -> len++;
    string -> stringContainer[len(string)] = '\0';
}

void concat(str *string, int num, ...){
    va_list varList;
    va_start(varList, num);
    for (int i = 0; i < num; i++){
        concatSingle(string, va_arg(varList, char*));
    }
}

int findInstance(str *string, char instance){
    int countNumber = 0;
    for (int i = 0; charAt(string, i) != '\0'; i++){
        if (charAt(string, i) == instance) countNumber++;
    }
    return countNumber;
}

void replaceStr(str *string, char newString[]){
    free(string -> stringContainer);
    string -> stringContainer = (char*) malloc((strLen(newString) + 1) * sizeof(char));
    for (int i = 0; newString[i] != '\0'; i++){
        string -> stringContainer[i] = newString[i];
    }
    string -> stringContainer[strLen(newString)] = '\0';
    string -> len = strLen(newString) + 1;
}

void replace(str *string, char replace[], char replaceWith[]){
    for(int i = 0; string -> stringContainer[i] != '\0'; i++){
        if (string -> stringContainer[i] == replace[0]){
            if (strnCmp(string -> stringContainer + i, replace, strLen(replace)) == 0){
                if (strLen(replaceWith) > strLen(replace)){
                    string -> stringContainer = (char*) realloc(string -> stringContainer, (measureLength(string) + strLen(replaceWith) - strLen(replace)) * sizeof(char));
                    for (unsigned int j = (measureLength(string) + strLen(replaceWith) - strLen(replace)); i + strLen(replace) < j; j--){
                        string -> stringContainer[j] = string -> stringContainer[j - strLen(replaceWith) + strLen(replace)];
                    }
                    for(int j = 0; replaceWith[j] != '\0'; j++){
                        string -> stringContainer[i + j] = replaceWith[j];
                    }
                    string -> stringContainer[measureLength(string)] = '\0';
                }
                else {
                    int j = 0;
                    for(; replaceWith[j] != '\0'; j++){
                        string -> stringContainer[i + j] = replaceWith[j];
                    }
                    for (j = i + j; string -> stringContainer[j + (strLen(replace) - strLen(replaceWith))] != '\0'; j++){
                        string -> stringContainer[j] = string -> stringContainer[j + (strLen(replace) - strLen(replaceWith))];
                    }
                    string -> stringContainer = (char*) realloc(string -> stringContainer, (measureLength(string) + strLen(replaceWith) - strLen(replace) ) * sizeof(char));
                    string -> stringContainer[j] = '\0';
                }
                i += (int) strLen(replaceWith) - 1;
            }
        }
    }
    string -> len = measureLength(string);
}

char *getStr(str *string){
    return string -> stringContainer;
}

void clearStr(str *string){
    free(string -> stringContainer);
}

void deleteStr(str *string){
    clearStr(string);
    free(string -> lenFo);
    free(string);
}

#endif //MAIN_C_STRING_H