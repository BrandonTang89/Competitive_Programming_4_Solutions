for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    ans = 0
    cur = 0
    for i in range(n):
        if a[i] >= k:          
            cur += a[i]
        if a[i] == 0 and cur > 0:
            cur -= 1
            ans += 1
    
    print(ans)