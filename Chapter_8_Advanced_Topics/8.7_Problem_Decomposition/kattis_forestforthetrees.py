'''
Kattis - forestforthetrees
Math. Clearly the only trees to consider are trees of the kind (kp, kq) where k is the gcd of (xb, yb). 
To see which trees have been cut down, observe that (x1/p <= k <= x2/p) and (y1/q <= k <= y2/q) must hold
for (kp, kq) to be cut down.
Now we just consider the different cases (slightly tedious) and output the answer.

Time: O(1), Space: O(1)
'''
xb, yb = map(int, input().split())
x1, y1, x2, y2 = map(int, input().split())

from math import gcd
bk = gcd(xb, yb)
if bk == 1:
    print("Yes")
    exit()
p, q = xb//bk, yb//bk

xleft = (x1-1)//p + 1
xright = x2//p

yleft = (y1-1)//q + 1
yright = y2//q

# maintain xleft <= yleft
if xleft > yleft:
    xleft, yleft = yleft, xleft
    xright, yright = yright, xright
    
if (xright < yleft or xleft > xright or yleft > yright):
    print("No")
    print(p, q)
    exit()
    
if yleft >= 2:
    print ("No")
    print(p, q)
    exit()

rightEnd = min(xright, yright)
if rightEnd + 1 < bk:
    print("No")
    print(p*(rightEnd+1), q*(rightEnd+1))
    exit()

print("Yes")