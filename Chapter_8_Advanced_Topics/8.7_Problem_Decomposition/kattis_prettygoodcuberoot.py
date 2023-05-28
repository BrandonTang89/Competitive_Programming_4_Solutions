'''
Kattis - prettygoodcuberoot
We just do a classic binary search. Need some big integers for this.

Time: O(log 1e500), Mem: O(1)
'''
from math import ceil 
from sys import stdin

for line in stdin:
    x = int(line)
    
    l = 1
    r = x
    
    # find the largest cube <= x
    while l < r:
        mid = (l+r+1)//2
        if mid**3 <= x:
            l = mid
        else:
            r = mid-1
    
    x1 = l
    x2 = x1+1
    
    e1 = abs(x1**3-x)
    e2 = abs(x2**3-x)
    
    if e1 < e2:
        print(x1)
    else:
        print(x2)
        