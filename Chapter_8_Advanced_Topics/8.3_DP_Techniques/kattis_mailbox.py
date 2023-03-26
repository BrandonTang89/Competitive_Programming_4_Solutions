'''
Kattis - mailbox
We let dp(k, l, r) be the minimum cost with k mailboxes, and we need to test [l, r).
We try all possible number of firecrackers within l, r and take the best position test.
The recurrences are not exactly trivial to get right but the sample testcase is good
to debug.

Time: O(k*m^3)
''' 
from functools import lru_cache
tc = int(input())


@lru_cache(maxsize=None)
def dp(k, l, r):  # could be [l, r) or not possible

    if (k == 1):
        return (sum(range(l, r)))
    if (l == r):
        return 0
    if (l + 1 == r):
        return l
    assert (l < r)

    ans = int(1e9)
    for i in range(l, r):
        ans = min(ans, i + max(dp(k-1, l, i), dp(k, i+1, r)))
    return ans


for _ in range(tc):
    k, m = map(int, input().split())
    print(dp(k, 1, m+1))
