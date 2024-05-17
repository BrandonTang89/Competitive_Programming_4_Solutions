t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = [0] * n
    
    indexOfMax = arr.index(max(arr))
    
    if indexOfMax % 2 == 0:
        # all the even indexes are big
        bigs = list(range(0, n, 2))
        smalls = list(range(1, n, 2))
    else:
        # all the odd indexes are big
        bigs = list(range(1, n, 2))
        smalls = list(range(0, n, 2))
            
    
    bigs.sort(key=lambda x: arr[x], reverse=True)
    
    for i in range(n//2):
        ans[bigs[i]] = (i+1+n//2)
        
    smalls.sort(key=lambda x: arr[x], reverse=True)
    for i in range(n//2):
        ans[smalls[i]] = (i+1)
        
    print(*ans)
        
        
        