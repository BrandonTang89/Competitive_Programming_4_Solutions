'''
Kattis - candydivision
We are just trying to get all factors of a number in increasing order.

Time: O(num_factors log num_factors + sqrt(n)), Space: O(num_factors)
'''
n = int(input())
from math import sqrt, floor
def getfactors(n):
    factors = []
    for i in range(1,int(sqrt(n)) + 1):
        if (n % i == 0):
            factors.append(i)
            factors.append(n // i)
    if (floor(sqrt(n)) * floor(sqrt(n)) == n):
        factors.pop()
    
    return factors

f = getfactors(n)
f.sort()
for i in f:
    print(i-1, end=' ')