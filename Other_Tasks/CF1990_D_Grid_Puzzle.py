from functools import lru_cache
from sys import setrecursionlimit

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))

    ans = 0
    state = None
    for u in range(n):
        if arr[u] == 0:
            state = None
            continue
        
        if state is None:
            if arr[u] <= 2:
                ans += 1
                state = 0
            else:
                ans += 1
                state = None
        elif state == 0:
            if arr[u] <= 2:
                state = None
            elif arr[u] <= 4:
                ans += 1
                state = 2
            else:
                ans += 1
                state = None
        elif state == 2:
            if arr[u] <= 4:
                ans += 1
                state = 0
            else:
                ans += 1
                state = None
        else:
            assert False
            
    print(ans)
            