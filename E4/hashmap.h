/* autores: José Henrique da Silva Braz */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "stdlib.h"

#define HASHMAP_INITIAL_CAPACITY 100
#define HASHMAP_REALLOC_FACTOR 3

typedef struct __hashmap_key {
    char key[20];
} hashmap_key_t;

typedef struct __hashmap_value {
    char value[100];
} hashmap_value_t;

typedef struct __hashmap_entry {
    hashmap_key_t key;
    hashmap_value_t value;
} hashmap_entry_t;

typedef struct __hashmap {
    int size;
    int actual_capacity;
    hashmap_entry_t **values;
} hashmap_t;

hashmap_t* hashmap_init();

int hashmap_hashcode(const hashmap_key_t *key);

int hashmap_index(const hashmap_t *map, const hashmap_key_t *key);

void hashmap_put(hashmap_t *map, const hashmap_key_t *key, const hashmap_value_t *value);

int hashmap_get(const hashmap_t *map, const hashmap_key_t *key, hashmap_value_t *value);

int hashmap_remove(hashmap_t *map, const hashmap_key_t *key, hashmap_value_t *value);

#endif