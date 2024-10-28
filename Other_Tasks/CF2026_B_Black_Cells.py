inf = int(1e19)
def checkMaxi(arr):
    n = len(arr)
    assert n % 2 == 0
    maxi = 0
    for i in range(0, n, 2):
        maxi = max(maxi, arr[i+1] - arr[i])
        
    return maxi
        
t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    if n == 1:
        print(1)
        continue
    if n % 2 == 0:
        print(checkMaxi(arr))
    else:
        best=  inf
        for i in range(n):
            best = min(best, checkMaxi(arr[:i] + arr[i+1:]))
            
        print(best)