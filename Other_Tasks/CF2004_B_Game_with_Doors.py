for _ in range(int(input())):
    
    al, ar = map(int, input().split())
    bl, br = map(int, input().split())
    
    if al > bl:
        al, ar, bl, br = bl, br, al, ar
    
    if ar < bl: 
        print(1) 
        continue
    
    if ar > br:
        ans = 0
        if al < bl: ans += 1
        print (ans + 1 + br - bl)
        continue
    
    ans = 0
    if al < bl: ans += 1
    if ar < br: ans += 1
    ans += ar - bl
    
    print(ans)