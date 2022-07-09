'''Kattis - teacherevaluation
Greedily fake scores of 100 until the average is p. Check if amt == 0 or p == 100 to avoid division by 0.

Time: O(1), Space: O(1)'''
n, p = map(int, input().split())
cur = sum(map(int, input().split()))
amt = p*n - cur

from math import ceil
if (amt == 0): 
    print(0)
    exit()

if (p == 100):
    print("impossible")
    exit()

ans = ceil(amt/(100-p))
print(ans)