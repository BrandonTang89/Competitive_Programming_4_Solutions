t = int(input())
for _ in range(t):
    n, x, y = map(int, input().split())
    x-=1 
    y-=1
    
    arr = [0 for i in range(n)]
    for i in range(y, x+1):
        arr[i] = 1
    
    c = -1
    for i in range(x+1, n):
        arr[i] = c
        c *= -1
    
    c = -1
    for i in range(y-1, -1, -1):
        arr[i] = c
        c *= -1
    
    print(*arr)
        