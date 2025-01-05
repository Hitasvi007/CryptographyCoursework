import random
import sympy
from Crypto.Hash import SHA256

def is_primitive_root(g, p):
    factors = sympy.factorint(p - 1)
    for factor in factors:
        if pow(g, (p - 1) // factor, p) == 1:
            return False
    return True

def find_primitive_root(p):
    for g in range(2, p):
        if is_primitive_root(g, p):
            return g
    return None

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

def generate_keypair(p, g):
    x = random.randint(1, p - 2)
    y = pow(g, x, p)
    return (y, g, p), x

def sign(private_key, public_key, message):
    x = private_key
    y, g, p = public_key
    hash_value = int.from_bytes(SHA256.new(bytes(str(message), 'utf-8')).digest(), byteorder='big')
    k = random.randint(1, p - 2)
    r = pow(g, k, p)
    k_inv = modinv(k, p - 1)
    s = (k_inv * (hash_value - x * r)) % (p - 1)
    return (r, s)

def verify(public_key, signature, message):
    y, g, p = public_key
    r, s = signature
    if not (0 < r < p and 0 < s < p - 1):
        return False
    w = modinv(s, p - 1)
    u1 = (message * w) % (p - 1)
    u2 = (r * w) % (p - 1)
    v = (pow(g, u1, p) * pow(y, u2, p)) % p
    return v == r

p = sympy.randprime(50, 100)
g = find_primitive_root(p)

print('Prime Number is:', p)
print('Generator is:', g)

keypair, private_key = generate_keypair(p, g)
public_key = keypair  # Use the entire keypair as the public key

message = "Hello, world!"
signature = sign(private_key, public_key, message)
print("Signature:", signature)

verified = verify(public_key, signature, int.from_bytes(SHA256.new(bytes(str(message), 'utf-8')).digest(), byteorder='big'))
print("Verification result:", verified)
