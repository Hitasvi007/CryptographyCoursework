#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
int euclidean(int a, int b) { 
    int q, r; 
    while (b != 0) { 
        q = a / b; 
        r = a % b; 
        a = b; 
        b = r; 
    } 
    if (a == 1) { 
        return 0; 
    } 
    return 1; 
} 
 
int random_relatively_prime(int phi_n) { 
    srand(time(NULL)); 
    int min = 2; 
    int e = min + rand() % (phi_n - min); 
    while (euclidean(e, phi_n) || e == 1) { 
        e = min + rand() % (phi_n - min); 
    } 
    return e; 
} 
 
int extended_euclidean(int a, int b) { 
    int q, r, t1 = 0, t2 = 1, t; 
    int original_b = b; 
    while (a != 0) { 
        q = b / a; 
        r = b % a; 
        t = t1 - q * t2; 
        b = a; 
        a = r; 
        t1 = t2; 
        t2 = t; 
    } 
    if (t1 < 0) 
        t1 += original_b; 
    return t1; 
} 
 
void key_generation(int p, int q, int public_key[], int private_key[]) { 
    int n = p * q; 
    int phi_n = (p - 1) * (q - 1); 
    int e = random_relatively_prime(phi_n); 
    public_key[0] = n; 
    public_key[1] = e; 
    private_key[0] = n; 
    private_key[1] = extended_euclidean(e, phi_n); 
} 
 
int encryption(int private_key[], int plaintext) { 
    int ciphertext = 1; 
    int key = private_key[1]; 
    plaintext = plaintext % private_key[0]; 
    while (key > 0) { 
        if (key % 2 == 1) { 
            ciphertext = (ciphertext * plaintext) % private_key[0]; 
        } 
        key = key >> 1; 
        plaintext = (plaintext * plaintext) % private_key[0]; 
    } 
    return ciphertext; 
} 
 
int decryption(int public_key[], int ciphertext) { 
    int plaintext = 1; 
    ciphertext = ciphertext % public_key[0]; 
    while (public_key[1] > 0) { 
        if (public_key[1] % 2 == 1) { 
            plaintext = (plaintext * ciphertext) % public_key[0]; 
        } 
        public_key[1] = public_key[1] >> 1; 
        ciphertext = (ciphertext * ciphertext) % public_key[0]; 
    } 
    return plaintext; 
}
int main() { 
    int private_key[2]; 
    int public_key[2]; 
    int p, q, plaintext; 
 
    printf("Enter two prime numbers (p and q): "); 
    scanf("%d %d", &p, &q); 
 
    key_generation(p, q, public_key, private_key); 
 
    printf("Enter the plaintext: "); 
    scanf("%d", &plaintext); 
 
    int c = encryption(private_key, plaintext); 
    int p_decrypted = decryption(public_key, c); 
 
    printf("Plain Text: %d\n", plaintext); 
    printf("Encrypted: %d\n", c); 
    printf("Decrypted: %d\n", p_decrypted); 
 
    return 0; 
} 