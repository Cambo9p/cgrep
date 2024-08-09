#ifndef ARGS_H
#define ARGS_H

typedef struct grep_args {
    //char filename[100];
    char *filename;
    char pattern[50];
    // results
    char **results;
    int curr;
} grep_args_t;

grep_args_t* argsInit(char* pattern);

#endif
