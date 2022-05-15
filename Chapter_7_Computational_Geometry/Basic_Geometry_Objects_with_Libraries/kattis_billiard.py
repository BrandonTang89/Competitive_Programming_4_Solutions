'''
Kattis - billiard
Another high school type math problem. Note that the x and y axis are perpendicular and thus
we can deal with the horizontal and vertical components separately. Assume the ball only
has horizontal velocity, then we compute the horizontal speed needed to hit the wall m
times and then go back to the center within the time. Same thing for the vertical component.
Then we combine the 2 components and get a combined velocity.

Time: O(1), Space: O(1)
'''
from math import atan, pi
def radtodeg(rad):
    return rad * (180 / pi)
while 1:
    a, b, s, m, n = map(int, input().split())
    if a == 0 and b == 0 and s == 0 and m == 0 and n == 0: break
    vx = a*m/s
    vy = b*n/s
    
    theta = atan(vy/vx)
    v = (vx**2 + vy**2)**0.5
    theta = round(radtodeg(theta), 2)
    v = round(v, 2)
    theta = "{:.2f}".format(theta)
    v = "{:.2f}".format(v)
    print(theta, v)