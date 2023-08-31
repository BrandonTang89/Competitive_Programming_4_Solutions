'''
Kattis - doodling
95% Observation and math...
First we notice that it will take lcm(2*(w-1), 2*(h-1)) time for the trace to return to the starting point,
but half of the time is spent retracing backwards so in reality it is lcm(w-1, h-1) time to finish the
trace. The real issue is how to deal with the intersections. 

What we notice is that when w-1 and h-1 are coprime, then half of all squares will be coloured. 
Also we notice that when w-1 and h-1 are not coprime, it is an "enlarged" version of the coprime
case, i.e. sum of the number of intersection squares and border squares is the same. So after 
finding the time to finish the trace, we subtract the number squares in the coprime case and add
back the border squares. Then just clean up any off by 1 errors and we are done...

Time: O(log (max(h, w))), Space: O(1)
'''
from math import gcd
def lcm(a, b): return a * b // gcd(a, b)


tc = int(input())
for _ in range(tc):
    x, y = map(int, input().split())
    w, h = min(x, y), max(x, y)

    d = lcm(w-1, h-1) # length of trace, excluding the first square
    g = gcd(w-1, h-1)
    lateralMovements = d // (w-1)
    verticalMovements = d // (h-1) # lateral + vertical movements = number of border squares

    smallw, smallh = (w-1) // g + 1, (h-1) // g + 1 # smaller coprime case
    squares = d + 1 + lateralMovements + verticalMovements - smallh*smallw//2
    # +1 to add back the first square of the trace
    print(squares)