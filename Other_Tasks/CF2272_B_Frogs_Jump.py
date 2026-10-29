for _ in range(int(input())):
    n = int(input())
    grid = [list(input()) for _ in range(2)]
    grid = [[1 if c == 'f' else 0 for c in row] for row in grid]
    
    ans = 0
    for i in range(n):
      if grid[0][i] + grid[1][i] == 1:
        ans ^= 1
    
    print(ans)