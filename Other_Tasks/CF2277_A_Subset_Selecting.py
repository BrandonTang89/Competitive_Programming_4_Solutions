
for _ in range(int(input())):
    
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    
    freq = [0] * (n+1)
    
    for i in arr:
        freq[i] += 1
    
    reserve = 0
    for i in range(n+1):
        if freq[i] == 0:
            print(i)
            break
        freq[i] -= 1
        reserve += freq[i]
        reserve -= (k-1)
        
        if reserve < 0:
            print(i)
            break
        
    else:
        print(n+1)
        