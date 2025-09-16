for _ in range(int(input())):
    a, x, y = map(int, input().split())
    x, y = min(x, y), max(x, y)
    
    if x <= a and a <= y:
        print("NO")
    else:
        print("YES")