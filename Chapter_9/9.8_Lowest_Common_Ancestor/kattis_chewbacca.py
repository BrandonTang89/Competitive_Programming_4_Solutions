'''
Kattis - Chewbacca
Use some pen and paper to figure out the right mathematical steps to solve this problem.
Note that the tree is at most 64 in height (excluding the 1-ary edge case), so we can kinda brute
force the depth function (to avoid unnecessary code complexity).

I tried implementing this in C++ but I suppose the datatype supoprt there is bad so I couldn't AC
initially. Refer to that source code for how I ACed.
Time: O(log(n)^2*q), Space: O(1)
'''
n, k, q = map(int, input().split())
def parent(u):
    x = u // k
    if ((u % k) == 0 or (u % k) == 1): return x
    return x+1

def depth(u):
    if (u == 1): return 0

    t = u*(k-1) + 1
    for d in range(1, 100000):
        if ((pow(k, d+1) >= t) and (pow(k, d) < t)):  return d

    assert(False)

def lca(u, v):
    if (depth(u) > depth(v)): u,v = v,u # v is deeper
    while (depth(u) < depth(v)):
        v = parent(v)
    while (u != v):
        u = parent(u)
        v = parent(v)
    return u

for _ in range(q):
    u,v = map(int, input().split())

    if (k != 1):
        print(depth(u) + depth(v) - 2*depth(lca(u, v)))
    else: 
        print(abs(u - v))