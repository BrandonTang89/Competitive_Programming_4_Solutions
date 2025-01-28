for _ in range(int(input())):
    
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    arr.sort()
    
    i = 0
    j = n-1
    npairs = 0
    while i < j:
        if arr[i] + arr[j] > k:
            j -= 1
        elif arr[i] + arr[j] < k:
            i += 1
        else: 
            npairs += 1
            i += 1
            j -= 1
    
    left = n - 2*npairs
    
    if left%2 == 0:
        print (npairs)
    else:
        print (0)
    
