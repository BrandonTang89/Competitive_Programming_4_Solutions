'''
Kattis - namethatpermutation
A classic problem. There exist a faster solution with the use of an order statistic tree to select
and remove the kth smallest element in O(log(n)) time rather than O(n) iteration through a set. However,
that is overkill for this question since n <= 50.

Time: O(n^2), Space: O(n)
'''
from sys import stdin
factorial = [1]
for i in range(1, 51):
    factorial.append(i * factorial[-1])
    
for line in stdin:
    n, k = map(int, line.split())
    s = set(range(1, n + 1))
    
    while (n > 0):
        # print(s)
        pos = k // factorial[n-1]
        k = k % factorial[n-1]
        for i,e in enumerate(s):
            # print(i, pos)
            if (i == pos):
                print(e, end=' ')
                s.remove(e)
                break
            
        n-=1
    print()