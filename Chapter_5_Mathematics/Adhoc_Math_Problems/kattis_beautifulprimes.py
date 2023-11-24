'''
Kattis - beautifulprimes
We are trying to get a list of primes p1, p2, ..., pn such that floor(log10(p1 * p2 * ... * pn)) + 1 = n
This means that floor(log10 p1 + log10 p2 + ... + log10 pn) = n - 1
We observe that roughly log10 pi should be around 1 for each pi but the closest primes we have to 10 are 11 and 7.
As such, we keep track of the running difference between the sum we would like i.e. we should try to get 
log10 p1 + log10 p2 + ... + log10 pn = n - 0.5 and the actual sum we have. If our sum is too big, we add a 7
which has log10 7 < 1 and if our sum is too small, we add a 11 which has log10 11 > 1.
We start off at diff = 0.5 since initially we should have a running sum of (0-0.5) = -0.5 but we have a sum of 0.

Time: O(n), Space: O(1)
'''
from math import log10
l7 = log10(7)
l11 = log10(11)
for _ in range(int(input())):
    n = int(input())
    
    diff = 0.5 # too big
    for i in range(n):
        if diff > 0:
            print(7, end=' ')
            diff += l7 - 1
        else:
            print(11, end=' ')
            diff += l11 - 1
    print()