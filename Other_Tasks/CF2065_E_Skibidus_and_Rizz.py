for _ in range(int(input())):
    n, m, k = map(int, input().split())
    
    if n < k and m < k: 
        print(-1)
        continue
    
    if max(n, m) - min(n, m) > k:
        print(-1)
        continue
    
    if n > m:
        start = 0
    else:
        start = 1
        
    ans = ""
    while n > 0 or m > 0:
        if start == 0:
            ans += "0" * min(k, n)
            n -= min(k, n)
            start = 1
        else:
            ans += "1" * min(k, m)
            m -= min(k, m)
            start = 0
    
    print(ans)