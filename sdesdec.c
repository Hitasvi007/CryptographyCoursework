#include <stdio.h>

// Key generation functions

int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

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

int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

int P4[] = {2, 4, 3, 1};

int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

void initialPermutation(int *input, int *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[IP[i] - 1];
    }
}

void expandAndPermute(int *input, int *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[EP[i] - 1];
    }
}

void xorArrays(int *a, int *b, int size) {
    for (int i = 0; i < size; i++) {
        a[i] ^= b[i];
    }
}

void substitute(int *input, int *output, int sBox[4][4]) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];
    int value = sBox[row][col];

    output[0] = (value >> 1) & 1;
    output[1] = value & 1;
}

void permutationP4(int *input, int *output) {
    for (int i = 0; i < 4; i++) {
        output[i] = input[P4[i] - 1];
    }
}

void swap(int *left, int *right, int size) {
    for (int i = 0; i < size; i++) {
        int temp = left[i];
        left[i] = right[i];
        right[i] = temp;
    }
}

void encrypt(int *plaintext, int *k1, int *k2, int *ciphertext) {
    // Initial Permutation
    int IP_result[8];
    initialPermutation(plaintext, IP_result);

    int left[4], right[4];
    for (int i = 0; i < 4; i++) {
        left[i] = IP_result[i];
        right[i] = IP_result[i + 4];
    }

    // Round 1
    int expandedRight[8];
    expandAndPermute(right, expandedRight);
    xorArrays(expandedRight, k1, 8);

    int substitutedRight[4];
    substitute(expandedRight, substitutedRight, S0);

    int permutedRight[4];
    permutationP4(substitutedRight, permutedRight);

    xorArrays(left, permutedRight, 4);
    swap(left, right, 4);

    // Round 2
    expandAndPermute(right, expandedRight);
    xorArrays(expandedRight, k2, 8);

    substitute(expandedRight, substitutedRight, S1);
    permutationP4(substitutedRight, permutedRight);

    xorArrays(left, permutedRight, 4);

    for (int i = 0; i < 4; i++) {
        ciphertext[i] = right[i];
        ciphertext[i + 4] = left[i];
    }
}

void decrypt(int *ciphertext, int *k1, int *k2, int *plaintext) {
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = k1[i];
        k1[i] = k2[i];
        k2[i] = temp[i];
    }

    encrypt(ciphertext, k1, k2, plaintext);
}

int main() {
    int ciphertext[] = {1, 0, 1, 0, 0, 1, 0, 1};
    int key[] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 1};

    int decryptedPlaintext[8];

    int k1[8], k2[8];
    generateSubKeys(key, k1, k2);

    decrypt(ciphertext, k1, k2, decryptedPlaintext);

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    printf("Key: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", key[i]);
    }
    printf("\n");

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", decryptedPlaintext[i]);
    }
    printf("\n");

    return 0;
}
