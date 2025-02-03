for _ in range(int(input())):
    
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    
    extra = n - k 
    
    ans = 0
    if extra == 0:
        for i in range(1, n, 2):
            if arr[i] != i//2 + 1:
                ans = i//2 + 1
                break
        else:
            ans = n//2 + 1
    else:
        for i in range(1, extra+2):
            if arr[i] != 1:
                ans = 1
                break
        else:
            ans = 2
    print(ans)