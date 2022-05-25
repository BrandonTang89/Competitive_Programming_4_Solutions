'''
Kattis - permutationdescent
Rather theoratical problem, just determine the recurrence relation and we are good to go.

Time: O(nv), Space: O(nv)'''
from functools import lru_cache
@lru_cache(maxsize=None)
def pdc(n, v):
    if (v == 0 or v == n-1): return 1
    return ((v+1)*pdc(n-1, v) + (n-v)*pdc(n-1, v-1))%1001113
num_tc = int(input())
for tc in range(1, num_tc+1):
    _, n, v = map(int, input().split())
    print(tc, pdc(n, v))