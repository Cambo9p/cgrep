#ifndef HASHMAP_H
#define HASHMAP_H

#define MAP_SIZE 94

#define MAP_OK 0
#define MAP_MISING -1

// this implementation isnt really a map just an array
typedef void* map_t;

// allocates space for a new map
map_t map_new();

// adds/overides a key value pair in the map
void map_put(map_t map, char key, int val);

// returns -1 if theres no value 
int map_get(map_t map, char key);

// frees all memory used by the map
void map_free(map_t map);

// prints the contents of the map to stdout
void map_print(map_t map);

#endif 
