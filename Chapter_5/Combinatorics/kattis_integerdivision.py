'''
Kattis - integerdivision
Get the input, divide by divisor, count number of each value, for each frequency, add (frequency)C(2)

Time: O(n), Space: O(n)
'''

from functools import lru_cache
from collections import Counter
@lru_cache(maxsize=None)
def choose2(n): return n*(n-1)//2

n, d = map(int, input().split())
v = list(map(int, input().split()))
v = Counter(map(lambda x: x//d, v))

ans = 0
for (k, v) in v.items():
    # print(k, v)
    ans += choose2(v)
print(ans)

