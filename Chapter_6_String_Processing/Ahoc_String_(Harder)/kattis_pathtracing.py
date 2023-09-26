'''
Kattis - pathtracing
Just trace the path on a hashset then offset by the right amount into a grid then print it out.

Time: O(n + hw), Space: O(hw)
'''
visited = set()

from sys import stdin
cur = (0, 0)
visited.add(cur)
for line in stdin.readlines():
    if line == "down\n":
        cur = (cur[0], cur[1] - 1)
    elif line == "up\n":
        cur = (cur[0], cur[1] + 1)
    elif line == "right\n":
        cur = (cur[0] + 1, cur[1])
    else:
        cur = (cur[0] - 1, cur[1])
    
    visited.add(cur)
    
minx = min(map(lambda x: x[0], visited))
maxx = max(map(lambda x: x[0], visited))
miny = min(map(lambda x: x[1], visited))
maxy = max(map(lambda x: x[1], visited))

h = maxy - miny + 3
w = maxx - minx + 3
grid = [[' ' for _ in range(w)] for _ in range(h)]
for c in range(w):
    grid[0][c] = '#'
    grid[-1][c] = '#'
for r in range(h):
    grid[r][0] = '#'
    grid[r][-1] = '#'
    
for (x, y) in visited:
    grid[- (y - miny + 1) -1][x - minx + 1] = '*'

x, y = cur
grid[- (y - miny + 1) -1][x - minx + 1] = 'E'
grid[- (0 - miny + 1) -1][0 - minx + 1] = 'S'
for row in grid:
    print("".join(row))
    
