t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    
    ans = n
    for i in range(n):
        
        numBigger = 0
        for j in range(i+1,n):
            if arr[j] > arr[i]:
                numBigger += 1
        
        ans = min(ans, i + numBigger)
    
    print(ans)