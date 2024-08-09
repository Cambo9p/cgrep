#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_QUEUE_CAP 20
static void qResize(queue_t* queue);

queue_t *qinit() {
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    if (q == NULL) {
        perror("could not allocate memory");
        exit(1);
    }

    q->arr = (char**)malloc(sizeof(char*) * DEF_QUEUE_CAP);
    if (q->arr == NULL) {
        perror("could not allocate memory");
        free(q);
        exit(1);
    }

    q->capacity = DEF_QUEUE_CAP;
    q->len = 0;

    return  q;
}

char *qPop(queue_t* queue) {
    if (queue->len == 0) {
        return NULL;
    }

    char *e = queue->arr[0];

    for (int i = 1; i < queue->len; i++) {
        queue->arr[i - 1] = queue->arr[i];
    }

    queue->len--;
    return e;
}


void qPush(queue_t* queue, char *e) {
    if (queue->len == queue->capacity) {
        qResize(queue);
    }

    queue->arr[queue->len] = (char*)malloc(strlen(e) + 1);
    if (queue->arr[queue->len] == NULL) {
        perror("could not allocate memory for queue element");
        exit(1);
    }

    strcpy(queue->arr[queue->len], e);
    queue->len++;
}

void qfree(queue_t* queue) {
    free(queue);
}

void qprint(queue_t* queue) {
    for (int i = 0; i < queue->len; i++) {
        printf("%s ", queue->arr[i]);
    }
    printf("\n");
}

static void qResize(queue_t* queue) {
    int newCap = sizeof(queue_t) * queue->capacity * 2;
    char **newArr = realloc(queue->arr, sizeof(char*) * newCap);
    if (newArr == NULL) {
        perror("could not reallocate memory");
        exit(1);
    }
    queue->capacity = newCap;
    queue->arr = newArr;
}
