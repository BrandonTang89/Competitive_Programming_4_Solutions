'''
Kattis - sjecista
Notice that there exist a bijection between the set of intersections of a diagonals and the
set of selecting 4 points from the polygon. This is because for any choice of 4 points, there
will be exactly 1 diagonal intersection. Thus we just print (n choose 4).

Time: O(n), Space: O(1)
'''
import operator as op
from functools import reduce
def comb(n, r): # n choose r
    if (r > n): return 0
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom

print(comb(int(input()), 4))