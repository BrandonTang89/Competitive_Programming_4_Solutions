'''
Kattis - hypercube
Simple recursive formula to find the index of the binary string in the graycode.

Time: O(n), Space: O(1)
'''
n, a, b = input().split()
n = int(n)


def dist(n: int, s: str):
    if (n == 0):
        return 0
    if (s[0] == '0'):
        return dist(n - 1, s[1:])
    if (s[0] == '1'):
        return 2 ** n - dist(n - 1, s[1:]) - 1

    assert (False)


print(dist(n, b) - dist(n, a) - 1)
