'''
Kattis - plot
this is one of those 90% math, 10% code problems. The short version of the explanation is as such:

let t_i(x) be the value of t_i at the xth iteration of the loop in the task pseudo code
t_i(x+1) = t_i(x) + t_i+1(x) [based on the task description]
t_i+1(x) = t_i(x+1) - t_i(x) [manipulate above]

Now, we note that t_i(0) = Ci. t_0 = P.
So t_1(0) = t_0(1) - t_0(0) = P(1) - P(0)
   t_1(1) = t_0(2) - t_0(2) = P(2) - P(1)

   t_2(0) = t_1(1) - t_1(0) = P(2) - 2P(1) + P(0)

Repeatedly applying the rules above... we note the general pattern for t_i(0)
    t_i(0) = ((-1)**0 * iC0 * P(i)) + ((-1)**1 * iC1 * P(i+1)) + ... + ((-1)**i * iCi * P(i+i))

We just calculate this using our n choose k function and a function to compute P(i).

Time: O(n^3), can be O(n^2) just by memorising values of P(i)
Space: O(n)
'''
import operator as op
from functools import reduce
def comb(n, r): # n choose r
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom

a = list(map(int, input().split())) # n, an, a(n-1), ..., a0
n = a[0]
a.pop(0)
a.reverse() # a0, a1, ..., an

def compute_poly(x):
    global a
    y = 0
    for i in range(n+1):
        y += a[i] * x**i
    return y

for i in range(n+1):
    t = 0
    for j in range(i+1):
        t += (-1)**j * comb(i, j) * compute_poly(i-j)

    print(t, end=' ')