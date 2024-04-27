
tc = int(input())
for _ in range(tc):
    h, w = map(int, input().split())
    grid = [list(input()) for _ in range(h)]

    def canDo(c):
        minr, maxr, minc, maxc = h, -1, w, -1
        for i in range(h):
            for j in range(w):
                if grid[i][j] == c:
                    minr = min(minr, i)
                    maxr = max(maxr, i)
                    minc = min(minc, j)
                    maxc = max(maxc, j)
        
        if minr == 0 and maxr == h-1 and minc == 0 and maxc == w-1:
            return 1
        return 0
    
    ans = canDo('W') or canDo('B')
    print('YES' if ans else 'NO')
    