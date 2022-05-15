'''
Kattis - suspensionbridge
Binary search for a, which a value such that f(a) = 0, ie a is a root of f. Once we have a, we can
directly compute l.

To know the shape of f and the upperbound of a, we use desmos to plot the graph of f(a). Note that
s >= 1 and d <= 1000.

Time: O(100), Space: O(1)
'''
d, s = map(int, input().split())

from math import cosh, sinh
def f(a): return -a + a*cosh(d/(2*a)) - s

# Binary search for a, where f(a) = 0, f is a decreasing function
l = 0
r = 125009
for i in range(100):
    mid = (l+r)/2
    if (f(mid) < 0):
        r = mid
    else:
        l = mid
print(2*l *sinh(d/(2*l)))