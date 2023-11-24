'''
Kattis - dickandjane
Primary school math question that is non-trivial (for me since im not great at math)
[in the following write up d1, d2, d3 are floats, f1, f2, f3 are floats in [0, 1) and the rest are integers]

First, the the differences if ages be (smallest) yertle <-- d2 = f2 + p --> (middle) puff <-- d1 = f1 + p --> (largest) spot
We also have the following:
    d3 = f3 + y
    d1 + d2 = d3

We let the current age of yertle be k+fc, so the current age of puff is k+p+fc+f2 and the current age of spot is k+p+fc+f3
This means that j+12 = x = floor(k+fc) + floor(k+p+fc+f2) + floor(k+y+fc+f3) = 3k + p + y + floor(fc + f2) + floor(fc + f3)
We can get k as (x-p-y)//3 since 0 <= floor(fc + f2) + floor(fc + f3) <= 2

We can get floor(fc + f2) + floor(fc + f3) = x - 3k - p - y
If this value is 2, it is clear that puff and spot should be k+p+1 and k+y+1 respectively.
Symmetrically, if this value is 0, it is clear that puff and spot should be k+p and k+y respectively.

The other case is where this value is 1.
Now we also note that y-s-p = f1 + f2 - f3 in {0, 1}.
If f1+f2=f3 then f3 > max(f1, f2) >= f2 so floor(fc+f2) < floor(fc+f3) so we must have floor(fc+f2) = 0 and floor(fc+f3) = 1
- this means that puff and spot should be k+p and k+y+1 respectively.
Otherwise, we have f3 < min(f1, f2) <= f2, so floor(fc+f2) > floor(fc+f3) which means that floor(fc+f2) = 1 and floor(fc+f3) = 0
- this means that puff and spot should be k+p+1 and k+y respectively.

Time: O(1), Space: O(1)
'''
from sys import stdin

for line in stdin:
    s,p,y,j = map(int, line.split())
    x = j+12
    k = (x-y-p)//3
    d = x - 3*k-p-y
    
    c = k
    if d == 0:
        a = k+y
        b = k+p
    elif d == 2:
        a = k+y+1
        b = k+p+1
    else:
        if y-s-p == 0:
            b = k+p
            a = k+y+1
        else:
            b = k+p+1
            a = k+y
    
    print(a, b, c)