#include "sort.h"

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge_n(Pokemon * arr[], int left, int mid, int right, int mod){
    
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pokemon* L[n1];
    Pokemon* R[n2]; 

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        bool derecha = false; //derecha es mayor!
        if (L[i] -> nivel * mod < R[j] -> nivel * mod) {
            derecha = true;
        }
        else if (L[i] -> nivel * mod == R[j] -> nivel * mod){
            if (L[i] -> vel * mod < R[j] -> vel * mod){
                derecha = true;
            }
            else if (L[i] -> vel * mod == R[j] -> vel * mod){
                if (L[i] -> id * mod < R[j] -> id * mod){
                    derecha = true;
                }
            }
        }
        if (derecha){
            arr[k] = L[i];
            i++;
            k++;
        }
        else{
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort_n(Pokemon * arr[], int left, int right, int mod){
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_n(arr, left, mid, mod);
        mergesort_n(arr, mid + 1, right, mod);
        merge_n(arr, left, mid, right, mod);
    }
}

void merge_v(Pokemon * arr[], int left, int mid, int right, int mod){
    
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pokemon* L[n1];
    Pokemon* R[n2]; 

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        bool derecha = false; //derecha es mayor!
        if (L[i] -> vel * mod < R[j] -> vel * mod) {
            derecha = true;
        }
        else if (L[i] -> vel * mod == R[j] -> vel * mod){
            if (L[i] -> nivel * mod < R[j] -> nivel * mod){
                derecha = true;
            }
            else if (L[i] -> nivel * mod == R[j] -> nivel * mod){
                if (L[i] -> id * mod < R[j] -> id * mod){
                    derecha = true;
                }
            }
        }
        if (derecha){
            arr[k] = L[i];
            i++;
            k++;
        }
        else{
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort_v(Pokemon * arr[], int left, int right, int mod){
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_v(arr, left, mid, mod);
        mergesort_v(arr, mid + 1, right, mod);
        merge_v(arr, left, mid, right, mod);
    }
}