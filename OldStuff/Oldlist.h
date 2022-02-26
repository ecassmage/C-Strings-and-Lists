//
// Created by evanm on 2021-06-29.
//

/**
 * @author Evan Morrison
 * @version 1.4.00
 * @since 1.1
 */

/**
 * If University asks you to use C and you want to use Python Just bring Python to C.
 */
#ifndef STRINGS_LIST_H
#define STRINGS_LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/// Structures
typedef struct{
    type_t type;
    void *element;
} all;

typedef struct{
    unsigned len;
    unsigned CurrentSize;
    all *list;
} list;
/// Structures


void errorList(unsigned num, unsigned Args, ...){
    va_list lis;
    va_start(lis, Args);
#ifdef STRINGS_ERROR_H
    ERROR(num, Args, lis);
#endif
    printf("\033[0;31m");
    printf("We Caught an ERROR message in \"list.h\" but \"ERROR.h\" was not included so this message played.\n");
    exit(253);
}
void isHere(const char *def, const char *ptr, const char *header){
    if (strcmp(def, "STRINGS_STR_H") == 0){
        #ifndef STRINGS_STR_H
            errorList(3, 2, ptr, header);
        #endif
    }
    else if (strcmp(def, "_STDBOOL_H") == 0){
        #ifndef _STDBOOL_H
            errorList(3, 2, ptr, header);
        #endif
    }
}


////// Functions Below


/// List Constructor
list *List();
/// List Constructor


/// InnerWorkings
void increaseDecreaseSize(list *this);
unsigned maxLen(list *voi){return voi -> CurrentSize;}
void fillElement(all *temp, type_t type, va_list lis);
/// InnerWorkings


/// Adding Functions
void add(list *addToList, type_t type, ...);
/// Adding Functions


/// Delete Functions
all *deletec(list *lis, unsigned index);
void delete(list *lis, unsigned index);
all *delc(list *lis);
void del(list *lis);
/// Delete Functions

/// Printers
void printList(list *ListPrint, unsigned newLine);
void prints(list *ListPrint);
/// Printers

////// Functions Above



/**
 * Constructs a list.
 * @return returns an empty constructed list
 */
list *List(){
    list *newList = (list*) malloc(sizeof(list));
    newList -> list = (all*) malloc(10 * sizeof(all));
    newList -> len = 0;
    newList -> CurrentSize = 10;
    for (unsigned i = len(newList); i < maxLen(newList); i++) newList -> list[i].type = EMPTY_T;
    return newList;
}

/**
 * Don't use this. just for manipulating the size of the list.
 * @param this takes a list.
 */
