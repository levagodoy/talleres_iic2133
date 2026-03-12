#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void ENTER(Magnezone * magnezone, Magnemite * magnemite, FILE *output_file){

    if (magnezone->head == NULL){
        magnezone->head = magnemite;
        magnezone->tail = magnemite;
    }

    else {
        magnezone->tail->next = magnemite;
        magnezone->tail = magnemite;
    }

    fprintf(output_file, "Magnemite %d ingreso a la manada %d.\n", magnemite->id, magnezone->id);

    return;
};

void FIND(Magnezone * magnezone, int ataque, FILE *output_file){

    int total = 0;
    int capacidad = 10;
    int *ids = malloc(capacidad * sizeof(int));
    Magnemite * actual = magnezone -> head;
    

    while (actual != NULL){
        if (actual -> atk == ataque){
            if (total == capacidad){
                capacidad = capacidad *2;
                ids = realloc(ids, capacidad * sizeof(int));
            }
            ids[total] = actual -> id;
            total++;
        }

        actual = actual -> next;
    }

    fprintf(output_file, "MagneZone %d encontrados %d:\n", magnezone -> id, total);

    for (int i = 0; i < total; i++){
        fprintf(output_file, "    Magnemite %d\n", ids[i]);
    }

    free(ids);
    return;
}


void INFO(Magnezone * magnezone, FILE *output_file){
    int total = 0;
    int id = magnezone -> id;

    Magnemite * actual = magnezone -> head;

    while(actual != NULL){
        total++;
        actual = actual -> next;    
    }

    fprintf(output_file, "MagneZone %d tiene %d magnemites.\n", id, total);

    return;
}


bool REMOVE(int magnemite_id, Magnezone * magnezone){
    if (magnezone -> head == NULL) return false;
    Magnemite * previo = magnezone -> head;

    if (previo -> id == magnemite_id){
        magnezone -> head = previo -> next;
        if (magnezone -> head == NULL) magnezone -> tail = NULL;
        free(previo);
        return true;
    }

    Magnemite * actual = previo -> next;
    while(actual != NULL){
        if (actual -> id == magnemite_id){
            previo -> next = actual -> next;
            if (magnezone -> tail == actual) magnezone -> tail = previo;
            free(previo);
            return true;
        }
        previo = actual;
        actual = previo -> next;
    }
    return false;
}
