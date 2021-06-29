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
    list *list = List();
    listHelp();
    add(list, STRING, mkString("Hello World"));
    add(list, CHARp, "Hello");
    add(list, INT, 100);
    add(list, CHAR, 's');
    add(list, INT, 101);
    for (int i = 0; i < 100; i++){
        add(list, INT, 100 + i);
    }
    printList(list);
    int *num = delc(list) -> element;
    printf("%d\n", *num);
    printList(list);
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