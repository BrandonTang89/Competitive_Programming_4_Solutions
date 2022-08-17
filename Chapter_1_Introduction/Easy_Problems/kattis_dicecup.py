'''
Kattis - dicecup
We can just do the obvious strategy.

Time: O(nm), Space: O(n+m)'''
n, m = map(int, input().split())
d = {}
maxi = 0
for i in range(1, n+1):
    for j in range(1, m+1):
        if i+j not in d:
            d[i+j] = 1
        else:
            d[i+j] += 1
        
        maxi = max(maxi, d[i+j])

arr = [s if d[s] == maxi else 0 for s in d]
arr.sort()
for i in arr:
    if i != 0:
        print(i)