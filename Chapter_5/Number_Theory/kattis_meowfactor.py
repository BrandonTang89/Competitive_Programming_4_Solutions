'''
Kattis - meowfactor
Find largest i such that i**9 | x. Since i is small, we just brute force. Else it would better to
binary search for i, or even better: work with prime factors.

Time: O(n**(1/9)), Space: O(1)
'''

x = int(input())

from math import ceil
ans = 1
for i in range(ceil(x**(1/9)) + 1, 0, -1):
    if (i**9 > x): continue
    if (x % (i**9) == 0):
        ans = i
        break

print(ans)