#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

/* Retorna true si ambos strings son iguales */
static bool string_equals(char *string1, char *string2) {
    return !strcmp(string1, string2);
}

static bool check_arguments(int argc, char **argv) {
    if (argc != 3) {
        printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
        printf("Donde:\n");
        printf("\tINPUT es la ruta del archivo de input\n");
        printf("\tOUTPUT es la ruta del archivo de output\n");
        exit(1);
    }
    return true;
}

int main(int argc, char **argv){
    /* Definicion de argumentos */
    check_arguments(argc, argv);
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    int M; // Cantidad maxima de Pokemon
    int N; // Cantidad de eventos

    //La funcion fscanf lee desde el archivo de input segun los especificadores de formato en el string
    //del segundo argumento. Lo que lea, se guarda en la dirección de memoria especificada en el tercer argumento
    //Se guarda en buffer un int de status para confirmar si todo salió bien. 
    int buffer = fscanf(input_file, "%d", &M);

    if (buffer != 1) {
        printf("Error reading maximum number of pokemon\n");
        return 1;
    }

    buffer = fscanf(input_file, "%d", &N);

    if (buffer != 1) {
        printf("Error reading number of events\n");
        return 1;
    }

    /* Eventos */

    char command[32];
    int heaps_size = 2;
    Heap* heaps[heaps_size];

    heaps[0] = heap_create(M, "HP", 2, true);
    heaps[1] = heap_create(M, "Speed", 5, false);

    for (int i = 0; i < N; i++){
        buffer = fscanf(input_file, "%s", command);
        if (buffer != 1) {
            printf("Error reading event\n");
            return 1;
        }

        if (string_equals(command, "ENTER")){
            int id, hp, speed;
            fscanf(input_file, "%d %d %d", &id, &hp, &speed);

            heap_insert(heaps[0], id, hp, speed);
            heap_insert(heaps[1], id, hp, speed);

            fprintf(output_file, "Centro Pokemon: nuevo pokemon id %d\n", id);
        }


        else if (string_equals(command, "EXTRACT")){
            char attr[32];
            fscanf(input_file, "%s", attr);

            int idx = strcmp(attr, "HP") ? 1 : 0;

            int id = heap_extract(heaps[idx]);
            fprintf(output_file, "Centro Pokemon: atendido id %d segun prioridad %s\n", id, attr);
        }


    }

    /* Liberamos memoria y cerramos archivos */

    for (int i = 0; i < heaps_size; i++) {
        heap_destroy(heaps[i]);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
