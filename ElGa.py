import random
import sympy

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    else:
        return x % m

def generate_keypair(p, g, x):
    y = pow(g, x, p)
    return (y, g, p), x

def encrypt(public_key, plaintext):
    y, g, p = public_key
    k = random.randint(1, p - 2) 
    c1 = pow(g, k, p)
    c2 = (plaintext * pow(y, k, p)) % p
    return c1, c2

def decrypt(private_key, public_key, ciphertext):
    c1, c2 = ciphertext
    y, g, p = public_key
    x = private_key
    s = pow(c1,- x, p)
    plaintext = (c2 * s) % p
    return plaintext


p = sympy.randprime(50, 100)
g = 5   
x = random.randint(1, p - 2) 

public_key, private_key = generate_keypair(p, g, x)

plaintext = 9
ciphertext = encrypt(public_key, plaintext)
print("Encrypted:", ciphertext)

decrypted_text = decrypt(private_key, public_key, ciphertext)
print("Decrypted:", decrypted_text)