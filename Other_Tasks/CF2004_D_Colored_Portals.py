for _ in range(int(input())):
    n, q = map(int, input().split())
    inf = int(1e18)
    latest = {}
    latest["BG"] = -inf
    latest["BR"] = -inf
    latest["BY"] = -inf
    latest["GR"] = -inf
    latest["GY"] = -inf
    latest["RY"] = -inf
    
    arr = list(input().split())
    sameLeft = [-inf for i in range(n)]
    sameRight = [inf for i in range(n)]
    
    for i in range(n):
        for k in latest:
            if len(set(k + arr[i])) == 3:
                sameLeft[i] = max(sameLeft[i], latest[k])
        latest[arr[i]] = i
        
    
    latest["BG"] = inf
    latest["BR"] = inf
    latest["BY"] = inf
    latest["GR"] = inf
    latest["GY"] = inf
    latest["RY"] = inf
    
    for i in range(n-1, -1, -1):
        for k in latest:
            if len(set(k + arr[i])) == 3:
                sameRight[i] = min(sameRight[i], latest[k])
        latest[arr[i]] = i
        
    for _ in range(q):
        l, r = map(int, input().split())
        if l > r: l, r = r, l
        l -= 1
        r -= 1
        
        if len(set(arr[l] + arr[r])) <= 3:
            print(r - l)
            continue
        
        if sameRight[l] <= r:
            print(r - l)
            continue
        
        extra = min(l - sameLeft[l], sameRight[l] - r)
        if extra >= int(1e7):
            print(-1)
            continue
        print(r - l + extra*2)