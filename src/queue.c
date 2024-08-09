#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

#define DEF_QUEUE_CAP 20
static void qResize(queue_t* queue);

queue_t *qinit() {
    queue_t *q = (queue_t*)malloc(sizeof(queue_t) * DEF_QUEUE_CAP);
    if (q == NULL) {
        perror("could not reallocate memory");
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

    return queue->arr[queue->len--];
}


void qPush(queue_t* queue, char *e) {
    if (queue->len == queue->capacity) {
        qResize(queue);
    }

    queue->arr[++queue->len] = e;
}

static void qResize(queue_t* queue) {
    int newCap = sizeof(queue_t) * queue->capacity * 2;
    queue = realloc(queue, newCap);
    if (queue == NULL) {
        perror("could not reallocate memory");
        exit(1);
    }
    queue->capacity = newCap;
}
