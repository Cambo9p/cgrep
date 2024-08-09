#include "../include/args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

grep_args_t* argsInit(char* pattern) {
    grep_args_t * args = (grep_args_t*)malloc(sizeof(grep_args_t));
    if (args == NULL) perror("error allocating space");

    args->results = (char**)malloc(1024); 
    if (args->results == NULL) perror("error allocating space");

    args->filename = (char*)malloc(1024); 
    if (args->filename == NULL) perror("error allocating space");

    args->results = (char**)malloc(2048); 
    if (args->results == NULL) perror("error allocating space");
    args->curr = 0;

    strcpy(args->filename, "");
    strcpy(args->pattern, pattern);

    return args;
}
