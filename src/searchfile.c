#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "../include/hashmap.h"
#include "../include/args.h"

static void cgrep_linear_search(grep_args_t *args);
static void boyer_moore_search(char *pattern, char *buffer, int buffSize);
static map_t shift_table_create(char *pattern, int len);
  
void cgrep_search_file(char *filename, char *pattern) {
    // TODO add option parsing
    grep_args_t *args = (grep_args_t*) malloc(sizeof(grep_args_t));
    if (args == NULL) {
        perror("could not allocate memory for args");
        exit(1);
    }
    args->filename = (char*)malloc(strlen(filename) + 1);
    //args->pattern = pattern;
    strcpy(args->pattern, pattern);
    //args->filename = filename;
    strcpy(args->filename, filename);
    cgrep_linear_search(args);
    free(args);
}


// naive linear search
static void cgrep_linear_search(grep_args_t *args) {
    char *filename = args->filename;
    char *pattern = args->pattern;
    FILE *fp;
    long lSize;
    size_t result;
    char *buffer;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "file '%s' not found\n", filename);
        fclose(fp);
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);


    // TODO: multiple buffers 2048 size 
    buffer = (char*)malloc(sizeof(char*) * lSize);
    if (buffer == NULL) {
        perror("failed to allocate buffer\n");
        fclose(fp);
        exit(-1);
    }

    result = fread(buffer, 1, lSize, fp);
    if (result != lSize) {
        perror("failed to allocate buffer\n");
        fclose(fp);
        exit(-1);
    }

    boyer_moore_search(pattern, buffer, lSize);

    fclose(fp);
    free(buffer);
}

static map_t shift_table_create(char *pattern, int len) {
    map_t *map = map_new();

    for (int i = 0; i < len; i++) {
        map_put(map, pattern[i], 1 > (len - i - 1) ? 1 : (len - i - 1));
    }

    return map;
}

void boyer_moore_search(char *pattern, char *buffer, int buffSize) {
    int pLen = strlen(pattern);
    map_t *table = shift_table_create(pattern, pLen);

    int index = pLen - 1;

    while (index <= buffSize - pLen) {
        int offset = 0;
        
        while (offset < pLen && pattern[pLen - offset - 1] == buffer[index - offset]) {
            offset++;
        }

        if (offset == pLen) {
            printf("found!!!!!\n");
            printf("index %d to %d\n", index - offset + 1, index + 1);
            index += pLen;
        } else {
            int tableVal = map_get(table, buffer[index]); 
            int shift = (tableVal == -1) ? pLen : tableVal;
            if (shift + index >= buffSize) {
                printf("done\n");
                return;
            }
            index += shift;
        }
    }
}
