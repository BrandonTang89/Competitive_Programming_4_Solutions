t = int(input())
for _ in range(t):
    n = int(input())
    a = list(input())
    a = [int(x) for x in a]
    
    b = [a[0]]
    for i in range(1,n):
        if a[i-1] == a[i] and a[i] == 0: continue
        b.append(a[i])
        
    if b.count(1) > b.count(0):
        print("Yes")
    else:
        print("No")