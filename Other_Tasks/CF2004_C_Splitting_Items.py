t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    
    arr = list(map(int, input().split()))
    arr.sort(reverse=True)
    
    rk = k
    for i in range(0, n-1, 2):
        maxUp = arr[i] - arr[i+1]
        update = min(maxUp, rk)
        rk -= update
        arr[i+1] += update
        if rk == 0:
            break
    
    ans = 0
    for i in range(0, n):
        ans += (-1 if i % 2 == 1 else 1) * arr[i]
    
    print(ans)
        
        