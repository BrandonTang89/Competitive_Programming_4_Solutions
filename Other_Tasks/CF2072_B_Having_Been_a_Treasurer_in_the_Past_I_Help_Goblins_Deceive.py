from collections import Counter

for _ in range(int(input())):
    n = int(input())
    c = Counter(input())
    x = c["-"] // 2
    y = c["_"]
    z = c["-"] - x
    print(x * y * z)
