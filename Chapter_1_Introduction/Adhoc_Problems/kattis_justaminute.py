'''
Kattis - justaminute
Simple loop problem.

Time: O(n), Space: O(1)
'''
n = int(input())
a, b = 0, 0
for i in range (n):
    x, y = map(int, input().split())
    a += x*60
    b += y

print(b / a if b/a > 1 else "measurement error")