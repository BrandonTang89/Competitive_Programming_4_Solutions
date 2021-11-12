''' Kattis - primes2
Luckily this didn't TLE. It is much easier to do the random adhoc stuff like attempting
to convert the string to binary, octal, hex, etc in python rather than C++. Also, simplifying
the fraction is easier with the standard library.

Time: O(1060000 log log 1060000), Space: O(1060000)
'''

from sys import stdin
from fractions import Fraction

_sieve_size = 0
bs = []
primes = []


def sieve(upperbound=1060000): # upper bound > sqrt (16^10) which is the largest possible value interpreted
    global _sieve_size, bs, primes

    _sieve_size = upperbound+1
    bs = [True] * 10000010
    bs[0] = bs[1] = False
    for i in range(2, _sieve_size):
        if bs[i]:
            for j in range(i*i, _sieve_size, i):
                bs[j] = False
            primes.append(i)


def isPrime(N):
    global _sieve_size, primes
    if N <= _sieve_size:
        return bs[N]
    for p in primes:
        if p * p > N:
            break
        if N % p == 0:
            return False
    return True


sieve()

tc = int(stdin.readline())
for _ in range(tc):
    n = stdin.readline()
    denom = 0
    numer = 0

    try:
        x = int(n)
        denom += 1
        if (isPrime(x)):
            numer += 1

    except:
        #print("x not a deci")
        pass
    
    try:
        x = int(n, 2)
        denom += 1
        if (isPrime(x)):
            numer += 1

    except:
        #print("x not a bin")
        pass
      
    try:
        x = int(n, 16)
        denom += 1
        if (isPrime(x)):
            numer += 1

    except:
        #print("x not a hex")
        pass
      
    try:
        x = int(n, 8)
        denom += 1
        if (isPrime(x)):
            numer += 1

    except:
        #print("x not a oct")
        pass
      
    f = Fraction(numer, denom)
    if (f == Fraction(0)):
      print("0/1")
    elif (f == Fraction(1)):
      print("1/1")
    else:
      print(f)
