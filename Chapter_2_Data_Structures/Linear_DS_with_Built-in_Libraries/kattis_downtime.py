'''
Kattis - downtime
Use the same idea as the range update point query fenwick tree. Note that we don't need to use
a RURQ segment tree since we only query once at the end of the input.

Time: O(n), Space: O(1)
'''
n, k = map(int, input().split())
arr = [0]*101001

for i in range(n):
    x = int(input())
    arr[x] += 1
    arr[x + 1000] -= 1

maxi = 0
cur = 0
for i in range(101001):
    cur += arr[i]
    maxi = max(maxi, cur)

from math import ceil
print(ceil(maxi/k))