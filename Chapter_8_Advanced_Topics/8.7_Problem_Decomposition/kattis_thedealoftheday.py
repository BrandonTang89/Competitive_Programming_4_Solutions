'''
Kattis - thedealoftheday
Some easy Math + DP. We let dp(i, num_left) be the number of ways to make an ascending sequence of length num_left using only elements in V[i:].
The base cases are bascially being done (num_left == 0 => 1) or not being able to make a sequence (i == len(v) => 0). The recursive case is
to either use the current element or not use the current element. The answer is dp(0, k).

Time: O(n * k), Mem: O(n * k)
'''
from functools import lru_cache

v = list(map(int, input().split()))
k = int(input())
@lru_cache(maxsize=None)
def dp(i, num_left):
    if num_left == 0: return 1
    if i == len(v): return 0
    return dp(i+1, num_left) + v[i] * dp(i+1, num_left-1)
print(dp(0, k))