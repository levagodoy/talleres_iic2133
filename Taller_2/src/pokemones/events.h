#pragma once
#include "structs.h"
#include "sort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void SMALL_SORT(FILE *input_file, FILE *output_file, Pokemon * arr[], int n, bool orden, bool atr);
void BIG_SORT(FILE *input_file, FILE *output_file, Pokemon * arr[], int n, bool orden, bool atr);
