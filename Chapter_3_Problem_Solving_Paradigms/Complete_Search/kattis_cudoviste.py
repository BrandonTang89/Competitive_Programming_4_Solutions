h, w = map(int, input().split())
grid = [list(input()) for i in range(h)]

c = [0,0,0,0,0]
for i in range(0, w-1):
    for j in range(0, h-1):
        cur = 0
        for k in range(2):
            for l in range(2):
                if grid[j+k][i+l] == '#':
                    cur = -100
                    break
                if grid[j+k][i+l] == 'X':
                    cur += 1
        
        if (cur < 0): continue
        c[cur] += 1

for i in range(5):
    print(c[i])