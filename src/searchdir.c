#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include "../include/args.h"
#include "../include/queue.h"
#include "../include/searchfile.h"


#define INP 1
#define OUTP 0
#define NUM_THREADS 50

typedef struct worker_t worker_T;
result_t *res;

static void *handle_file(void *arg);
static void init_workers(grep_args_t *workers[], char *pattern);
static void join_and_free_workers(pthread_t threads[], grep_args_t *workers[], int numWorkers);

// searches the current directory for all files, and sub directories
// currently, each file encountered is handled in its own thread and each 
// directory is handled in as a bfs search
void cgrep_search_dir(char *dir, char *pattern) {
    pthread_t threads[NUM_THREADS];
    DIR *d;
    struct dirent *dirstr;
    char *path = "./";
    grep_args_t *workers[NUM_THREADS];
    int numfiles = 0;
    queue_t *queue = qinit();
    res = rInit();

    memset(workers, 0, sizeof(workers));
    init_workers(workers, pattern);

    d = opendir(path);
    if (!d) {
        perror("could not open current directory\n");
    }


    int i = 0;
    while ((dirstr = readdir(d)) != NULL && i < NUM_THREADS) {
        if (dirstr->d_type == DT_REG) {
            //printf("found %s\n", dirstr->d_name);
            strcat(workers[i]->filename, path);
            strcat(workers[i]->filename, dirstr->d_name);

            if (pthread_create(&threads[i], NULL, handle_file, workers[i])) {
                perror("error creating thread");
                exit(-1);
            }
            numfiles++;
            i++;
        } else if (dirstr->d_type == DT_DIR 
                    && strcmp(".", dirstr->d_name) != 0 
                    && strcmp("..", dirstr->d_name) != 0) {
            //printf("found the dir %s\n", dirstr->d_name);
            qPush(queue, dirstr->d_name);
        }
    }
    // handle all the queues recursively
    qprint(queue);
    qfree(queue);

    closedir(d);

    join_and_free_workers(threads, workers, numfiles);
}

static void *handle_file(void *arg) {
	grep_args_t* threadWorker = (grep_args_t *) arg;
    printf("got into the thread for dir %s\n", threadWorker->filename);

    cgrep_linear_search(threadWorker);
    // TODO we can get the results from the threadworker

    for (int i = 0; i < threadWorker->curr; i++) {
        printf("in here");
        printf("%s",threadWorker->results[i]);
    }
	pthread_exit(NULL);
}

// inits array of workers
static void init_workers(grep_args_t *workers[], char *pattern) {
    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i] = argsInit(pattern);
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
