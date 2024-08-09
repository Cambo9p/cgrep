#include "../include/formatted_ans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define RESET "\x1B[0m"
#define RESULT_SIZE 1024

result_t *rInit() {
    result_t *r = (result_t*)malloc(sizeof(result_t));
    if (r == NULL) {
        perror("error allocating memory");
        exit(1);
    }
    r->len = 0;
    r->result = (char**)malloc(sizeof(char*) * RESULT_SIZE);
    if (r->result == NULL) {
        perror("error allocating memory");
        free(r);
        exit(1);
    }
    r->filenames = (char**)malloc(sizeof(char*) * RESULT_SIZE);
    if (r->filenames == NULL) {
        perror("error allocating memory");
        free(r);
        exit(1);
    }


    return r;
}

void addResult(result_t *res, char* line, char* filename) {
    char *str = (char*)malloc(strlen(line) + 1);
    if (str == NULL) {
        perror("error allocating memory");
        exit(1);
    }

    res->result[res->len] = str;
    res->len++;
}
    
void printResult(result_t *res) {
    for (int i = 0; i < res->len; i++) {
        if (res->isRecursive) {
            printf("%s%s%s:%s ", KRED, res->filenames[i], KGRN, RESET);
        }
        printf("%s\n", res->result[i]);
    }

}

void freeResult(result_t *res) {
    for (int i = 0; i < res->len; i++) {
        free(res->result[i]);
        free(res->filenames[i]);
    }

    free(res);
}

void formatLine(char* line, int start, int end) {
    int lineLen = strlen(line);
    if (start < 0 || end >= lineLen || start >= end) {
        perror("Invalid start or end indices.\n");
        exit(1);
    }

    char *lineToStart = (char*)malloc((start + 1) * sizeof(char)); 
    char *lineToEnd = (char*)malloc((lineLen - end + 1) * sizeof(char)); 
    char *res = (char*)malloc((end - start + 1) * sizeof(char)); 

    if (!lineToStart || !lineToEnd || !res) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    strncpy(lineToStart, line, start);
    lineToStart[start] = '\0'; 

    strncpy(lineToEnd, line + end, lineLen - end);
    lineToEnd[lineLen - end] = '\0'; 

    strncpy(res, line + start, end - start);
    res[end - start] = '\0'; 

    printf("%s%s%s%s%s\n", lineToStart, KRED, res, RESET, lineToEnd);

    free(lineToStart);
    free(lineToEnd);
    free(res);
}
