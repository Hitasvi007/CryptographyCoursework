import random

def generate_random_coefficients(secret, threshold, prime):
    coefficients = [secret] + [random.randint(0, prime - 1) for _ in range(threshold - 1)]
    return coefficients

def evaluate_polynomial(coefficients, x, prime):
    result = 0
    for coefficient in reversed(coefficients):
        result = (result * x + coefficient) % prime
    return result

def generate_shares(secret, threshold, prime, num_shares):
    coefficients = generate_random_coefficients(secret, threshold, prime)
    shares = [(i, evaluate_polynomial(coefficients, i, prime)) for i in range(1, num_shares + 1)]
    return shares

def lagrange_interpolation(shares, prime):
    def interpolate(x):
        result = 0
        for xi, yi in shares:
            numerator = denominator = 1
            for xj, _ in shares:
                if xj != xi:
                    numerator = (numerator * (x - xj)) % prime
                    denominator = (denominator * (xi - xj)) % prime
            result = (result + (yi * numerator * pow(denominator, -1, prime))) % prime
        return result
    return interpolate

def reconstruct_secret(shares, prime):
    interpolate = lagrange_interpolation(shares, prime)
    return interpolate(0)

# Example usage:
secret = 42
threshold = 2
prime = 257  # Should be a prime number greater than the secret
num_shares = 3

shares = generate_shares(secret, threshold, prime, num_shares)
print("Shares:", shares)

reconstructed_secret = reconstruct_secret(shares, prime)
print("Reconstructed Secret:", reconstructed_secret)