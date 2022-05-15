'''
Kattis - anagramcounting
Simply count number of permutations of the input string, account for repeated characters.

Time: O(len(x)), Space: O(len(x))
'''
from sys import stdin
from collections import Counter

fact = [1] # fact(0) = 1
for i in range(1, 101):
    fact.append(fact[i-1] * i)
    
for line in stdin:
    x = line.strip()
    w = Counter(x)
    
    ans = fact[len(x)]
    for (k, v) in w.items():
        ans //= fact[v]

    print(ans)