'''
Kattis - espressobucks
Relatively easy constructive problem. We just try to add as many shops as possible, ie whenever we can add, we just
add.

Time: O(hw), Space: O(hw)
'''
h, w = map(int, input().split())
grid = [list(input()) for _ in range(h)]

dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

for r in range(h):
    for c in range(w):
        if grid[r][c] == '#':
            continue
        canput = True
        for d in range(4):
            nr = r + dr[d]
            nc = c + dc[d]
            
            if 0 <= nr < h and 0 <= nc < w:
                if grid[nr][nc] == 'E':
                    canput = False
                    break
        if canput:
            grid[r][c] = 'E'


for r in range(h):
    for c in range(w):
        print(grid[r][c], end='')
    print()      