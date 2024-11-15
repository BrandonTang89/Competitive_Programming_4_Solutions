from collections import Counter
for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    c = Counter(arr)
    maxi = max(c.values())
    print(n - maxi)