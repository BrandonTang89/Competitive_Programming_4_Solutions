t = int(input())

for _ in range(t):
    n = int(input())
    arr = list(input())
    numu = 0
    
    for i in range(n):
        if arr[i] == 'U':
            numu += 1
    
    if (numu) % 2 == 0:
        print("NO")
    else:
        print("YES")