t = int(input())
for _ in range(t):
    x, y = map(int, input().split())
    
    ans = 0
    while x > 1:
        x -= (y-1)
        ans += 1
    print(ans)