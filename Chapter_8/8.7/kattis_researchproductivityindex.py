'''
Kattis - researchproductivityindex
While this consists of complete search, greedy, dp, and math, the most important part is the math.

Firstly, obvserve that if we submit s submissions, we should submit the s best papers... So
the first step is immediately to sort in descending order.

Assume we are given a specific s, we want to get a formula for the expected research index
E(a^(a/s)) = sum( p((a^(a/s))_i) * (a^(a/s))_i )
Since p((a^(a/s))_i) is equal to p(a_i), we can simplify the formula to
E(a^(a/s)) = sum( p(a_i) * (a^(a/s))_i )

Then we need to find p(a_i) given s. We thus define dp(a, s) to be the probability of
a accepted submissions given s submissions. We work out the formulae as seen in the code below.

Now, since we aren't given a specific s, we just complete search for s.

Id say a decently interesting question overall!

Time: O(n^2), Space: O(n^2)
'''
from functools import lru_cache
n = int(input())
p_acc = list(map(float, input().split()))
p_acc = [x/100  for x in p_acc]
p_acc.sort(reverse=True)

@lru_cache(maxsize=None)
def dp(a, s):
    if (a < 0): return 0
    if (a > s): return 0
    if (a == 0 and s == 0): return 1
    return dp(a, s-1) * (1 - p_acc[s-1]) + dp(a-1, s-1) * p_acc[s-1]

def cal_idx(a, s):
    if a == 0: return 0
    return pow(a, a/s)

ans = 0
for s in range(1, n+1):
    e_idx = sum(cal_idx(i, s)*dp(i, s) for i in range(0, s+1))

    ans = max(ans, e_idx)

print(ans)
    