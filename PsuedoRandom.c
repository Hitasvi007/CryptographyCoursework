#include <stdio.h>

/* Global variables for the LCG */
unsigned long seed = 1;
const unsigned long a = 1664525;
const unsigned long c = 1013904223;
const unsigned long m = 4294967296; // 2^32

/* Function to generate a pseudo-random number */
unsigned long rand_num() {
    seed = (a * seed + c) % m;
    return seed;
}

int main() {
    int i;
    printf("Generating 10 pseudo-random numbers:\n");
    for (i = 0; i < 10; i++) {
        printf("%lu\n", rand_num());
    }
    return 0;
}







#include <stdio.h>

/* Global variables for the MCM */
unsigned long seed = 1;
const unsigned long a = 22695477;
const unsigned long m = 4294967296; // 2^32

/* Function to generate a pseudo-random number */
unsigned long rand_num() {
    seed = (a * seed) % m;
    return seed;
}

int main() {
    int i;
    printf("Generating 10 pseudo-random numbers using Multiplicative Congruential Method:\n");
    for (i = 0; i < 10; i++) {
        printf("%lu\n", rand_num());
    }
    return 0;
}














#include <stdio.h>

/* Global variables for the CLCG */
unsigned long seed1 = 1;
unsigned long seed2 = 2;
const unsigned long a1 = 1664525;
const unsigned long c1 = 1013904223;
const unsigned long m1 = 4294967296; // 2^32

const unsigned long a2 = 22695477;
const unsigned long long m2 = 4294967296ULL; // 2^32 as unsigned long long

/* Function to generate a pseudo-random number */
unsigned long rand_num() {
    seed1 = (a1 * seed1 + c1) % m1;
    seed2 = (a2 * seed2) % m2;
    return (seed1 + seed2) % m1;
}

int main() {
    int i;
    printf("Generating 10 pseudo-random numbers using Combined Linear Congruential Method:\n");
    for (i = 0; i < 10; i++) {
        printf("%lu\n", rand_num());
    }
    return 0;
}



