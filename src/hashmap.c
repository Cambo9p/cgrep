#include "../include/hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 94 // all ascii chars we want
#define SPACE_VAL 32

// maps chars to ints
typedef struct {
    char *keys;
    int *values;
} hashmap_t; // 5 bytes size

static int gethash(char ch) {
    return (int)ch - SPACE_VAL;
}

extern map_t map_new() {
    hashmap_t *map = (hashmap_t*)malloc(sizeof(hashmap_t));
    if (!map) {
        map_free(map);
        return NULL;
    }

    map->keys = (char*) calloc(MAP_SIZE, sizeof(hashmap_t));
    if (!map->keys) {
        map_free(map);
        return NULL;
    }

    map->values = (int*) calloc(MAP_SIZE, sizeof(hashmap_t));
    if (!map->values) {
        map_free(map);
        return NULL;
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        map->values[i] = - 1;
        map->keys[i] = (char)(i + SPACE_VAL);
    }

    return map;
}

extern void map_put(map_t map, char key, int val) {
    hashmap_t *m = (hashmap_t*)map;
    int bucket = gethash(key);

    m->values[bucket] = val;
}

extern int map_get(map_t map, char key) {
    hashmap_t *m = (hashmap_t*)map;
    if ((int)key > 127 || (int)key < SPACE_VAL) {
        return -1;
    }
    int bucket = gethash(key);

    return m->values[bucket];
}

extern void map_free(map_t map) {
    hashmap_t *m = (hashmap_t*)map;

    free(m->values);
    free(m->keys);
    free(m);
}

extern void map_print(map_t map) {
    hashmap_t *m = (hashmap_t*)map;

    for (int i = 0; i < MAP_SIZE; i++) {
        printf("%c : %d\n", m->keys[i], m->values[i]);
    }
}
