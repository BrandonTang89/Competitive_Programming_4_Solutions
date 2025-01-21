for  _ in range(int(input())):
    n, m = map(int, input().split())
    
    totalX = 0
    totalY = 0
    
    input()
    for i in range(n-1):
        x, y = map(int, input().split())
        totalX += x
        totalY += y
        
    print((totalX + m + totalY + m) * 2)