void increaseDecreaseSize(list *this){
    if (maxLen(this) > 10 && (maxLen(this) / 15) > len(this)){
        // Go Down Size
        for (int i = maxLen(this) - 1; i >= maxLen(this) / 10; i--) free(this -> list[i].element);
        this -> list = (all*) realloc(this -> list, (maxLen(this) / 10) * sizeof(all));
        if (this -> list == NULL) errorList(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tDeallocating Space Failure\n");
        this -> CurrentSize /= 10;
    }
    else if (len(this) == maxLen(this)){
        // Go Up Size
        this -> list = (all*) realloc(this -> list, (maxLen(this) * 10) * sizeof(all));
        if (this -> list == NULL) errorList(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tAllocating Space Failure\n");
        this -> CurrentSize *= 10;
        for (unsigned i = len(this); i < maxLen(this); i++) this -> list[i].type = EMPTY_T;
    }
}

/**
 * Don't use this. Just fills up the lists elements with the required information.
 * @param temp Takes an element memory address.
 * @param type Takes a type.
 * @param lis Takes a va_list. // Could probably use void* instead but meh.
 */
void fillElement(all *temp, type_t type, va_list lis){
    //if (temp -> type != EMPTY_T) free(temp -> element);
    temp -> type = type;
    temp -> element = (void*) malloc(sizeof(void));
    switch(type){
        case INT:{
            int *num = (int*) malloc(sizeof(int));
            if (num == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tint *num = (int*) malloc(sizeof(int));");
            *num = va_arg(lis, int);
            temp -> element = num;
            break;
        }

        case DOUBLE:{
            double *doub = (double*) malloc(sizeof(double));
            if (doub == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tdouble *doub = (double*) malloc(sizeof(double));");
            *doub = va_arg(lis, double);
            temp -> element = doub;
            break;
        }

        case LDOUBLE:{
            long double *ldouble = (long double*) malloc(sizeof(long double));
            if (ldouble == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tlong double *ldouble = (long double*) malloc(sizeof(long double));");
            *ldouble = va_arg(lis, double);
            temp -> element = ldouble;
            break;
        }

        case FLOAT:{
            float *flo = (float*) malloc(sizeof(float));
            if (flo == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tfloat *flo = (float*) malloc(sizeof(float));");
            *flo = (float) va_arg(lis, double);
            temp -> element = flo;
            break;
        }

        case STRING:{
            isHere(STRINGS_STR_H, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
            #ifdef STRINGS_STR_H
                temp -> element = va_arg(lis, string*);
            #else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
            #endif
            break;
        }

        case CHAR:{
            char *cha = (char*) malloc(sizeof(char));
            if (cha == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tchar *cha = (char*) malloc(sizeof(char));");
            *cha = (char) va_arg(lis, int);
            temp -> element = cha;
            break;
        }

        case CHARp:{
            char *tempoChar = va_arg(lis, char*);
            char *chap = (char*) malloc((strLen((char*) tempoChar) + 1) * sizeof(char));
            if (chap == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tchar *chap = (char*) malloc((strLen((char*) tempoChar) + 1) * sizeof(char));");
            int i = 0; do {chap[i] = tempoChar[i];i++;} while (tempoChar[i] != '\0');
            temp -> element = chap;
            break;
        }

        case BOOL:{
            #ifdef _STDBOOL_H
                bool *boo = (bool*) malloc(sizeof(bool));
                if (boo == NULL) errorList(2, 1, "\tvoid fillElement(element *temp, type_t type, va_list lis)\n\tchar *chap = (char*) malloc((strLen((char*) tempoChar) + 1) * sizeof(char));");
                *boo = (bool) va_arg(lis, int);
                temp -> element = boo;
            #else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "<stdbool.h>");
            #endif
            break;
        }

        case LIST:{
            temp -> element = va_arg(lis, list*);
            break;
        }

        case null:{
            temp -> element = NULL;
            break;
        }

        case DEBUG:{
            errorList(2, 2, "\tvoid fillElement(element *temp, type_t type, va_list lis);\n\terrorList(2, 1, \"\\tvoid fillElement(element *temp, type_t type, va_list lis)\\n\\tcase DEBUG:\");",
                  "\nI love this ANSI Color. Probably won't appear on most terminals/consoles but the fact it will sometimes show up is great\n");
            break;
        }

        default:{
            errorList(1, 1, "void add(list *addToList, type_t type, void *ptr);\n\t\tdefault:");
        }

    }
}

/**
 * Adds a something and adds it to the list.
 * @param addToList takes the list wanted to receive new something.
 * @param type takes a type.
 * @param ... Takes a single argument but can take more (don't bother sending more, it is pointless and does nothing) and will add this to the list.
 */
void add(list *addToList, type_t type, ...){
    va_list lis;
    va_start(lis, type);
    increaseDecreaseSize(addToList);
    fillElement(&(addToList -> list[len(addToList)]), type, lis);
    addToList -> len++;
}

/**
 * More Advanced Version of {@link #add(list*, type_t, ...)} Where you can insert element into middle of the
 * @param addToList
 * @param index
 * @param type
 * @param ...
 */
void insert(list *addToList, int index, type_t type, ...){
    if (index < 0) index += (int) addToList -> len;
    if (index >= addToList -> len || addToList -> len < 0) errorList(0, index, len(addToList), "void insert(list *addToList, int index, type_t type, ...);");  // Catches Double Wrap Arounds', I don't like doubles, they seem dumm.;P
    va_list lis;
    va_start(lis, type);
    increaseDecreaseSize(addToList);
    for (unsigned i = len(addToList); index < i; i--) addToList -> list[i] = addToList -> list[i-1];
    fillElement(&addToList -> list[index], type, lis);
    addToList -> len++;
}

/**
 * Deletes an element from list. Uses an index to find specified element. Will send a copy of deleted element by way of an element memory address.
 * <p>
 *      If you do not want to receive a copy then use {@link #delete(list*, unsigned)}
 * </p>
 * @param lis Takes a list.
 * @param index takes an index.
 * @return returns copied element.
 */
all *deletec(list *lis, unsigned index){
    if (index < 0) index += lis -> len;
    if (index >= lis -> len || lis -> len < 0) return NULL;  // Catches Double Wrap Arounds', I don't like doubles, they seem dumm.;P
    all *temp = (all*) malloc(sizeof(all));
    temp = &lis -> list[index];
    for (index++; index < lis -> len; index++) lis -> list[index-1] = lis -> list[index];
    lis -> len--;
    increaseDecreaseSize(lis);
    return temp;
}

/**
 * Deletes an element from list. Uses an index to find specified element.
 * @param lis Takes a list.
 * @param index takes an index.
 */
void delete(list *lis, unsigned index){
    free(deletec(lis, index) -> element);
}

/**
 * Deletes the last element in the list.
 * <p>
 *      If you do not want to receive a copy then use {@link #del(list*)}
 * </p>
 * @param lis takes a list.
 * @return returns deleted element
 */
all *delc(list *lis){
    all *temp = deletec(lis, len(lis) - 1); // Ta Gaa
    return temp;
}

/**
 * Deletes the last element in the list.
 * @param lis takes a list
 */
void del(list *lis){
    free(deletec(lis, len(lis)));
}

/**
 * Helper Function. Just Call this for some information on all of the Functions I remember to talk about in here.
 */
void listHelp(){
    printf("////// Functions Below\n"
           "\n"
           "/// List Constructor\n"
           "\tlist *List();\n"
           "\t\tCreates the List.Starts out Empty Similar to Python (list = []).\n"
           "/// List Constructor\n"
           "\n\n"
           "/// InnerWorkings - Shouldn't be Touched since they are build for certain Parts of the List.\n"
           "\tvoid increaseDecreaseSize(list *this);\n"
           "\t\tChecks if the list needs to be increased or decreased. This is used as a quick all in one check for the adding and deleting functions\n"
           "\tunsigned maxLen(list *voi){return voi -> CurrentSize;}\n"
           "\t\tGets The Real Size of the List. This is meant as a way to speed up adding and deleting elements since it only occasionally have to reallocate the memory.\n"
           "\tvoid fillElement(element *temp, type_t type, va_list lis);\n"
           "\t\tFills element with stuff. Sort of for centralizing the creation and filling up of the list.\n"
           "/// InnerWorkings\n"
           "\n\n"
           "/// Adding Functions\n"
           "\tvoid add(list *addToList, type_t type, ...);\n"
           "\t\tAdds new Elements to the list. Takes the List you want added to, the type that will be added (all capitalized ie int is INT) and a single whatever is being added.\n"
           "\t\tYou can add as many as you want but only the first will actually be added so keep that in mind. Don't know why I am doing it this way. The other way I was trying was being a pain\n"
           "\t\tSo I Changed it to this.\n"
           "/// Adding Functions\n"
           "\n\n"
           "/// Delete Functions\n"
           "\telement *deletec(list *lis, unsigned index);\n"
           "\t\tDeletes a Specific element by index value. Will Also return copy of what was deleted\n"
           "\tvoid delete(list *lis, unsigned index);\n"
           "\t\tDeletes a Specific element by index value.\n"
           "\telement *delc(list *lis);\n"
           "\t\tDeletes the Last Element. Will Also return copy of what was deleted\n"
           "\tvoid del(list *lis);\n"
           "\t\tDeletes the Last Element.\n"
           "/// Delete Functions\n"
           "\n\n"
           "/// Printers\n"
           "\tvoid printList(list *ListPrint, bool newLine);\n"
           "\t\tPrints List. This is Redundant and is only separate from prints for nested lists.\n"
           "\tvoid prints(list *ListPrint);\n"
           "\t\tPrints the Entire list inside square brackets. Supports Nested Lists.\n"
           "/// Printers\n"
           "\n"
           "////// Functions Above\n\n\n"
           );
}
void printListt(list *ListPrint, unsigned newLine);
void type(const char *ptr, va_list *listOfOutputs);
void print(const char *format, ...){
    va_list listOfOutputs;
    va_start(listOfOutputs, format);
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] == '%') {
            switch (format[i + 1]) {
                case 'd':   printf("%d", va_arg(listOfOutputs, int)); break;
                case 'l':   if (format[i + 2] == 'f'){
                        printf("%lf", va_arg(listOfOutputs, double));
                        i++;
                    } else  printList(va_arg(listOfOutputs, list*), 0); break;
                case 'f':   printf("%f", va_arg(listOfOutputs, double)); break;
                case 'c':   printf("%c", (char) va_arg(listOfOutputs, int)); break;
                case 's':   printf("%s", va_arg(listOfOutputs, char*)); break;
                case '%':   printf("%%");
                case 't':
                    type(format + i + 2, &listOfOutputs);
                    if (format[i + 1] == 'l' && (format[i + 2] == 'f')) i++;
                    i++;
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

void type(const char *ptr, va_list *listOfOutputs) {
    switch (*ptr) {
        case 'd':
            va_arg(*listOfOutputs, int);
            printf("(int)");
            break;

        case 'l':
            if (*(ptr + 1) == 'f') {
                printf("(double)");
            } else {
                printf("(list)");
                list *FuckMyAss = va_arg(*listOfOutputs, list*);
                printListt(FuckMyAss, 0);  // Fix This.
            }
            break;

        case 'f':
            printf("(float)");
            break;

        case 'c':
            printf("(char)");
            break;

        case 's':
            printf("(char*)");
            break;
    }
}

void printt(const char *format, ...){
    va_list listOfOutputs;
    va_start(listOfOutputs, format);
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] == '%' && format[i-1] != '%' && format[i-1] != '\\'/* Probably won't work unless \\% not \% */) {
            switch (format[i + 1]) {

                case 'd':   printf("%d", va_arg(listOfOutputs, int)); break;

                case 'l':   if (format[i + 2] == 'f'){
                        printf("%lf", va_arg(listOfOutputs, double));
                        i++;
                    } else  {
                        printf("");
                        //printListT(va_arg(listOfOutputs, list*), 0);  // Fix Up printList
                    }
                    break;

                case 'f':   printf("%f", va_arg(listOfOutputs, double)); break;

                case 'c':   printf("%c", (char) va_arg(listOfOutputs, int)); break;

                case 's':   printf("%s", va_arg(listOfOutputs, char*)); break;

                default:    continue;

            }
            i++;
        }
        else{
            printf("%c", format[i]);
        }
    }
}

/**
 * prints a list. Don't use as it takes an unnecessary boolean and if you send 0 through will print the list without a newline at the end.
 * <p>
 *      If you want to not have a newline at the end of the list, pass 0 through.
 * </p>
 * @param ListPrint Takes a list.
 * @param newLine takes an unsigned 1 or 0 for if a newLine is wanted.
 */
void printList(list *ListPrint, unsigned newLine){
    printf("[");
    for (int i = 0; i < len(ListPrint); i++){
        if (i != 0) printf(", ");
        switch(ListPrint -> list[i].type) {
            case INT:       printf("%d", *(int*) ListPrint -> list[i].element); break;
            case DOUBLE:    printf("%f", *(double*) ListPrint -> list[i].element); break;
            case LDOUBLE:   printf("%Lf", *(long double*) ListPrint -> list[i].element); break;
            case FLOAT:     printf("%f", *(float*) ListPrint -> list[i].element); break;
            case STRING:
                #ifdef STRINGS_STR_H
                    printf("'%s'", getStr((string*) ListPrint -> list[i].element));
                #else
                    errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
                #endif
                break;
            case CHAR:      printf("'%c'", *(char*) ListPrint -> list[i].element); break;
            case CHARp:     printf("'%s'", (char*) ListPrint -> list[i].element); break;
            case BOOL:
                #ifdef _STDBOOL_H
                    printf("%d", *(bool*) ListPrint -> list[i].element);
                #else
                    errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "<stdbool.h>");
                #endif
                break;
            case LIST:      printList((list*) ListPrint -> list[i].element, 0); break;
            case null:      printf("NULL"); break;

            default:        errorList(1, 1, "\tvoid printList(list *ListPrint, bool newLine);\n");
        }
    }
    printf("]");
    if(newLine) printf("\n");
}

void printListt(list *ListPrint, unsigned newLine){
    printf("[");
    for (int i = 0; i < len(ListPrint); i++){
        if (i != 0) printf(", ");
        switch(ListPrint -> list[i].type) {
            case INT:       printf("(INT)"); break;
            case DOUBLE:    printf("(DOUBLE)"); break;
            case LDOUBLE:   printf("(LONGDOUBLE)"); break;
            case FLOAT:     printf("(FLOAT"); break;
            case STRING:
#ifdef STRINGS_STR_H
                printf("(STRING");
#else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
#endif
                break;
            case CHAR:      printf("(CHAR)"); break;
            case CHARp:     printf("(CHAR*)"); break;
            case BOOL:
#ifdef _STDBOOL_H
                printf("(BOOL)");
#else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "<stdbool.h>");
#endif
                break;
            case LIST:      printf("(LIST):"); printListt((list*) ListPrint -> list[i].element, 0); break;
            case null:      printf("(NULL)"); break;

            default:        errorList(1, 1, "\tvoid printList(list *ListPrint, bool newLine);\n");
        }
    }
    printf("]");
    if(newLine) printf("\n");
}

/**
 * Prints a list
 * @param ListPrint takes a list to print.
 */
void prints(list *ListPrint){
    printList(ListPrint, 1);
}

#endif //STRINGS_LIST_H
