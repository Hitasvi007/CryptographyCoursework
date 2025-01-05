def permute(input, permutation):
    return [input[i - 1] for i in permutation if i - 1 < len(input)]


def left_circular_shift(input, shifts):
    return input[shifts:] + input[:shifts]


def generate_subkeys(key):
    P10 = [3, 5, 2, 7, 4, 10, 1, 9, 8, 6]
    P8 = [6, 3, 7, 4, 8, 5, 10, 9]

    key = permute(key, P10)
    key = left_circular_shift(key[:5], 1) + left_circular_shift(key[5:], 1)
    k1 = permute(key, P8)

    key = left_circular_shift(key[:5], 2) + left_circular_shift(key[5:], 2)
    k2 = permute(key, P8)

    return k1, k2


def initial_permutation(input):
    IP = [2, 6, 3, 1, 4, 8, 5, 7]
    return permute(input, IP)


def expand_and_permute(input):
    EP = [4, 1, 2, 3, 2, 3, 4, 1]
    return permute(input, EP)


def substitute(input, s_box):
    row = (input[0] << 1) + input[3]
    col = (input[1] << 1) + input[2]
    value = s_box[row][col]

    return [(value >> 1) & 1, value & 1]


def permutation_p4(input):
    P4 = [2, 4, 3, 1]
    return permute(input[:4], P4)  


def encrypt(plaintext, k1, k2):
    S0 = [
        [1, 0, 3, 2],
        [3, 2, 1, 0],
        [0, 2, 1, 3],
        [3, 1, 3, 2]
    ]
    S1 = [
        [0, 1, 2, 3],
        [2, 0, 1, 3],
        [3, 0, 1, 0],
        [2, 1, 0, 3]
    ]

    plaintext = initial_permutation(plaintext)
    left, right = plaintext[:4], plaintext[4:]

    expanded_right = expand_and_permute(right)
    expanded_right_xor_k1 = [a ^ b for a, b in zip(expanded_right, k1)]

    substituted_right_s0 = substitute(expanded_right_xor_k1[:4], S0)
    substituted_right_s1 = substitute(expanded_right_xor_k1[4:], S1)

    permuted_right_s0 = permutation_p4(substituted_right_s0)
    permuted_right_s1 = permutation_p4(substituted_right_s1)

    left_xor_permuted_s0 = [a ^ b for a, b in zip(left, permuted_right_s0)]
    left_xor_permuted_s1 = [a ^ b for a, b in zip(left_xor_permuted_s0, permuted_right_s1)]

    return right + left_xor_permuted_s1


def find_key(plaintext, ciphertext):
    for key in range(1024):  # Iterate over all possible keys
        key_binary = [int(x) for x in format(key, '010b')]
        k1, k2 = generate_subkeys(key_binary)
        result = encrypt(plaintext, k1, k2)
        if result == ciphertext:
            return key_binary
    return None


plaintexts = [
    [1, 0, 1, 1, 0, 0, 1, 0],
    [1, 0, 1, 0, 1, 0, 0, 0],
]

ciphertexts = [
    [0, 0, 1, 1, 0, 1, 0, 0],
    [1, 1, 1, 1, 0, 0, 1, 0],
]

for i, (plaintext, ciphertext) in enumerate(zip(plaintexts, ciphertexts)):
    print(f"Pair {i + 1}:")
    key = find_key(plaintext, ciphertext)
    if key:
        print(f"Key: {''.join(map(str, key))}")
    else:
        print("Key not found.")
