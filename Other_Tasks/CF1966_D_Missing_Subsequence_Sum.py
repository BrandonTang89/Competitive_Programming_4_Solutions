t = int(input())

for _ in range(t):
    n, k = map(int, (input().split()))

    # smallest power of 2 <= than k
    p = 0
    while (1<<p) <= k: p += 1
    p -= 1
    ans = [k+1, k+(1<<(p+1))]
    
    # if k is a power of 2
    if (1<<(p)) != k:
        ans.append(k-(1<<p))
    
    for i in range(25):
        if i == p: continue
        if (1<<i) < n: ans.append(1<<i)
        else: break
    
    
    print(len(ans))
    print(*ans)