'''
Kattis - expandingrods
Easy in theory, hard in practise...  This is just about doing pen and paper mathematics then
trying to find a quantity to binary search for. After trying many different ways, the following
works: Binary search for d, then for each d, find r, then check if r is a valid solution.

Note that we have "large" precision errors.. Need to have the special check for no expansion
to AC... :(
    
Time: O(1), Space: O(1)
'''
from math import sin
while (1):
    L, n, C = map(float, input().split())
    if (L < 0 and n < 0 and C < 0):
        break
    if (L == 0 or n*C == 0):
        print("0.000")
        continue
    Lp = (1 + n*C) * L
    target = L
    lo = 0
    hi = L/2
    for i in range(500):
        d = (lo + hi) / 2
        r = (d/2) + (L**2)/(8*d)
        # print("d ", d)
        # print("r", r)
        # print("val", 2*r*sin(Lp/(2*r)))
        # print("target", target)
        
        if (2*r*(sin(Lp/(2*r))) < target):
            hi = d
        else:
            lo = d
    
    print(lo)
    # print("{0:.3f}".format(lo))
