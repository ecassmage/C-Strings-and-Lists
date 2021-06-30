#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "list.h"
#include "error.h"

void strings();
void lists();

int main() {
    //strings();
    lists();
    return 0;
}

void lists(){
    list *list1 = List();
    list *list2 = List();
    listHelp();
    add(list1, STRING, mkString("Hello World"));
    add(list1, CHARp, "Hello");
    add(list1, INT, 100);
    add(list1, CHAR, 's');
    add(list1, INT, 101);
    add(list1, FLOAT, 101.1);  // Floats are BAAAAAAD.
    add(list1, BOOL, true);  // Floats are BAAAAAAD.
    add(list1, BOOL, false);  // Floats are BAAAAAAD.
    add(list1, DOUBLE, 101.111123122);
    add(list1, DOUBLE, 101.1);
    add(list1, LDOUBLE, 145646401.3453453);
    for (int i = 0; i < 10; i++){
        add(list2, INT, 100 + i);
    }
    prints(list1);
    printf("This be Deleted -> %d\n", *(int*) delc(list1) -> element);
    prints(list1);
    add(list1, LIST, list2);
    prints(list2);
    prints(list1);
}

void strings(){
    printf("Hello, World!\n");
    string *string4 = mkString("Hi Boi");
    string *str1 = newString(null, N);
    string *str2 = newString(CHAR, "HEllO");
    string *str3 = String();
    str *string = Str(null, N);
    str *string1 = Str(CHAR, "HelloBoi");
    str *string2 = Str(STRING, string4);
    printFull(str1);
    printFull(str2);
    printFull(str3);
    printFull(string -> cont);
    printFull(string1 -> cont);
    printFull(string2 -> cont);
    //printf("%d, %d %d\n", len(str1), len(string), len(string -> cont));
    //printf("%d, %d, %d\n", len(str2), len(string1), len(string1 -> cont));
    //printf("%d, %d, %d\n", len(str3), len(string2), len(string2 -> cont));
    concat(str1, 1, "Hello World");
    concatStr(str3, 1, str2);
    concat(str1, 1, " ");
    concatStr(str3, 1, str2);
    printf("\n");
    printFull(str1);
    printFull(str2);
    printFull(str3);
    printFull(string -> cont);
    printFull(string1 -> cont);
    printFull(string2 -> cont);
    newReplace(str3, "HEll", "Evan Morrison");
    printf("\n");
    printFull(str1);
    printFull(str2);
    printFull(str3);
    printFull(string -> cont);
    printFull(string1 -> cont);
    printFull(string2 -> cont);
    newReplace(str3, "Evan Morrison", "Bitch");
    append(string, CHAR, "Hello World");
    printf("\n");
    printFull(str1);
    printFull(str2);
    printFull(str3);
    printFull(&string -> cont[0]);
    printFull(&string1 -> cont[0]);
    printFull(&string2 -> cont[0]);
    //printf("\n%d, %d\n", len(str1), len(string));
    //printf("%d, %d, %d\n", len(str2), len(string1), len(string1 -> cont));
    //printf("%d, %d, %d\n", len(str3), len(string2), len(string2 -> cont));
    //get(string1, 1124);
}