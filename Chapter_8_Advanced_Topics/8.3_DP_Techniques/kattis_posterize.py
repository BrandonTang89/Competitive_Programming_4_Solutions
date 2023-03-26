'''
Kattis - posterize
Debugging: Ensure your INF is 1e18 rather than 1e9...

Relatively alright DP (though there is sort of a nested DP). Let dp(k, prev) be the minimum cost of
all the red values with intensity > prev assuming that we can select k more points. We just try selecting
all possible intensities from [prev+1, 256) and take the best one. 

When doing the testing, we go along (prev, i) and sum the min squared error. Notice that this work
is repeated and can thus be subject to DP as well. This is extracted out as the range_sum function
that sums the errors within that range, allowing us to drop the time complexity from O(256^4) to O(256^3).

Time: O(256^3), Space: O(256^2)
'''
from functools import lru_cache

d, k = map(int, input().split())
v = [0 for _ in range(256)]


@lru_cache(maxsize=None)
def range_sum(prev, i):  # O(256^3) overall
    prevp1 = max(prev+1, 0)
    c = 0
    for x in range(prevp1, i):
        c += v[x]*min((x-prev)**2, (x-i)**2)
    return c


@lru_cache(maxsize=None)
def dp(k, prev):  # O(256^3) overall
    if prev == 255:
        return 0

    prevp1 = max(prev+1, 0)
    if k == 0:
        assert (prev >= 0)
        ans = 0
        for x in range(prevp1, 256):
            ans += v[x]*(x-prev)**2
        return ans

    ans = int(1e18)
    for i in range(prevp1, 256):
        c = range_sum(prev, i)
        c += dp(k-1, i)
        ans = min(ans, c)

    return ans


for i in range(d):
    x, n = map(int, input().split())
    v[x] = n

print(dp(k, -1000))
