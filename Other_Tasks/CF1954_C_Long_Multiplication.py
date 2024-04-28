t = int(input())

for _ in range(t):
    x = list(map(int, list(input())))
    y = list(map(int, list(input())))

    
    n = len(x)
    
    i = 0
    while i < n and x[i] == y[i]:
        i += 1
        
    if i < n and y[i] < x[i]: x, y = y, x
    
    # x[i] < y[i]
    for j in range(i+1, n):
        x[j], y[j] = max(x[j], y[j]), min(x[j], y[j])
        
    print(''.join(map(str, y)))
    print(''.join(map(str, x)))