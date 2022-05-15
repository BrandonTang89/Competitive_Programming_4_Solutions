'''
Kattis - runningsteps
This is presented as a paths on DAG question.. but im legit mega lazy to do that when it is obviously solvable
with elementary mathematics. This can be made more efficient with cached recurrence relation for comb...

Time: O(n), Mem: O(n) assuming that comb is more or less O(1) for small values of n
'''
import operator as op
from functools import reduce, lru_cache

'''
def comb(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom 
'''

@lru_cache(maxsize=None)
def comb(n, r):
    if (r == 0 or r == n):
        return 1
    return (comb(n-1, r-1) + comb(n-1, r))

tc = int(input())
for t_num in range(tc):
    n = int(input().split()[1])
    x = n // 2 

    if (x%2): #odd case
        z = 1
    else:
        z = 0
    
    y = x//2
    ans = 0
    while z <= y:
        ans += comb(y+z, y)**2
        y -= 1
        z += 2
    
    print(t_num+1, ans)