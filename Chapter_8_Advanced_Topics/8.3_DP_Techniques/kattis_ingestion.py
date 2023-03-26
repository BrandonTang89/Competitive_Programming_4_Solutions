# Kattis - ingestion
# Relatively simple DP. We should precompute the amounts of food that are edible.
# Let dp(i, amt, k) be the amount of food we can consume assuming the next food is v[i],
# amts[amt] is how much food we can consume this hour, and k = 1 if we didn't eat last hour
# and 0 otherwise.
# The recurrences are quite obvious.
# Time: O(n^2), Space: O(n)
from functools import lru_cache
n, m = map(int, input().split())
v = list(map(int, input().split()))
amts = [m]
for i in range(n+1):
    amts.append(amts[-1]*2//3)


@lru_cache(maxsize=None)
def dp(i, amt, k):
    if (i == n):
        return 0

    if (k == 0):
        return max(dp(i+1, amt-1, 1), min(v[i], amts[amt]) + dp(i+1, amt+1, 0))

    if (k == 1):
        return max(dp(i+1, 0, 1), min(v[i], amts[amt]) + dp(i+1, amt+1, 0))


print(dp(0, 0, 1))
