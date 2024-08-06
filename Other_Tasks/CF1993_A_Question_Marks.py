from collections import Counter

tc = int(input())
for _ in range(tc):
    n = int(input())
    c = Counter(list(input()))
    ans = sum(min(n, c[x]) for x in 'ABCD')
    print(ans)