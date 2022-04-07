import argparse

from math import ceil, sqrt
import math


def bsgs(g, h, p):
    N = ceil(sqrt(p - 1))  # phi(p) is p-1 if p is prime

    # Store hashmap of g^{1...m} (mod p). Baby step.
    tbl = {pow(g, i, p): i for i in range(int(N))}

    # Precompute via Fermat's Little Theorem
    c = pow(g, N * (p - 2), p)

    # Search for an equivalence in the table. Giant step.
    for j in range(N):
        y = (h * pow(c, j, p)) % p
        if y in tbl:
            return j * N + tbl[y]

    # Solution not found
    return None


def main(read_path, write_path):

    with open(read_path, 'r') as f:
        lines = f.readlines()
        A, B, M = [int(v) for v in lines[0].split()]

    result = bsgs(A, B, M)

    with open(write_path, 'w') as f:
        f.write(str(result))


if __name__ == '__main__':


    parser = argparse.ArgumentParser()

    parser.add_argument('read_path', type = str)
    parser.add_argument('write_path', type = str)


    args = parser.parse_args()

    main(args.read_path, args.write_path)

