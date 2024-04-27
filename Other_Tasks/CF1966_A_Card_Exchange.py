t = int(input())

for _ in range(t):
    counter = {}
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    for i in arr:
        if i in counter:
            counter[i] += 1
        else:
            counter[i] = 1
            
    maxi = max(counter.values())
    if (maxi >= k): print(min(n, k-1))
    else: print(n)