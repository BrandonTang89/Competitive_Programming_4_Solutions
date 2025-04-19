for _ in range(int(input())):
    n = int(input())
    a = list(input())
    a.reverse()
    
    top = n
    bottom = 1
    
    ans = []
    for x in a:
        if x == '<':
            ans.append(bottom)
            bottom += 1
        else:
            ans.append(top)
            top -= 1
    
    ans.append(bottom)
    
    ans.reverse()
    
    print(*ans)