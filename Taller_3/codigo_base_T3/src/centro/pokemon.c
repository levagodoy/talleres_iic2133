#include "pokemon.h"

#include <stdlib.h>

Pokemon* pokemon_create(int id, int hp, int speed) {
    Pokemon* new_pokemon = malloc(sizeof(Pokemon));

    new_pokemon->id = id;
    new_pokemon->hp = hp;
    new_pokemon->speed = speed;

    return new_pokemon;
}

void pokemon_destroy(Pokemon* target) {
    free(target);
}
