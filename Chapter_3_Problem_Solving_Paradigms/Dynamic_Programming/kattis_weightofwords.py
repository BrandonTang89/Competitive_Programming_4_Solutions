'''
Kattis - weightofwords
Pretty easy question actually. We could do this without DP... but we can do it with DP.

Time: O(lw), Space: O(lw)'''
from functools import lru_cache
@lru_cache(maxsize=None)

def dp(l: int, w: int):
    if (l == 0):
        return 1 if w == 0 else 0
    if (w == 0): return 0
    
    ans = 0
    for i in range(26):
        ans = max(ans, dp(l-1, w-i-1))
    
    return ans

def get_sol(l: int, w: int):
    if (l == 0): return
    if (w == 0): return
    
    for i in range(26):
        if (dp(l-1, w-i-1) > 0):
            print(chr(ord('a') + i), end='')
            get_sol(l-1, w-i-1)
            break

l, w = map(int, input().split())
if dp(l, w) == 1:
    get_sol(l, w)
else:
    print('impossible')