#include <search.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/searchdir.h"
#include "../include/searchfile.h"

typedef enum {
    RECURSIVE_OPT,
    LINE_NUM_OPT,
    COUNT_OPT,
} Options_t;

// Parses the input and searches for the pattesh in the file
void cgrep_find_in_file(int inputCount, char **input) {
    char *filename = input[1];
    char *pattern = input[0];
    printf("searching for '%s' in %s\n", pattern, filename);
    
    cgrep_search_file(filename, pattern);
}

// Parses the input and searches for the pattesh in the directory
void cgrep_find_in_dir(int inputCount, char **input) {
    char *directory = input[1];
    char *pattern = input[0];

    cgrep_search_dir(directory, pattern);
}

void cgrep_read_from_stdin() {
    char buffer[100];

    while (fgets(buffer, 100, stdin) != NULL) {
        printf("%s\n", buffer);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    //Options_t options[3];
    bool recursive = false;
    
    int i = 0;
    while ((opt = getopt(argc, argv, "rcn")) != -1) {
        switch (opt) {
            case 'r':
                // TODO
                //printf("option %s\n",optarg); // this is when 'r:' is used
                recursive = true;
                break;
            case 'c':
                //options[i] = COUNT_OPT;
                break;
            case 'n':
                //options[i] = LINE_NUM_OPT;
                break;
            default:
                break;
        }
        i++;
    }
    // TODO: check if we need to get from stdin

    int numArgs = argc - optind;
    char **args = &argv[optind++];

    // TODO: if we use -r we shouldnt have to pass in the filename
    // so we will need to make argrs[0]
    if (numArgs != 2) {
        fprintf(stderr, "Useage: %s [-rcn] [word...] [file...]\n", argv[0]);
        exit(-1);
    }


    if (recursive) {
        cgrep_find_in_dir(numArgs, args);

    } else {
        cgrep_find_in_file(numArgs, args);
    }

    return 0;
}
