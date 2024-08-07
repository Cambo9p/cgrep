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
static void init_workers(grep_args_t *workers[], char *pattern);
static void join_and_free_workers(pthread_t threads[], grep_args_t *workers[], int numWorkers);

// searches the current directory for all files, and sub directories
void cgrep_search_dir(char *dir, char *pattern) {
    pthread_t threads[NUM_THREADS];
    DIR *d;
    struct dirent *dirstr;
    char *path = "./";
    grep_args_t *workers[NUM_THREADS];
    int numfiles = 0;

    memset(workers, 0, sizeof(workers));
    init_workers(workers, pattern);

    d = opendir(path);
    if (!d) {
        perror("could not open current directory\n");
    }

    int i = 0;
    while ((dirstr = readdir(d)) != NULL && i < NUM_THREADS) {
        if (dirstr->d_type == DT_REG) {
            printf("found %s\n", dirstr->d_name);
            strcat(workers[i]->filename, path);
            if (pthread_create(&threads[i], NULL, recursive_dfs, workers[i])) {
                perror("error creating thread");
                exit(-1);
            }
            numfiles++;
            i++;
        } else if (dirstr->d_type == DT_DIR 
                    && strcmp(".", dirstr->d_name) != 0 
                    && strcmp("..", dirstr->d_name) != 0) {
            printf("found the dir %s\n", dirstr->d_name);
        }
    }
    closedir(d);

    join_and_free_workers(threads, workers, numfiles);
}

static void *recursive_dfs(void *arg) {
	grep_args_t* threadWorker = (grep_args_t *) arg;
    printf("got into the thread for dir %s\n", threadWorker->filename);

	pthread_exit(NULL);
}

// inits array of workers
static void init_workers(grep_args_t *workers[], char *pattern) {
    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i] = (grep_args_t*)malloc(sizeof(grep_args_t));
        if (workers[i] == NULL) perror("error allocating space");

        workers[i]->results = (char*)malloc(1024); 
        if (workers[i]->results == NULL) perror("error allocating space");

        workers[i]->filename = (char*)malloc(1024); 
        if (workers[i]->filename == NULL) perror("error allocating space");

        strcpy(workers[i]->filename, "");
        strcpy(workers[i]->pattern, pattern);
    }
}

// waits for all threads to finish and frees all memory
static void join_and_free_workers(pthread_t threads[], grep_args_t *workers[], int numWorkers) {
    for (int j = 0; j < numWorkers; j++) {
        if (pthread_join(threads[j], NULL) != 0) {
            perror("error joining thread");
            exit(1);
        }
        free(workers[j]->filename);
        free(workers[j]->results);
        free(workers[j]);
    }

}
