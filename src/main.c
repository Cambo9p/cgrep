#include <search.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/search.h"

typedef enum{
    NO_OPT,
} Options_t;

// takes array with filename and 
void cgrep_find_in_file(int inputCount, char **input) {
    char *filename = input[0];
    char *pattern = input[1];
    printf("searching for '%s' in %s\n", pattern, filename);
    // TODO make sure the file exists
    
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
    
    while ((opt = getopt(argc, argv, "r:")) != -1) {
        switch (opt) {
            case 'r':
                // TODO
                printf("option %s\n",optarg);
                break;
            default:
                break;
        }
    }
    // TODO: check if we need to get from stdin

    int numArgs = argc - optind;
    char **args = &argv[optind++];

    if (numArgs > 2) {
        printf("error");
        exit(-1);
    }

    cgrep_find_in_file(numArgs, args);

    return 0;
}
