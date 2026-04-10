#include "heap.h"
#include "pokemon.h"

#include <stdlib.h>
#include <string.h>

Heap* heap_create(unsigned long size, char* attribute, int attribute_length, bool is_min_heap) {
    Heap* new_heap = calloc(1, sizeof(Heap));

    new_heap->array = calloc(size, sizeof(Pokemon*));
    new_heap->size = size;
    new_heap->used = 0;
    strncpy(new_heap->attribute, attribute, attribute_length);
    new_heap->is_min_heap = is_min_heap;

    return new_heap;
};

void heap_destroy(Heap* target) {
    for (unsigned long i = 0; i < target->size; i++) {
        pokemon_destroy(target->array[i]);
    }

    free(target->array);
    free(target);
}

void heap_swap(Heap* target, unsigned long first_idx, unsigned long second_idx) {
    if (first_idx >= target->size || second_idx >= target->size) return;

    Pokemon* tmp = target->array[second_idx];
    target->array[second_idx] = target->array[first_idx];
    target->array[first_idx] = tmp;
}

int heap_priority(Heap* target, unsigned long pokemon_index) {
    int pokemon_field = 0;
    if (!strncmp(target->attribute, "HP", 2)) {
        pokemon_field = target->array[pokemon_index]->hp;
    } else if (!strncmp(target->attribute, "Speed", 5)) {
        pokemon_field = target->array[pokemon_index]->speed;
    }

    if (target->is_min_heap) {
        pokemon_field *= -1;
    }

    return pokemon_field;
}

unsigned long heap_compare_priority(Heap* target, unsigned long first_index, unsigned long second_index) {
    int first_priority = heap_priority(target, first_index);
    int second_priority = heap_priority(target, second_index);

    unsigned long higher_priority_index = first_index;
    if (second_priority > first_priority || (second_priority == first_priority && second_index < first_index)) {
        higher_priority_index = second_index;
    }

    return higher_priority_index;
}

void heap_sift_up(Heap* target, unsigned long pokemon_index) {
    bool in_position = false;
    while (!in_position) {
        if (pokemon_index == 0) {
            in_position = true;
            continue;
        }

        long parent_index = (pokemon_index - 1) / 2;
        if (pokemon_index == heap_compare_priority(target, pokemon_index, parent_index)) {
            heap_swap(target, pokemon_index, parent_index);
            pokemon_index = parent_index;
        } else {
            in_position = true;
        }
    }
}

void heap_sift_down(Heap* target, unsigned long pokemon_index) {
    unsigned long max_priority_index;
    unsigned long child_index;
    bool in_position = false;
    while (!in_position) {
        max_priority_index = pokemon_index;
        child_index = 2 * pokemon_index + 1;
        if (child_index < target->used) {
            max_priority_index = heap_compare_priority(target, max_priority_index, child_index);
        }

        child_index++;
        if (child_index < target->used) {
            max_priority_index = heap_compare_priority(target, max_priority_index, child_index);
        }

        if (max_priority_index == pokemon_index) {
            in_position = true;
            continue;
        }

        heap_swap(target, pokemon_index, max_priority_index);
        pokemon_index = max_priority_index;
    }
}

void heap_insert(Heap* target, int id, int hp, int speed) {
    if (target->used >= target->size) return;

    Pokemon* new_pokemon = pokemon_create(id, hp, speed);
    target->array[target->used] = new_pokemon;
    target->used += 1;
    unsigned long new_index = target->used - 1;

    heap_sift_up(target, new_index);
}

int heap_extract(Heap* target){

    int id = target->array[0] -> id;
    int last = target -> used - 1;

    heap_swap(target, 0, last);
    target -> used -=1;

    heap_sift_down(target, 0);

    return id;
}