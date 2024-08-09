#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_t queue_t;

// dynamically sized queue
typedef struct queue_t{
    int len;
    int capacity;

    queue_t *(*qinit)();
    char *(*qPop)(queue_t*);
    void (*qPush)(queue_t*, char*);

    char *arr[];
} queue_t;

queue_t *qinit();
char *qPop(queue_t* queue);
void qPush(queue_t* queue, char* e);

#endif
