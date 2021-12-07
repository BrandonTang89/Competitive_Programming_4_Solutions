'''
Kattis - rings2
Essentially a multi-source flood fill BFS with output formatting. Note that apart from the empty
cells as sources, we also need to use the edge T cells as sources, but with distance of 1 already.

My first time using the heapq module, seems less flexible than C++ priority_queue but works here.

Time: O(hw), Space: O(hw)
'''
import heapq
h, w = map(int, input().split())
grid = [[""] for _ in range(h)]
dist = [[-1] * w for _ in range(h)]

for r in range(h):
    grid[r] = list(input())

dr = [0, 1, 0, -1]
dc = [1, 0, -1, 0]

pq = []
for r in range(h):
    for c in range(w):
        if grid[r][c] == '.':
            dist[r][c] = 0
            pq.append((0, r, c))
            
for r in range(h):
    if (grid[r][0] == 'T'):
        dist[r][0] = 1
        pq.append((1, r, 0))
    if (grid[r][w-1] == 'T'):
        dist[r][w-1] = 1
        pq.append((1, r, w-1))

for c in range(1,w-1):
    if (grid[0][c] == 'T'):
        dist[0][c] = 1
        pq.append((1, 0, c))
    if (grid[h-1][c] == 'T'):
        dist[h-1][c] = 1
        pq.append((1, h-1, c))
        
heapq.heapify(pq)  # min heap

max_dist = max(max(dist))
while (pq):
    (d, r, c) = heapq.heappop(pq)
    max_dist = max(max_dist, d)
    for i in range(4):
        nr = r + dr[i]
        nc = c + dc[i]
        if (nc < 0 or nc >= w or nr < 0 or nr >= h):
            continue
        if (dist[nr][nc] == -1):
            heapq.heappush(pq, (d + 1, nr, nc))
            dist[nr][nc] = d + 1

if (max_dist >= 10):
    for r in range(h):
        for c in range(w):
            if dist[r][c] == 0:
                print("...", end="")
            elif dist[r][c] < 10:
                print(".." + str(dist[r][c]), end="")
            else: # max is 50
                print("." + str(dist[r][c]), end="")
        print()
else:
    for r in range(h):
        for c in range(w):
            if dist[r][c] == 0:
                print("..", end="")
            elif dist[r][c] < 10:
                print("." + str(dist[r][c]), end="")
        print()