'''
Kattis - beehouseperimeter
Similar to the other question kattis_honeyheist. However, this time we have to do multi source
BFS from "outside alice's house". But how do we know where on earth is outside the house?
Well... we can just extend the grid in all 4 directions by 1 extra row/column. This will definitely
be outside of the grid and thus outside of the house. From here, we just BFS from all the added points
and count the number of walls we run into! 

Time: O(r^2), Space: O(r^2)
'''
from pprint import pprint
r, k = map(int, input().split())
alice_house = list(map(int, input().split()))

grid = [[-2] * (2*r-1) for _ in range(2*r-1)]
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

for alice in alice_house:
    i, j = m[alice]
    grid[i][j] = -1

# increase grid size by 1
for row in grid:
    row.append(0);
    row.insert(0, 0)
grid.append([0] * (2*r+1))
grid.insert(0, [0] * (2*r+1))

q = []
dc = [-1, -1, 0, 1, 1, 0]
dr = [0, -1, -1, 0, 1, 1]

for i in range(2*r+1):
    q.append((i, 0))
    q.append((i, 2*r))
    q.append((0, i))
    q.append((2*r, i))
q = list(set(q)) # removes some duplicates

peri = 0
while q:
    i, j = q.pop(0)
    for k in range(6):
        ni = i + dr[k]
        nj = j + dc[k]
        if ni < 0 or nj < 0 or ni >= 2*r+1 or nj >= 2*r+1:
            continue
        if grid[ni][nj] == -1:
            # print(ni, nj, " - ", i, j)
            peri+=1
            continue
        if grid[ni][nj] == -2:
            grid[ni][nj] = grid[i][j] + 1
            q.append((ni, nj))

# pprint(grid)

print(peri)
