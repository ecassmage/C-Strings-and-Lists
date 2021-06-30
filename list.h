//
// Created by evanm on 2021-06-29.
//

/**
 * @author Evan Morrison
 * @version 1.2.50
 * @since 1.1
 */

/**
 * If University asks you to use C and you want to use Python Just bring Python to C.
 */
#ifndef STRINGS_LIST_H
#define STRINGS_LIST_H

#include "str.h"
#include <stdbool.h>
#include <stdarg.h>

/// Structures
typedef struct{
    type_t type;
    void *element;
} element;

typedef struct{
    unsigned len;
    unsigned CurrentSize;
    element *list;
} list;
/// Structures



////// Functions Below


/// List Constructor
list *List();
/// List Constructor


/// InnerWorkings
void increaseDecreaseSize(list *this);
unsigned maxLen(list *voi){return voi -> CurrentSize;}
void fillElement(element *temp, type_t type, va_list lis);
/// InnerWorkings


/// Adding Functions
void add(list *addToList, type_t type, ...);
/// Adding Functions


/// Delete Functions
element *deletec(list *lis, unsigned index);
void delete(list *lis, unsigned index);
element *delc(list *lis);
void del(list *lis);
/// Delete Functions

/// Printers
void printList(list *ListPrint, bool newLine);
void prints(list *ListPrint);
/// Printers

////// Functions Above



list *List(){
    list *newList = (list*) malloc(sizeof(list));
    newList -> list = (element*) malloc(10 * sizeof(element));
    newList -> len = 0;
    newList -> CurrentSize = 10;
    return newList;
}

void increaseDecreaseSize(list *this){
    if (maxLen(this) > 10 && (maxLen(this) / 15) > len(this)){
        // Go Down Size
        for (int i = maxLen(this) - 1; i >= maxLen(this) / 10; i--) free(this -> list[i].element);
        this -> list = (element*) realloc(this -> list, (maxLen(this) / 10) * sizeof(element));
        if (this -> list == NULL) ERROR(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tDeallocating Space Failure\n");
        this -> CurrentSize /= 10;
    }
    else if (len(this) == maxLen(this)){
        // Go Up Size
        this -> list = (element*) realloc(this -> list, (maxLen(this) * 10) * sizeof(element));
        if (this -> list == NULL) ERROR(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tAllocating Space Failure\n");
        this -> CurrentSize *= 10;
    }
}

void fillElement(element *temp, type_t type, va_list lis){
    temp -> type = type;
    temp -> element = (void*) malloc(sizeof(void));
    switch(type){
        case INT:{
            int *num = (int*) malloc(sizeof(int));
            *num = va_arg(lis, int);
            temp -> element = num;
            break;
        }

        case DOUBLE:{
            double *doub = (double*) malloc(sizeof(double));
            *doub = va_arg(lis, double);
            temp -> element = doub;
            break;
        }

        case LDOUBLE:{
            long double *ldouble = (long double*) malloc(sizeof(long double));
            *ldouble = va_arg(lis, double);
            temp -> element = ldouble;
            break;
        }

        case FLOAT:{
            float *flo = (float*) malloc(sizeof(float));
            *flo = (float) va_arg(lis, double);
            temp -> element = flo;
            break;
        }

        case STRING:{
            temp -> element = va_arg(lis, string*);
            break;
        }

        case STR:{

            break;
        }

        case CHAR:{
            char *cha = (char*) malloc(sizeof(char));
            *cha = (char) va_arg(lis, int);
            temp -> element = cha;
            break;
        }

        case CHARp:{
            char *tempoChar = va_arg(lis, char*);
            char *chap = (char*) malloc((strLen((char*) tempoChar) + 1) * sizeof(char));
            int i = 0; do {chap[i] = tempoChar[i];i++;} while (tempoChar[i] != '\0');
            temp -> element = chap;
            break;
        }

        case BOOL:{

            bool *boo = (bool*) malloc(sizeof(bool));
            *boo = (bool) va_arg(lis, int);
            temp -> element = boo;
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

        default:{
            ERROR(2, 1, "void add(list *addToList, type_t type, void *ptr);\n");
        }
    }
}

void add(list *addToList, type_t type, ...){
    va_list lis;
    va_start(lis, type);
    increaseDecreaseSize(addToList);
    element *temp = &(addToList -> list[len(addToList)]);  // Easier Access
    fillElement(temp, type, lis);
    addToList -> len++;
}

/**
 * Short form for delete, will delete last element
 * @param lis takes a list
 */

element *deletec(list *lis, unsigned index){
    if (index < 0) index += lis -> len;
    if (index >= lis -> len || lis -> len < 0) return NULL;  // Catches Double Wrap Arounds', I don't like doubles, they seem dumm.;P
    element *temp = (element*) malloc(sizeof(element));
    temp = &lis -> list[index];
    for (index++; index < lis -> len; index++) lis -> list[index-1] = lis -> list[index];
    lis -> len--;
    increaseDecreaseSize(lis);
    return temp;
}
void delete(list *lis, unsigned index){
    free(deletec(lis, index) -> element);
}

element *delc(list *lis){
    element *temp = deletec(lis, len(lis) - 1); // Ta Gaa
    return temp;
}

void del(list *lis){
    free(deletec(lis, len(lis)));
}

void printList(list *ListPrint, bool newLine){
    printf("[");
    for (int i = 0; i < len(ListPrint); i++){
        if (i != 0) printf(", ");
        switch(ListPrint -> list[i].type){
            case INT:       printf("%d", *(int*) ListPrint -> list[i].element); break;
            case DOUBLE:    printf("%f", *(double*) ListPrint -> list[i].element); break;
            case LDOUBLE:   printf("%Lf", *(long double*) ListPrint -> list[i].element); break;
            case FLOAT:     printf("%f", *(float*) ListPrint -> list[i].element); break;
            case STRING:    printf("'%s'", getStr((string*) ListPrint -> list[i].element)); break;
            case STR:       break;
            case CHAR:      printf("'%c'", *(char*) ListPrint -> list[i].element); break;
            case CHARp:     printf("'%s'", (char*) ListPrint -> list[i].element); break;
            case BOOL:      printf("%d", *(bool*) ListPrint -> list[i].element); break;
            case LIST:      printList((list*) ListPrint -> list[i].element, false); break;
            case null:      printf("NULL"); break;

            default:        ERROR(2, 1, "void add(list *addToList, type_t type, void *ptr);\n");
        }
    }
    printf("]");
    if(newLine) printf("\n");
}

void prints(list *ListPrint){
    printList(ListPrint, true);
}


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


#endif //STRINGS_LIST_H
