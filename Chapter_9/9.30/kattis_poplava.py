'''
Kattis - poplava
Notice that we can achieve the biggest possible sum by putting the largest and second largest as the first and
last respectively, ie n,1,2,3,4,...,n-1. 

Consider the following algorithm to get a subset of {1, 2, 3, ..., n} to sum to an arbitary value k:
    for i = n to i = 1
        if i <= k
            select i
            k = k - i

We will prove that this algorithm will be able to generate all values of k <= n(n+1)/2 by induction.

Assume that this algorithm works for n-1. Now, to construct all values of k > n, we first select n, then
we have some number <= (n)(n-1)/2 and can still select the rest of [1..n-1], by induction, we can form all such k.
If k < n, we can just select k directly. Base case of n=1 is trivial.

Now using this, notice that we can construct the histogram using the same idea, essentially we form an upward staircase
between (n) and (n-1) such that sum (n-1 - i) for each i in the staircase = volume = k. The leftover bars 
are just put as a downward staircase after n-1, adding 0 to the capacity.

Time: O(n), Space: O(n)
'''
n, x = map(int, input().split())
max_cap = (n-2)*(n-1)//2

import sys
if (x > max_cap):
    print(-1)
    sys.exit()


ans = [n]
left_overs = []
for i in range(n-2, 0, -1):
    if (i <= x):
        ans.append(n-1 - i)
        x -= i
    else:
        left_overs.append(n-1 - i)

ans = ans + [n-1] + left_overs[::-1]
ans = [str(i) for i in ans]
print(' '.join(ans))