#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"



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

    int S; // Cantidad maxima de magneZones
    int E; // Cantidad de eventos



    //La funcion fscanf lee desde el archivo de input segun los especificadores de formato en el string
    //del segundo argumento. Lo que lea, se guarda en la dirección de memoria especificada en el tercer argumento
    //Se guarda en buffer un int de status para confirmar si todo salió bien. 
    int buffer = fscanf(input_file, "%d", &S);

    if (buffer != 1) {
    printf("Error reading maximum number of sectors");
    return 1;
    }

    buffer = fscanf(input_file, "%d", &E);

    if (buffer != 1) {
        printf("Error reading number of events");
        return 1;
    }


    /* Eventos */


    char command[32];

    Magnezone * magnezones[S];

    for (int i = 0; i < S; i++){
        Magnezone * new = (Magnezone *) calloc(1, sizeof(Magnezone));
        new->id = i;
        new->head = NULL;
        new->tail = NULL;

        magnezones[i] = new;
    }

    for (int i = 0; i < E; i++){
        
        buffer = fscanf(input_file, "%s", command);
        if (buffer != 1) {
            printf("Error reading event");
            return 1;
        }

        if (string_equals(command, "ENTER")){
            
            int magnezone_id;
            int magnemite_id;
            int atk;
            int speed;

            fscanf(input_file, "%d %d %d %d", &magnezone_id, &magnemite_id, &atk, &speed);
            
            Magnemite * new = (Magnemite *) calloc(1, sizeof(Magnemite));
            new->id = magnemite_id;
            new->atk = atk;
            new->speed = speed;
            new->next = NULL;
            new->magnezone_id = magnezone_id;

            Magnezone * obj = magnezones[magnezone_id];
            ENTER(obj, new, output_file);

        }
        else if (string_equals(command, "FIND")){
            int magnezone_id;
            int atk;
            fscanf(input_file, "%d %d", &magnezone_id, &atk);
            Magnezone * op = magnezones[magnezone_id];

            FIND(op, atk, output_file);

        }

        else if (string_equals(command, "REMOVE")){
            int magnemite_id;
            fscanf(input_file, "%d", &magnemite_id);

            for (int i = 0; i < S; i++){
                Magnezone * mag_t = magnezones[i];
                if (REMOVE(magnemite_id, mag_t)){
                    fprintf(output_file, "Magnemite %d abandono a su magnezone.\n", magnemite_id);
                    break;
                }
                else continue;
            }

        }

        else if (string_equals(command, "INFO")){
            int magnezone_id;
            fscanf(input_file, "%d", &magnezone_id);
            Magnezone * obj = magnezones[magnezone_id];
            INFO(obj, output_file);

        }

    }


    return 0;
}