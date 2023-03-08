'''
Kattis - findpoly
We convert the line segments into a graph (where every endpoint is a vertex and the line segments are edges).
Then we count the number of connected components and the number of connected components that are cycles.

Time: O(n), Mem: O(n) # where n is the number of line segments
'''
import sys

lines = []
unique_pts = set()
for line in sys.stdin:
    for s in line.split(';')[:-1]:
        pt1, pt2 = s.split("),(")
        x1, y1 = pt1[1:].split(',')
        x2, y2 = pt2[:-1].split(',')
        lines.append(((int(x1), int(y1)), (int(x2), int(y2))))
        unique_pts.add((int(x1), int(y1)))
        unique_pts.add((int(x2), int(y2)))
        
pts_to_index = {}
for i, pt in enumerate(unique_pts):
    pts_to_index[pt] = i

adjlist = [[] for i in range(len(unique_pts))]
for ((x1, y1), (x2, y2)) in lines:
    i1 = pts_to_index[(x1, y1)]
    i2 = pts_to_index[(x2, y2)]
    adjlist[i1].append(i2)
    adjlist[i2].append(i1)

visited = [False for i in range(len(unique_pts))]
iscycle = True
def dfs(u):
    visited[u] = True
    global iscycle
    if len(adjlist[u]) != 2:
        iscycle = False
    for v in adjlist[u]:
        if not visited[v]:
            dfs(v)
            
cc = 0
cycles = 0
for i in range(len(unique_pts)):
    if visited[i]:
        continue
    iscycle = True
    dfs(i)
    
    cc += 1
    if iscycle:
        cycles += 1
    
print(cc, cycles)