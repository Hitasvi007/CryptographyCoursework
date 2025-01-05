#include <stdio.h>

long long calculateModularExponentiation(long long base, long long exponent, long long modulus) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    long long base, exponent, modulus;
    
    printf("Enter the base: ");
    scanf("%lld", &base);
    
    printf("Enter the exponent: ");
    scanf("%lld", &exponent);
    
    printf("Enter the modulus: ");
    scanf("%lld", &modulus);
    
    long long result = calculateModularExponentiation(base, exponent, modulus);
    
    printf("%lld^%lld mod %lld = %lld\n", base, exponent, modulus, result);
    
    return 0;
}
