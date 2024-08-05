#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#define INP 1
#define OUTP 0
#define NUM_THREADS 50

typedef struct worker_t worker_T;

// TODO: alter with the line contents 
struct worker_t {
    void (*execute)(worker_T *);
    int linenums[1000];
};

void cgrep_search_dir(char *dir, char *pattern) {
    printf("searching for '%s' in %s\n", pattern, dir);
    // have a worker accumulate all of the occurances and put 
    // them together at the end 
    pthread_t threads[NUM_THREADS];
    worker_T workers[NUM_THREADS];
    DIR *d;
    struct dirent *dirstr;
    char *path = "./";

    d = opendir(path);
    if (!d) {
        perror("could not open current directory\n");
    }

    int i = 0;
    while ((dirstr = readdir(d)) != NULL) {
        if (dirstr->d_type == DT_REG) {
            printf("found %s\n", dirstr->d_name);
            // need some worker thread in here 
            pthread_create(&threads[i], NULL, integrateTrap, &workers[i]);
        } else if (dirstr->d_type == DT_DIR) {
            printf("found the dir %s\n", dirstr->d_name);
        }
    }
}

// NOTE
// what if I made a module where i can loop through a directory 
// and apply a function using the worker thread 
// or to some graph stuff
// maybe try this recurively

static void recursive_dfs(char *dir, char*pattern) {
    
     
}
