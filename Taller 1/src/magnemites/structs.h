#pragma once
#include <stdio.h>
#include <stdbool.h>


typedef struct magnemite {
    int id;
    int atk;
    int speed;
    int magnezone_id;
    struct magnemite * next; // Con el asterisco sabe cuanto espacio usar. (puntero)
} Magnemite;

typedef struct magnezone{

    int id;
    struct magnemite * head;
    struct magnemite * tail;

} Magnezone;


void ENTER(Magnezone * magnezone, Magnemite * magnemite, FILE *output_file);
void FIND(Magnezone * magnezone, int ataque, FILE *output_file);
void INFO(Magnezone * magnezone, FILE *output_file);
bool REMOVE(int magnemite_id, Magnezone * magnezone);
