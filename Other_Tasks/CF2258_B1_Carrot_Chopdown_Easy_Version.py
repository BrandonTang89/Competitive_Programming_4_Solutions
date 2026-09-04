from collections import Counter

for _ in range(int(input())):
    n, m = map(int, input().split())
    arr = list(map(int, input().split()))
    arr.sort(reverse=True)
    
    c = Counter(arr)
    
    num_cut = 0
    maxi = 0
    for i in range(m, 0, -1):
        while num_cut < n and arr[num_cut] >= i:
            num_cut += 1
        maxi = max(maxi, num_cut + c[2*i])
        
    print(maxi)