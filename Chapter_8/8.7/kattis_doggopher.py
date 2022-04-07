'''Kattis - doggopher
An easy complete search question. The most difficult part is just formatting honestly.

Time: O(n), Space: O(n)
'''
from sys import stdin
xg, yg, xd, yd = map(float, stdin.readline().split())

holes = [map(float, line.split()) for line in stdin.readlines()]
#print(holes)

def dist(x1, y1, x2, y2): return ((x1-x2)**2 + (y1-y2)**2)**0.5
for (x, y) in holes:
    if (dist(x, y, xg, yg)*2 < dist(x, y, xd, yd)):
        print("The gopher can escape through the hole at (" + "{0:.3f}".format(x) + ","  + "{0:.3f}".format(y) + ").")
        exit()

print("The gopher cannot escape.")