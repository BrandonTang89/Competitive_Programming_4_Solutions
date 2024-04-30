t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    j = 0 # index into a

    ans  = 0
    for i in range(n):
        if a[j] <= b[i]: 
            j += 1
        else:
            ans += 1
            
    print(ans)