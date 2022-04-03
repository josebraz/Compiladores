/* autores: José Henrique da Silva Braz */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "types.h"

#define HASHMAP_INITIAL_CAPACITY 100
#define HASHMAP_REALLOC_FACTOR 3
#define HASHMAP_KEY_SIZE 20

hashmap_t* hashmap_init(char *label);

int hashmap_hashcode(const char *key);

int hashmap_index(const hashmap_t *map, const char *key);

void hashmap_put(hashmap_t *map, const char *key, const hashmap_value_t *value);

hashmap_value_t *hashmap_get(const hashmap_t *map, const char *key);

hashmap_value_t *hashmap_remove(hashmap_t *map, const char *key);

#endif