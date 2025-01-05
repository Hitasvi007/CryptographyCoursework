#include <stdio.h> 
 
int pow_mod(int base, int exp, int mod) { 
    int result = 1; 
    while (exp > 0) { 
        if (exp % 2 == 1) { 
            result = (result * base) % mod; 
        } 
        base = (base * base) % mod; 
        exp /= 2; 
    } 
    return result; 
} 
 
int inverse_mod(int a, int b) { 
    int b0 = b, t, q; 
    int x0 = 0, x1 = 1; 
    if (b == 1) return 1; 
    while (a > 1) { 
        q = a / b; 
        t = b, b = a % b, a = t; 
        t = x0, x0 = x1 - q * x0, x1 = t; 
    } 
    if (x1 < 0) x1 += b0; 
    return x1; 
} 
 
 
int main() { 
    int e = 13; 
    int d = 7; 
    int N = 33; 
    int r = 3; 
    int M = 5; 
 
     
 
    int cipher = pow_mod(M, e, N); 
    printf("==Initial values ====\n"); 
     printf("e=%d, d=%d, N=%d\n", e, d, N); 
    printf("message=%d, r=%d\n", M, r); 
    printf("=====================\n\n"); 
 
    printf("Initial cipher:\t%d\n", cipher); 
 
    int cipher_dash = (cipher * pow_mod(r, e, N)) % N; 
    printf("Eve gets Bob to decipher:\t%d\n", cipher_dash); 
 
    int decipher = pow_mod(cipher_dash, d, N); 
    printf("Bob says that the result is wrong: %d\n", decipher); 
 
    int res = (decipher * inverse_mod(r, N)) % N; 
    printf("Eve determines as: %d\n", res); 
 
    if (res == M) { 
        printf("Eve has cracked the message, as result is same as message\n"); 
    } else { 
        printf("Eve has not cracked the message\n"); 
    } 
 
    return 0; 
}