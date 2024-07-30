#include <search.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/searchfile.h"

typedef enum{
    RECURSIVE_OPT,
    LINE_NUM_OPT,
    COUNT_OPT,
} Options_t;

// takes array with filename and 
void cgrep_find_in_file(int inputCount, char **input) {
    char *filename = input[1];
    char *pattern = input[0];
    printf("searching for '%s' in %s\n", pattern, filename);
    
    cgrep_search(filename, pattern);
}

void cgrep_read_from_stdin() {
    char buffer[100];

    while (fgets(buffer, 100, stdin) != NULL) {
        printf("%s\n", buffer);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    Options_t *options;
    
    int i = 0;
    while ((opt = getopt(argc, argv, "rcn")) != -1) {
        switch (opt) {
            case 'r':
                // TODO
                //printf("option %s\n",optarg); // this is when 'r:' is used
                options[i] = RECURSIVE_OPT;
                break;
            case 'c':
                options[i] = COUNT_OPT;
                break;
            case 'n':
                options[i] = LINE_NUM_OPT;
                break;
            default:
                break;
        }
        i++;
    }
    // TODO: check if we need to get from stdin

    int numArgs = argc - optind;
    char **args = &argv[optind++];

    if (numArgs != 2) {
        fprintf(stderr, "Useage: %s [-rcn] [file...]\n", argv[0]);
        exit(-1);
    }

    // TODO multi opt parsing

    cgrep_find_in_file(numArgs, args);

    return 0;
}
