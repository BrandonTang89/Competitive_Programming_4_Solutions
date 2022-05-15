'''
Kattis - multigram
Relatively simple problem, for each divisor of the length of the number, we check if that length
can be a length of the root.

Time: O(sqrt(n) + num_factors * n), Space: O(n)
'''
import sys
from math import sqrt, floor
def getfactors(n):
    factors = []
    for i in range(1,int(sqrt(n)) + 1):
        if (n % i == 0):
            factors.append(i)
            factors.append(n // i)
    if (floor(sqrt(n)) * floor(sqrt(n)) == n):
        factors.pop()
    
    factors.sort()
    return factors

s = input()
factors = getfactors(len(s))
from collections import Counter
for f in factors:
    t = s # copy of string
    root = Counter(s[:f])
    t = t[f:]
    
    can_be_root = True
    while len(t) > 0:
        test = Counter(t[:f])
        if test != root:
            can_be_root = False
            break
        t = t[f:]
    
    if (can_be_root and f != len(s)):
        print(s[:f])
        sys.exit()
    elif (f == len(s)):
        print(-1)
        sys.exit()