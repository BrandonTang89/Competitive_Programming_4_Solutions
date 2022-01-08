'''
Kattis - mountainbiking
Bad question in my opinion. They are basically treating the mountain like a flat line with
differing acclerations. But in reality, once the bike moves from 1 segment to another, the
velocity parallel to the slope changes since the slope changes angles! For example,
if we have a nearly vertical slope into a horizontal slope, the velocity going into the
horizontal slope is near 0 since most of the previous velocity is perpendicular to the
horizontal. Also the question doesn't care about the case where the normal force
is 0 and the bike is basically flying... But okay wtv.

just use v^2 = u^2 + 2as a few times.

Time: O(n^2), Space: O(1)
'''
n, g = input().split()
n = int(n)
g = float(g)

from math import cos, pi
slopes = []
for i in range(n):
    s, theta = map(int, input().split())
    theta = theta * (2 * pi / 360)
    slopes.append((s, theta))
    
for i in range(n):
    cur_velocity = 0
    for j in range(i, n):
        s, theta = slopes[j]
        cur_velocity = (cur_velocity**2 + 2*g*cos(theta)*s)**0.5
    
    print(cur_velocity)