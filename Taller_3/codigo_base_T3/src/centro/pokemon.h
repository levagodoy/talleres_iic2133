#pragma once

typedef struct pokemon {
    int id;
    int hp;
    int speed;
} Pokemon;

Pokemon* pokemon_create(int id, int hp, int speed);
void pokemon_destroy(Pokemon* target);
