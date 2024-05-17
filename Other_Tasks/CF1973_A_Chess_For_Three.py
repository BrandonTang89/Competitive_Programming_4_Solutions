t = int(input())
for _ in range(t):
    a, b, c = map(int, input().split())
    a, b, c = sorted([a, b, c])
    
    if ((a + b + c) % 2 == 1):
        print(-1)
        continue
    
    ans = 0
    while (b > 0 and c > 0):
        ans += 1
        b -= 1
        c -= 1
        a, b, c = sorted([a, b, c])
        
    print(ans)