/* autores: José Henrique da Silva Braz */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

hashmap_t* hashmap_init() {
    hashmap_t* hashmap = (hashmap_t *) malloc(sizeof(hashmap_t));

    if (hashmap == NULL) {
        perror("Não foi possivel criar a pilha!");
        return NULL;
    }

    hashmap->size = 0;
    hashmap->actual_capacity = HASHMAP_INITIAL_CAPACITY;
    hashmap->values = (hashmap_entry_t **) calloc(HASHMAP_INITIAL_CAPACITY, sizeof(hashmap_entry_t*));

    if (hashmap->values == NULL) {
        perror("Não foi possivel alocar memória inicial para as entradas da tabela!");
        return NULL;
    }

    return hashmap;
}

void hashmap_alloc_more_mem(hashmap_t *map) {
    printf("hashmap_alloc_more_mem size %d\n", map->size);
    int old_capacity = map->actual_capacity;
    int old_size = map->size;
    hashmap_entry_t **old_values = map->values;

    
    int new_capacity = map->actual_capacity * HASHMAP_REALLOC_FACTOR;
    map->values = (hashmap_entry_t **) calloc(new_capacity, sizeof(hashmap_entry_t *));
    map->actual_capacity = new_capacity;
    map->size = 0;
    if (map->values == NULL) {
        perror("Não foi possivel alocar mais memória para o map!");
        exit(1);
    }

    int count = 0, index = 0;
    while (count < old_size && index < old_capacity) {
        if (old_values[index] != NULL) {
            hashmap_put(map, &(old_values[index]->key), &(old_values[index]->value));
            count++;
        }
        index++;
    }
    free(old_values);
}

int hashmap_hashcode(const hashmap_key_t *key) {
    int i;
    int sum = 0;
    int len = strlen(key->key);
    for (i = 0; i < len; i++) {
        sum += key->key[i] * 31;
    }
    return sum;
}

int hashmap_index(const hashmap_t *map, const hashmap_key_t *key) {
    return hashmap_hashcode(key) % map->actual_capacity;
}

void hashmap_put(hashmap_t *map, const hashmap_key_t *key, const hashmap_value_t *value) {
    static int all_conflits = 0;
    int index, conflits = 0;
    hashmap_entry_t *entry;

    if (map->size >= (map->actual_capacity / 2)) {
        // não deixa enxer muito a tabela para evitar muitos conflitos
        hashmap_alloc_more_mem(map);
    }

    index = hashmap_index(map, key);
    // vai percorrendo os valores até chegar em um local sem conflito
    while ((entry = map->values[index]) != NULL) {
        conflits++;
        index = (index + 3) % map->actual_capacity;
    }
    if (conflits > 0) {
        all_conflits += conflits;
        printf("CONFLITO PUT %d all %d capacity %d size %d\n", conflits, all_conflits, map->actual_capacity, map->size);
    }

    entry = (hashmap_entry_t *) malloc(sizeof(hashmap_entry_t));
    memcpy(entry->key.key, key->key, strlen(key->key));
    memcpy(entry->value.value, value->value, strlen(value->value));
    map->values[index] = entry;
    map->size++;
}

int hashmap_compare_key(const hashmap_key_t *key1, const hashmap_key_t *key2) {
    return strcmp(key1->key, key2->key);
}

hashmap_entry_t *hashmap_entry(const hashmap_t *map, const hashmap_key_t *key, int *out_index) {
    int conflits = 0;
    int index = hashmap_index(map, key);
    hashmap_entry_t *entry = map->values[index];
    while ((entry == NULL || hashmap_compare_key(&(entry->key), key) != 0) && 
            conflits < map->actual_capacity) {
        conflits++;
        index = (index + 3) % map->actual_capacity;
        entry = map->values[index];
    }
    if (conflits >= map->actual_capacity) { // não achamos a entrada
        entry = NULL;
        *out_index = -1;
    } else {
        *out_index = index;
    }
    return entry;
}

int hashmap_get(const hashmap_t *map, const hashmap_key_t *key, hashmap_value_t *value) {
    int index;
    hashmap_entry_t *entry = hashmap_entry(map, key, &index);
    if (entry == NULL) {
        memcpy(value->value, "\0", 1);
        return 0;
    } else {
        memcpy(value->value, entry->value.value, strlen(entry->value.value));
        return 1;
    }
}

int hashmap_remove(hashmap_t *map, const hashmap_key_t *key, hashmap_value_t *value) {
    int index;
    hashmap_entry_t *entry = hashmap_entry(map, key, &index);

    if (entry == NULL) {
        memcpy(value->value, "\0", 1);
        return 0;
    } else {
        memcpy(value->value, entry->value.value, strlen(entry->value.value));
        free(entry);
        map->values[index] = NULL;
        map->size--;
        return 1;
    }
}