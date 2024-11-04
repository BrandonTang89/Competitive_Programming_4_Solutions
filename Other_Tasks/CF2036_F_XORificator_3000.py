t = int(input())
from math import log2

for _ in range(t):
    l, r, i, k = map(int, input().split())

    def prefix(x): # XOR of 1..x
        ans = 0
        for j in range(int(log2(x + 2)) + 1):
            if j == 0:
                if x % 4 == 1 or x % 4 == 2:
                    ans = 1
                else:
                    ans = 0
                continue

            if (x >> j) % 2 == 1:
                # one block
                numOnes = x % (1 << j) + 1
                if numOnes % 2 == 1:
                    ans |= 1 << j
        return ans

    def xorUpto(x):  # XOR of all numbers up to x that are k mod 2^i
        y = x // (1 << i)
        if x % (1 << i) >= k:
            y += 1

        return (prefix(y - 1) << i) + (k if y % 2 == 1 else 0)

    print(prefix(r) ^ prefix(l - 1) ^ xorUpto(r) ^ xorUpto(l - 1))