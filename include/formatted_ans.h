#ifndef FORMATTED_ANS_H
#define FORMATTED_ANS_H

typedef struct {
    char **result;
    char **filenames;
    int len;
    int isRecursive;
} result_t;

result_t *rInit();
void addResult(result_t *res, char* line, char* filename);
void printResult(result_t *res);
void freeResult(result_t *res);
// formats line so that from start to end the chars
// are in red 
void formatLine(char* line, int start, int end);

#endif
