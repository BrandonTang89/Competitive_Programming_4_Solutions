
from math import log2
t = int(input())
for _ in range(t):
    
    n, k = map(int, input().split())
    if n == 1: 
        print(k)
        continue
    
    x = int(log2(k)) # k = 2^x + r
    # print("x:", x)
    
    q = (1<<(x)) - 1
    h = k - q
    
    print(q, h, end = ' ')
    for _ in range(n-2):
        print(0, end = ' ')
    print()