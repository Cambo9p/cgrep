#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "../include/hashmap.h"
#include "../include/args.h"
#include "../include/formatted_ans.h"

void boyer_moore_search(char *pattern, char *buffer, int buffSize, grep_args_t *args);
static map_t shift_table_create(char *pattern, int len);

void cgrep_linear_search(grep_args_t *args);

void cgrep_search_file(char *filename, char *pattern) {
    grep_args_t *args = (grep_args_t*) malloc(sizeof(grep_args_t));
    if (args == NULL) {
        perror("could not allocate memory for args");
        exit(1);
    }
    args = argsInit(pattern);
    strcpy(args->filename, filename);

    cgrep_linear_search(args);
    free(args);
}

// naive linear search 
// TODO maybe return args for directory to use
void cgrep_linear_search(grep_args_t *args) {
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

    boyer_moore_search(pattern, buffer, lSize, args);

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

// called when the pattern is found, gets the last \n 
// and next one then formats the 
static void handle_line(int start, int end, char *buffer, grep_args_t *args) {
    int p1 = start;
    int p2 = end;
    int len = strlen(buffer);
    while (p1 > 0 && buffer[p1 - 1] != '\n') {
        p1--;
    }

    while (p2 < len && buffer[p2] != '\n') {
        p2++;
    }

    int line_len = p2 - p1;
    char *line = (char*)malloc((line_len + 1) * sizeof(char));
    if (line == NULL) {
        perror("failed to allocate mem");
        exit(1);
    }
    strncpy(line, buffer + p1, line_len);
    line[line_len] = '\0';

    formatLine(line, start - p1, end - p1);
    args->results[args->curr] = line;
    args->curr++;
    //printf("%s", line);
    //printf("%s", args->results[args->curr]);
}

void boyer_moore_search(char *pattern, char *buffer, int buffSize,grep_args_t *args) {
    int pLen = strlen(pattern);
    map_t *table = shift_table_create(pattern, pLen);

    int index = pLen - 1;

    while (index <= buffSize - pLen) {
        int offset = 0;
        
        while (offset < pLen && pattern[pLen - offset - 1] == buffer[index - offset]) {
            offset++;
        }

        if (offset == pLen) {
            handle_line(index - offset + 1, index + 1, buffer, args);
            index += pLen;
        } else {
            int tableVal = map_get(table, buffer[index]); 
            int shift = (tableVal == -1) ? pLen : tableVal;
            if (shift + index >= buffSize) {
                return;
            }
            index += shift;
        }
    }
}
