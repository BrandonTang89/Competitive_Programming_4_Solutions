'''
Kattis - chineseremainder
A basic chinese remainder problem, but with big integer so we re-implement the functions in
Python 3.

Time: O(log (nm)), Space: O(1)'''
# Given ax + by = GCD(a, b) return {GCD, x, y}
def extEuclid(a: int, b: int): 
    xx = y = 0
    yy = x = 1
    while b:  # repeats until b == 0
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - q * xx
        y, yy = yy, y - q * yy
    return a, x, y  # returns gcd(a, b)

# Computes the Modulo Multiplicative Inverse of a mod n
def modInverse(a: int, n: int): # returns modular inverse of a mod n
    _, x, _ = extEuclid(a, n)
    return x%n

from operator import mul
from functools import reduce
def crt(r: list, m: list):
    # m_t = m_0*m_1*...*m_{n-1}
    mt = reduce(mul, m, 1)
    x = 0
    for i in range(len(m)):
        a = r[i] * modInverse(mt // m[i], m[i]) % m[i]
        x = (x + a * (mt // m[i])) % mt
    return x

num_tc = int(input())
for _ in range(num_tc):
    a, ni, b, mi = map(int, input().split())
    r = [a, b]
    m = [ni, mi]
    print(crt(r, m), ni*mi)