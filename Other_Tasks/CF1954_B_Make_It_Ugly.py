t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    
    p = arr[0] # the element that will propogate
    
    for i in range(0, n):
        if arr[i] != p: arr[i] = 0
        else: arr[i] = 1
    
    arr = ''.join(map(str, arr))
    xss = arr.split('0')
    sizes = [len(xs) for xs in xss]
    
    ans = min(sizes)
    if ans == n:
        print(-1)
    else: print(ans)