t = int(input())
for _ in range(t):
    n = int(input())
    
    a, b = 0, 0
    pos, neg = 0, 0
    arr = list(map(int, input().split()))
    brr = list(map(int, input().split()))
    
    for i in range(n):
        x, y = arr[i], brr[i]
        if x < y:
            b += y
        elif y < x:
            a += x
        # now all x == y
        elif x == -1 and y == -1:
            neg += 1
        elif x == 1 and y == 1:
            pos += 1
        elif x == 0 and y == 0:
            continue
        else: 
            assert False
    
    a -= neg
    b -= neg
    
    pos += neg
    if a > b: a, b = b, a
    
    # a <= b
    diff = b - a
    # print(a, b, pos, diff)
    if pos <= diff:
        print(a + pos)
    else:
        print(b + (pos-diff) // 2)
    
    
    