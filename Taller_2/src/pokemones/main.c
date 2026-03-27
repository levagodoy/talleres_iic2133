#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "events.h"


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

int main(int argc, char **argv) {
  check_arguments(argc, argv);

  FILE *input_file = fopen(argv[1], "r");
  FILE *output_file = fopen(argv[2], "w");

  int E;
  int result;

  result = fscanf(input_file, "%d", &E);
  if (result != 1) {
    printf("Error reading number of events");
    return 1;
  }

  char command[32];
  for (int i = 0; i < E; i++) {
    result = fscanf(input_file, "%s", command);
    if (result != 1) {
      printf("Error reading event");
      return 1;
    }

    if (string_equals(command, "SMALL_SORT")) {
      int n;
      char orden[32], atr[32];

      fscanf(input_file, "%d %s %s", &n, atr, orden);
      Pokemon * arr[n];
      
      for (int i = 0; i < n; i++){
        int id, nivel, vel;
        fscanf(input_file, "%d %d %d", &id, &nivel, &vel);

        Pokemon * new = calloc(1, sizeof(Pokemon));
        new -> id = id;
        new -> nivel = nivel;
        new -> vel = vel;

        arr[i] = new;
      }
      bool atr_b = false;
      bool orden_b = false;

      if (string_equals(atr, "NIVEL")) {atr_b = true;}

      if (string_equals(orden, "ASC")) {orden_b = true;}

      SMALL_SORT(input_file, output_file, arr, n, orden_b, atr_b);

      for (int i = 0; i < n; i++){
        free(arr[i]);
      }
    }

    else if (string_equals(command, "BIG_SORT")) {
      int n;
      char orden[32], atr[32], atr_2[32];

      fscanf(input_file, "%d %s %s %s", &n, atr, atr_2, orden);

      Pokemon * arr[n];

      for (int i = 0; i < n; i++){
        int id, nivel, vel;
        fscanf(input_file, "%d %d %d", &id, &nivel, &vel);

        Pokemon * new = calloc(1, sizeof(Pokemon));
        new -> id = id;
        new -> nivel = nivel;
        new -> vel = vel;

        arr[i] = new;
      }

      bool atr_b = (string_equals(atr, "NIVEL")) ? true : false;

      bool orden_b = (string_equals(orden, "ASC")) ? true : false;

      BIG_SORT(input_file, output_file, arr, n, orden_b, atr_b);

      for (int i = 0; i < n; i++){
        free(arr[i]);
      }
    }
  }

  /* Cerramos los archivos */
  fclose(input_file);
  fclose(output_file);

  return 0;
}
