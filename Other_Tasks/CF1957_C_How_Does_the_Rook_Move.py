from functools import lru_cache
import sys

MOD = 10**9 + 7
arr = [1]*(int(3e5 + 10))

for i in range(2, int(3e5 + 10)):
    arr[i] = (arr[i-1] + 2*(i-1)*arr[i-2])%MOD

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    
    used = 0
    for _ in range(k):
        x, y = map(int, input().split())
        if x == y: used += 1
        else: used += 2
        
    print(arr[n-used])
    