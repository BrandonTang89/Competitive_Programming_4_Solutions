'''
Kattis - flowshop
Observe the pattern. Go row by row, column by column to determine the time the ith swather left the
jth stage (represented by arr[i][j]).

Time: O(n^2), Space: O(n^2)
'''
h, w = map(int, input().split())
g = []
for r in range(h):
    g.append(list(map(int,input().split())))

arr = [[0]*w for _ in range(h)]
arr[0][0] = g[0][0]
for c in range(1,w):
    arr[0][c] = g[0][c] + arr[0][c-1]

for r in range(1,h):
    arr[r][0] = g[r][0] + arr[r-1][0]

print(arr[0][-1], end = ' ')
for r in range(1,h):
    for c in range(1,w):
        arr[r][c] = g[r][c] + max(arr[r-1][c], arr[r][c-1]) 
        # wait for workers to finish the swather above and the process before

    print(arr[r][w-1], end = ' ')