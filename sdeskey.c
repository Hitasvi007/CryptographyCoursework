#include <stdio.h>


int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

// Left Circular Shifts
int LS1[] = {2, 4, 1, 3, 0};
int LS2[] = {1, 3, 0, 2};

int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

void permute(int *input, int *permutation, int size) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = input[permutation[i] - 1];
    }
    for (int i = 0; i < size; i++) {
        input[i] = temp[i];
    }
}

void leftCircularShift(int *input, int size, int *shifts, int num_shifts) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = input[(i + num_shifts) % size];
    }
    for (int i = 0; i < size; i++) {
        input[i] = temp[i];
    }
}

void generateSubKeys(int *key, int *k1, int *k2) {
    
    permute(key, P10, 10);

    leftCircularShift(key, 5, LS1, 1);
    leftCircularShift(key + 5, 5, LS1, 1);

    permute(key, P8, 8);
    for (int i = 0; i < 8; i++) {
        k1[i] = key[i];
    }

    leftCircularShift(key, 5, LS2, 2);
    leftCircularShift(key + 5, 5, LS2, 2);

    permute(key, P8, 8);
    for (int i = 0; i < 8; i++) {
        k2[i] = key[i];
    }
}

int main() {
    int key[] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 1};

    int k1[8], k2[8];

    generateSubKeys(key, k1, k2);

    printf("Key 1: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", k1[i]);
    }
    printf("\n");

    printf("Key 2: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", k2[i]);
    }
    printf("\n");

    return 0;
}
