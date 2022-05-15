'''
Kattis - heritage
Here I decided to use the actual substring as the DP state, then we do something similar to the
recursive parser problems but with DP since there is a high incidence of overlapping subproblems.

Time: O(32**2 * 32), Space: O(32**2)
'''
n, s = input().split()
n = int(n)

mod = 10**9 + 7
d = {}
for _ in range(n):
    x, meanings = input().split()
    d[x] = int(meanings)

from functools import lru_cache
@lru_cache(maxsize=None)
def dp(subs):
    ans = 0
    if (subs in d):
        ans += d[subs]
    for i in range(1,len(subs)+1):
        if (subs[:i] in d):
            ans += d[subs[:i]] * dp(subs[i:])
            ans %= mod

    ans %= mod
    return ans

print(dp(s))