for _ in range(int(input())):
    a, b, c = map(int, input().split())
    if (a + b + c) % 3 != 0:
        print("NO")
        continue
    
    target = (a + b + c) // 3
    
    if b > target:
        print("NO")
        continue
    
    avail = c - target
    need = (target - a) + (target - b)
    if avail >= need:
        print("YES")
    else:
        print("NO")    