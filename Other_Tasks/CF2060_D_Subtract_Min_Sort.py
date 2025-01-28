for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    
    can = True
    for i in range(n-1):
        if arr[i] > arr[i+1]:
            can = False
            break
        
        arr[i+1] -= arr[i]
        arr[i] = 0
    
    print('YES' if can else 'NO')