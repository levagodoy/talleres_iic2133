#include "events.h"
#include "sort.h"
#include "structs.h"

void SMALL_SORT(FILE *input_file, FILE *output_file, Pokemon * arr[], int n, bool orden, bool atr) {
    const char *out2 = (orden) ? "ASC" : "DESC"; // ? (if true) : (if false)
    const char *out1 = (atr) ? "NIVEL" : "VELOCIDAD"; // tmb se usa const char cuando se hace en string for whatever reason
    fprintf(output_file, "%d Pokemones ordenados por %s en orden %s:\n", n, out1, out2);

    int mult = (orden) ? 1 : -1; //transformamos los numeros a negativo si es DESC
    
    if (atr){
        for (int i = 1; i < n; ++i) {
            Pokemon * key = arr[i];
            int j = i - 1;

            while (j >= 0 && (arr[j] -> nivel * mult > key -> nivel * mult || 
                            (arr[j] -> nivel * mult == key -> nivel * mult && 
                                arr[j] -> id * mult > key -> id * mult))) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
    else{
        for (int i = 1; i < n; ++i) {
            Pokemon * key = arr[i];
            int j = i - 1;

            while (j >= 0 && (arr[j] -> vel * mult > key -> vel * mult || 
                            (arr[j] -> vel * mult == key -> vel * mult && 
                                arr[j] -> id * mult > key -> id * mult))) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }


    for (int i = 0; i < n; i++){
        Pokemon * act = arr[i];
        if (atr) fprintf(output_file, "\tPokemon ID %d: %s %d\n", act -> id, out1, act ->nivel);
        else fprintf(output_file, "\tPokemon ID %d: %s %d\n", act -> id, out1, act ->vel);
    }
}

void BIG_SORT(FILE *input_file, FILE *output_file, Pokemon * arr[], int n, bool orden, bool atr) {
    const char *atr1 = (atr) ? "NIVEL" : "VELOCIDAD";
    const char *atr2 = (atr) ? "VELOCIDAD" : "NIVEL";
    const char *orden_s = (orden) ? "ASC" : "DESC";
    int mod = (orden) ? 1 : -1;

    if (atr) mergesort_n(arr, 0 , n-1, mod);
    else mergesort_v(arr, 0 , n-1, mod);

    fprintf(output_file, "%d Pokemones ordenados por %s %s en orden %s:\n", n, atr1, atr2, orden_s);
    for (int i = 0; i < n; i++){
        Pokemon * act = arr[i];
        if (atr) fprintf(output_file, "\tPokemon ID %d: %s %d %s %d\n", act -> id, atr1, act ->nivel, atr2, act -> vel);
        else fprintf(output_file, "\tPokemon ID %d: %s %d %s %d\n", act -> id, atr1, act ->vel, atr2, act -> nivel);

}
}