t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    
    def process(arr):
        hasOne = set()
        curMax = 0
        
        brr = [0 for i in range(n)]
        for i in range(n):
            if arr[i] in hasOne:
                curMax = max(curMax, arr[i])
            else:
                hasOne.add(arr[i])
            
            brr[i] = curMax
        
        return brr

    ans = sum(arr)
    arr = process(arr)
    
    ans += sum(arr)
    arr = process(arr) 
    
    for i in range(n):
        ans += arr[i]*(n-i)
    
    print(ans)    
            
            
                