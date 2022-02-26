//
// Created by evanm on 2021-07-01.
//

#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// This is a bunch of stuff that list.h and str.h share so they need to be encapsulated between these #ifndef stuff so they don't collide with each other.
#ifndef STR_H
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
#endif //STR_H

typedef struct{
    type_t type;
    void *element;
} allTypes;

typedef struct{
    unsigned len;
    unsigned CurrentSize;
    allTypes *list;
} list;


// This is a bunch of stuff that list.h and str.h share so they need to be encapsulated between these #ifndef stuff so they don't collide with each other.
// I DON'T BELIEVE THIS WILL WORK ON ANY STRUCTURE NOT FORMATTED LIKE MINE ARE WHERE len IS THE FIRST VARIABLE STORED.
// This will activate if str.h is not an included header else will be disabled
#ifndef STR_H
unsigned len(void *lis){
    if ((list*) lis == NULL) return 0;
    return ((list*) lis) -> len;
}
#endif

unsigned maxLen(list *voi){return voi -> CurrentSize;}

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

void grow(list *this){
    this -> list = (allTypes*) realloc(this -> list, (maxLen(this) * 10) * sizeof(allTypes));
    if (this -> list == NULL) errorList(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tAllocating Space Failure\n");
    this -> CurrentSize *= 10;
    for (unsigned i = len(this); i < maxLen(this); i++) this -> list[i].element = (void*) malloc(sizeof(void));
}
void shrink(list *this){
    for (unsigned i = maxLen(this) - 1; i >= maxLen(this) / 10; i--) free(this -> list[i].element);
    this -> list = (allTypes*) realloc(this -> list, (maxLen(this) / 10 ) * sizeof(allTypes));
    if (this -> list == NULL) errorList(2, 1, "\tvoid increaseDecreaseSize(list *this);\n\tDeallocating Space Failure\n");
    this -> CurrentSize /= 10;
}
void checkSize(list *this){
    if (maxLen(this) > 10 && (maxLen(this) / 15) > len(this)) shrink(this);
    else if (len(this) == maxLen(this)) grow(this);
}


void fillElement(allTypes *temp, type_t type, void *appendList){
    temp -> type = type;
    switch(type){
        case INT:       temp -> element = (int*) realloc((int*) appendList, sizeof(int)); break;
        case FLOAT:     temp -> element = (float*) realloc((float*) appendList, sizeof(float)); break;
        case DOUBLE:    temp -> element = (double*) realloc((double*) appendList, sizeof(double)); break;
        case LDOUBLE:   temp -> element = (long double*) realloc((long double*) appendList, sizeof(long double)); break;
        case CHAR:      temp -> element = (char*) realloc((char*) appendList, sizeof(char)); break;
        case CHARp:     temp -> element = (char*) realloc((char*) appendList, (strlen((char*) appendList) + 1) * sizeof(char)); break;
        case LIST:      temp -> element = (list*) appendList;
        case BOOL:{
            #ifdef _STDBOOL_H
            temp -> element = (bool*) realloc((bool*) appendList, sizeof(bool)); break;
            #else
            errorList(3, 3, "\t\tvoid fillElement(allTypes *temp, type_t type, void *appendList)\n", "\"stdbool.h\"", "\nThis could be cause by either stdbool.h being included after list.h or \nBeing not Included.\n");
            #endif
        }
        case STRING: {
            #ifdef STR_H
            temp -> element = (string*) ; break;
            #else
            errorList(3, 3, "\t\tvoid fillElement(allTypes *temp, type_t type, void *appendList)\n", "\"str.h\"", "\nThis could be cause by either str.h being included after list.h or \nBeing not Included.\n");
            #endif
            break;
        }
        case DEBUG:{
            errorList(1, 2, "\tvoid fillElement(element *temp, type_t type, va_list lis);\n\terrorList(2, 1, \"\\tvoid fillElement(element *temp, type_t type, va_list lis)\\n\\tcase DEBUG:\");",
                      "\nI love this ANSI Color. Probably won't appear on most terminals/consoles but the fact it will sometimes show up is great\n");
            break;
        }
        default: errorList(1, 1, "void add(list *addToList, type_t type, void *ptr);\n\t\tswitch(type)\n\t\tdefault:");
    }
}

/// Add to List
void add(list *addToList, type_t type, void *appendList){
    checkSize(addToList);
    fillElement(&(addToList -> list[len(addToList)]), type, appendList);
    addToList -> len++;
}

/// This Can Easily Mess up if you do not input the correct number of things, use add instead of this.
void extend(list *addToList, int numberOfNewAdds, ...){
    va_list lis;
    va_start(lis, numberOfNewAdds);
    for (int i = 0; i < numberOfNewAdds; i++){
        add(addToList, va_arg(lis, type_t), va_arg(lis, void*));
    }
}

void insert(list *addToList, int index, type_t type, void *appendList){
    if (index < 0) index += (int) addToList -> len;
    if (index >= addToList -> len || addToList -> len < 0) errorList(0, index, len(addToList), "void insert(list *addToList, int index, type_t type, ...);");  // Catches Double Wrap Arounds', I don't like doubles, they seem dumm.;P

    checkSize(addToList);

    for (unsigned i = len(addToList); index < i; i--) addToList -> list[i] = addToList -> list[i-1];
    fillElement(&addToList -> list[index], type, appendList);
    addToList -> len++;
}
/// Add to List


/// Delete from List
allTypes *popIndexCopy(list *lis, int index){
    if (index < 0) index += (int) lis -> len;
    if (index >= lis -> len || lis -> len < 0) return NULL;  // Catches Double Wrap Arounds', I don't like doubles, they seem dumm. :P

    allTypes *temp = (allTypes*) malloc(sizeof(allTypes));
    temp -> element = (void*) malloc(sizeof(void));
    fillElement(temp, lis -> list[index].type, lis -> list[index].element);

    for (index++; index < lis -> len; index++) lis -> list[index-1] = lis -> list[index];
    lis -> len--;
    checkSize(lis);

    return temp;
}
void popIndex(list *lis, int index) { free(popIndexCopy(lis, index)); }
allTypes *popCopy(list *lis)        { return popIndexCopy(lis, -1); }
void pop(list *lis)                 { free(popIndexCopy(lis, -1)); }
/// Delete from List


/// Print
void printList(list *ListPrint, unsigned newLine);
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

/// This can catch easy to see recursion like if List1 adds to it List1, it will print [...] for List1 element instead of List1 to represent an infinite sized section.
void printList(list *ListPrint, unsigned newLine){
    printf("[");
    for (int i = 0; i < len(ListPrint); i++){
        if (i != 0) printf(", ");
        switch(ListPrint -> list[i].type) {
            case INT:       printf("%d", *(int*) ListPrint -> list[i].element); break;
            case DOUBLE:    printf("%f", *(double*) ListPrint -> list[i].element); break;
            case LDOUBLE:   printf("%Lf", *(long double*) ListPrint -> list[i].element); break;
            case FLOAT:     printf("%f", *(float*) ListPrint -> list[i].element); break;
            case CHAR:      printf("'%c'", *(char*) ListPrint -> list[i].element); break;
            case CHARp:     printf("'%s'", (char*) ListPrint -> list[i].element); break;
            case null:      printf("NULL"); break;
            case LIST:      ((list *) ListPrint->list[i].element == ListPrint) ? printf("[...]"):printList((list *) ListPrint->list[i].element, 0); break;
            case BOOL: {
                #ifdef _STDBOOL_H
                printf("%d", *(bool*) ListPrint -> list[i].element);
                #else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "<stdbool.h>");
                #endif
                break;
            }
            case STRING: {
                #ifdef STRINGS_STR_H
                printf("'%s'", getStr((string*) ListPrint -> list[i].element));
                #else
                errorList(3, 2, "\t\tvoid printList(list *ListPrint, bool newLine);\n", "\"str.h\"");
                #endif
                break;
            }
            default:        errorList(1, 1, "\tvoid printList(list *ListPrint, bool newLine);\n");
        }
    }
    printf("]");
    if(newLine) printf("\n");
}

#endif //LIST_H
