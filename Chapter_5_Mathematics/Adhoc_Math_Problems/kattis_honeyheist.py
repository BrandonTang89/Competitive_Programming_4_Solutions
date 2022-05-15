'''
Kattis - honeyheist

This is supposed to be relatively easy, but only once you know the right way to convert the 
hexagon grid onto a 2D grid. This kinda brings me back to the good old days of syntax printing
pattern questions. Just refer to the code to see how the conversion is done. Note the recording
of the coordinates of each cell using the dictionary m.

After that, its just basic BFS that even copilot can do almost automatically.

Time: O(r^2), Space: O(r^2)
'''
from pprint import pprint
r, n, a, b, x = map(int, input().split())
walls = list(map(int, input().split()))

grid = [[-1] * (2*r-1) for _ in range(2*r-1)]
num_cells = r*r*r - (r-1)*(r-1)*(r-1)
m = {}

# Build Grid
counter = 1
for i in range(r):
    for j in range(r + i):
        grid[i][j] = -2
        m[counter] = (i, j)
        counter += 1
for i in range(r,2*r-1):
    for j in range(i-r+1, 2*r-1):
        grid[i][j] = -2
        m[counter] = (i, j)
        counter += 1

for wall in walls:
    i, j = m[wall]
    grid[i][j] = -1

# BFS
source = m[a]
grid[source[0]][source[1]] = 0
q = [source]
dc = [-1, -1, 0, 1, 1, 0]
dr = [0, -1, -1, 0, 1, 1]
while q:
    i, j = q.pop(0)
    for k in range(6):
        ni = i + dr[k]
        nj = j + dc[k]
        if ni < 0 or nj < 0 or ni >= 2*r-1 or nj >= 2*r-1:
            continue
        if grid[ni][nj] == -1:
            continue
        if grid[ni][nj] == -2:
            grid[ni][nj] = grid[i][j] + 1
            q.append((ni, nj))

dest = m[b]
if grid[dest[0]][dest[1]] == -2 or grid[dest[0]][dest[1]] > n:
    print("No")
else:
    print(grid[dest[0]][dest[1]])
# pprint(grid)