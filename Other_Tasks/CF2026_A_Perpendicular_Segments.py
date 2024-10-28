
t = int(input())
for _ in range(t):
    x, y, k = map(int, input().split())
    
    x = min(x, y)
    
    print(0, 0, x, x)
    print(x, 0, 0, x)