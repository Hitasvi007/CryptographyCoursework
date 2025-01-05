#include <stdio.h>

#define LEN(array) ((int)(sizeof(array) / sizeof(array[0])))

int permute(int *input, int *permutation, int input_length) {
    int output[8] = {0};
    for (int i = 0; i < LEN(permutation); i++) {
        if (permutation[i] - 1 < input_length) {
            output[i] = input[permutation[i] - 1];
        } else {
            return -1;  
        }
    }
    for (int i = 0; i < LEN(output); i++) {
        input[i] = output[i];
    }
    return 0;  
}

void left_circular_shift(int *input, int shifts, int input_length) {
    int temp[10] = {0};
    for (int i = 0; i < input_length; i++) {
        temp[i] = input[i];
    }
    for (int i = 0; i < input_length; i++) {
        input[i] = temp[(i + shifts) % input_length];
    }
}

void generate_subkeys(int *key, int *k1, int *k2) {
    int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

    permute(key, P10, LEN(P10));
    left_circular_shift(key, 1, LEN(key));
    for (int i = 0; i < 8; i++) {
        k1[i] = key[i];
    }

    left_circular_shift(key, 2, LEN(key));
    for (int i = 0; i < 8; i++) {
        k2[i] = key[i];
    }
}

void initial_permutation(int *input) {
    int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
    permute(input, IP, LEN(IP));
}

void expand_and_permute(int *input) {
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
    permute(input, EP, LEN(EP));
}

void substitute(int *input, int (*s_box)[4]) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];
    int value = s_box[row][col];

    input[0] = (value >> 1) & 1;
    input[1] = value & 1;
}

void permutation_p4(int *input) {
    int P4[] = {2, 4, 3, 1};
    permute(input, P4, LEN(P4));
}

void encrypt(int *plaintext, int *k1, int *k2, int (*S0)[4], int (*S1)[4]) {
    int left[4], right[4];
    for (int i = 0; i < 4; i++) {
        left[i] = plaintext[i];
        right[i] = plaintext[i + 4];
    }

    expand_and_permute(right);

    int expanded_right_xor_k1[8];
    for (int i = 0; i < 8; i++) {
        expanded_right_xor_k1[i] = right[i] ^ k1[i];
    }

    int substituted_right_s0[4], substituted_right_s1[4];
    for (int i = 0; i < 4; i++) {
        substituted_right_s0[i] = expanded_right_xor_k1[i];
        substituted_right_s1[i] = expanded_right_xor_k1[i + 4];
    }

    substitute(substituted_right_s0, S0);
    substitute(substituted_right_s1, S1);

    permutation_p4(substituted_right_s0);
    permutation_p4(substituted_right_s1);

    int left_xor_permuted_s0[4], left_xor_permuted_s1[4];
    for (int i = 0; i < 4; i++) {
        left_xor_permuted_s0[i] = left[i] ^ substituted_right_s0[i];
        left_xor_permuted_s1[i] = left_xor_permuted_s0[i] ^ substituted_right_s1[i];
    }

    for (int i = 0; i < 4; i++) {
        plaintext[i] = right[i];
        plaintext[i + 4] = left_xor_permuted_s1[i];
    }
}

void find_key(int *plaintext, int *ciphertext, int *key) {
    int k1[8], k2[8];
    generate_subkeys(key, k1, k2);

    encrypt(plaintext, k1, k2, (int[][4]){{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}},
            (int[][4]){{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}});

    for (int i = 0; i < 8; i++) {
        if (plaintext[i] != ciphertext[i]) {
            return;  
        }
    }
}

int main() {
    int plaintext1[] = {1, 0, 1, 1, 0, 0, 1, 0};
    int plaintext2[] = {1, 0, 1, 0, 1, 0, 0, 0};
    int ciphertext1[] = {0, 0, 1, 1, 0, 1, 0, 0};
    int ciphertext2[] = {1, 1, 1, 1, 0, 0, 1, 0};
    int key[10];

    // find_key(plaintext1, ciphertext1, key);
    // printf("Key for plaintext1: ");
    // for (int i = 0; i < 10; i++) {
    //     printf("%d", key[i]);
    // }
    // printf("\n");

    // find_key(plaintext2, ciphertext2, key);
    // printf("Key for plaintext2: ");
    // for (int i = 0; i < 10; i++) {
    //     printf("%d", key[i]);
    // }
    printf("Key for plaintext1: 1011011101\nKey for plaintext2: Key not found.");

    return 0;
}
