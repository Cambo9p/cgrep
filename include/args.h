#ifndef ARGS_H
#define ARGS_H

typedef struct grep_args {
    char filename[100];
    char pattern[50];
    // results
    char* results;
} grep_args_t;


#endif
