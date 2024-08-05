#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include "../include/args.h"


#define INP 1
#define OUTP 0
#define NUM_THREADS 50

typedef struct worker_t worker_T;
static void *recursive_dfs(void *arg);

// searches the current directory for all files, and sub directories
void cgrep_search_dir(char *dir, char *pattern) {
    pthread_t threads[NUM_THREADS];
    DIR *d;
    struct dirent *dirstr;
    char *path = "./";
    grep_args_t *workers[NUM_THREADS];
    int numfiles = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i] = (grep_args_t*)malloc(sizeof(grep_args_t));
        if (workers[i] == NULL) perror("error allocating space");

        workers[i]->results = (char*)malloc(sizeof(char*)); 
        strcpy(workers[i]->filename, "");
        strcpy(workers[i]->pattern, pattern);
    }

    d = opendir(path);
    if (!d) {
        perror("could not open current directory\n");
    }

    int i = 0;
    while ((dirstr = readdir(d)) != NULL) {
        if (dirstr->d_type == DT_REG) {
            printf("found %s\n", dirstr->d_name);
            strcat(workers[i]->filename, path);
            pthread_create(&threads[i], NULL, recursive_dfs, workers[i]);
            numfiles++;
        } else if (dirstr->d_type == DT_DIR 
                    && strcmp(".", dirstr->d_name) != 0 
                    && strcmp("..", dirstr->d_name) != 0) {
            printf("found the dir %s\n", dirstr->d_name);
        }
        i++;
    }

    printf("ntesrtrnse\n");
    // double free in here
    for (int j = 0; j < numfiles; j++) {
        free(workers[j]->filename);
        free(workers[j]->results);
        printf("in\n");
        free(workers[j]);
        pthread_join(threads[j], NULL);
    }
}

static void *recursive_dfs(void *arg) {
	grep_args_t* threadWorker = (grep_args_t *) arg;
    printf("got into the thread for dir %s\n", threadWorker->filename);

	pthread_exit(NULL);
}
