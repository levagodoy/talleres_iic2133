#pragma once
#include "pokemon.h"

#include <stdbool.h>

typedef struct heap {
    Pokemon** array;
    unsigned long size;
    unsigned long used;
    char attribute[16];
    bool is_min_heap;
} Heap;

Heap* heap_create(unsigned long size, char* attribute, int attribute_length, bool is_min_heap);
void heap_destroy(Heap* target);
void heap_swap(Heap* target, unsigned long first_idx, unsigned long second_idx);
int heap_priority(Heap* target, unsigned long pokemon_index);
unsigned long heap_compare_priority(Heap* target, unsigned long first_index, unsigned long second_index);
void heap_sift_up(Heap* target, unsigned long pokemon_index);
void heap_sift_down(Heap* target, unsigned long pokemon_index);
void heap_insert(Heap* target, int id, int hp, int speed);
int heap_extract(Heap* target);
