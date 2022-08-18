'''
Kattis - bijele
Just straightforward

Time: O(1), Space: O(1)'''
default = [1, 1, 2, 2, 2, 8]
cur = list(map(int, input().split()))
for i, j in zip(default, cur):
    print(i - j, end=' ')
