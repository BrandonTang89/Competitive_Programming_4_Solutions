from math import ceil
t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    
    if (n - ceil(n/m) <= k):
        print("NO")
    else: print("YES")