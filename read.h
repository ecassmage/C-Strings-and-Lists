//
// Created by evanm on 2021-06-09.
//

#ifndef MAIN_C_READ_H
#define MAIN_C_READ_H

#include <stdio.h>
#include "string.h"

typedef struct FILEREAD{
    FILE *fd;
    int ptr;
    int eof;
} FR;


FR *FileRead(char file[]){
    FR *fileFR = (FR*) malloc(sizeof(FR));
    fileFR -> fd = (FILE*) malloc(sizeof(FILE));
    fileFR -> fd = fopen(file, "r");
    fileFR -> ptr = 0;
    fileFR -> eof = 0;
    return fileFR;
}

FILE *getFD(FR *fd){return fd -> fd;}
int getPTR(FR *fd) {return fd -> ptr;}
void upPTR(FR *fd) {fd -> ptr++;}
void setPTR(FR *fd, int num) {fd -> ptr = num;}
int atEndOfFile(FR *fd){return fd -> eof;}

str *readLine(FR *fd){
    str *line = String("");
    char buffer[1];
    unsigned number;
    fseek(getFD(fd), getPTR(fd), SEEK_SET);
    if (atEndOfFile(fd)) return NULL;
    while ((number = fread(buffer, 1, 1, getFD(fd))) > 0){
        upPTR(fd);
        if (buffer[0] == '\n') break;
        concatSingleChar(line, buffer[0]);
    }
    if (number == 0) fd -> eof = 1;
    return line;
}

void closeFR(FR *fd){
    fclose(fd -> fd);
    free(fd -> fd);
    free(fd);
}

#endif //MAIN_C_READ_H
