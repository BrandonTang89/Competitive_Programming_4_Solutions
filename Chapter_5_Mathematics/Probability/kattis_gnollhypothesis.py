'''
Kattis - gnollhypothesis
Decent probability problem. The idea is we count the effective spawn rate of each mob one at a time.
For each mob, we count all the situtations where the last m mobs before it (exclusive) are not
part of the spawn pool (wrapping around if needed) all at once. Just read the code, not too hard
to understand actually. Each case will look like: TAKEN, NOT TAKEN, NOT TAKEN, ..., NOT TAKEN, 
TAKEN (mob i).

We need to note the edge case where k = 1 so each pool is just 1 mob with 100% spawn rate. Since
each mob has equal chance to be the sole mob, all spawn rates are the same (100%/n).

We use the arr = arr + arr trick to deal with wrap around issues.

Time: O(nk), Space: O(nk)
'''
from functools import lru_cache
n, k = map(int, input().split())
arr = list(map(float, input().split()))
arr = arr + arr


@lru_cache(maxsize=None)
def comb(n, r):
    if (r == 0 or r == n):
        return 1
        if (n < r):
            return 0
    return (comb(n-1, r-1) + comb(n-1, r))


if k == 1:
    for i in range(0, n):
        print(100/n, end=" ")
    exit()

total = 0
for i in range(0, n):
    cur = 0
    ans = 0
    for m in range(0, n-k+1):
        cur += arr[i+n-m]
        ans += cur * comb(n-m-2, k-2) / comb(n, k)
        assert (i+n-m >= 0)

    print(ans, end=" ")
    total += ans

assert (abs(total - 100) < 0.00001)
