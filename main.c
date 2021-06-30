/**
 * @author Evan Morrison
 * @version 1.3.00
 * @since 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"  // Activates ERROR messages for str.h and list.h Should be included before either for this to work since
#include "str.h"
#include "list.h"
#include <string.h>
#include "printe.h" // This is separate for ease of coding will be merged probably later


void printE();
void strings();
void lists();

int main() {/*
    double a=2.1323458340538509345089354093405983;
    double d=23424323423424.1323458340538509345089354093405983;
    float b=2.1323458340538509345089354093405983;
    float e=45345345345342.1323458340538509345089354093405983;
    long double c=2.1323458340538509345089354093405983;
    long double f=45345345345345345354.1323458340538509345089354093405983;
    double g =  d - (double) ((long) d);
    double h =  a - (double) ((long) a);
    printf("%lf, %f, %Lf, %lf, %f, %Lf, %lf, %lf\n", a, b, c, d, e, f, g, h);
    printE();*/
    //strings();
    lists();
    return 0;
}

void printE(){
    printf("%s\n", convertIntToChar(155));
    printf("%s\n", convertIntToChar(-155));
    printf("%s\n", convertDoubleToChar(155.1412124));
}
/**
 * I Use this to Test lists.
 */
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
    //add(list1, DEBUG, "DebugToTestERRORMessageFormat");
    //add(list1, DEBUG, NULL);
    add(list1, INT, 2344234);
    for (int i = 0; i < 10; i++){
        add(list2, INT, 100 + i);
    }
    prints(list1);
    printf("This be Deleted -> %d\n", *(int*) delc(list1) -> element);
    prints(list1);
    add(list1, LIST, list2);
    prints(list2);
    prints(list1);
    insert(list2, 3, CHARp, "Hello");
    prints(list1);
    print("This is My Test I have Proposed: %d, %c, %lf, %l\n", 100, 'c', 10.154545, list1);
    print("This is My Test I have Proposed: %d, %c, %lf, %l", 100, 'c', 10.154545, list1);
}

/**
 * I Use this to Test Strings and string arrays or str.
 */
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
    replace(str3, "HEll", "Evan Morrison");
    printf("\n");
    printFull(str1);
    printFull(str2);
    printFull(str3);
    printFull(string -> cont);
    printFull(string1 -> cont);
    printFull(string2 -> cont);
    replace(str3, "Evan Morrison", "Bitch");
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