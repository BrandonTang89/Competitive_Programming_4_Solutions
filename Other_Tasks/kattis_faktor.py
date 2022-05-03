from math import ceil
x, y = map(int, input().split())
for i in range(100000):
    if (ceil(i/x) == y):
        print(i)
        break