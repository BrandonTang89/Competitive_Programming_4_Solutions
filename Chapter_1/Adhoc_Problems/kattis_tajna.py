'''
Kattis - Tajna
A relatively simple 2d cipher. Done easily with the use of a matrix transpose that is done easily in python

Time: O(n), Mem: O(n)
'''

from math import sqrt

ctext = input()
n = len(ctext)

for i in range(int(sqrt(n)), 0, -1):
    if n%i == 0:
        r=i
        c=n//r
        break
r,c = c,r
arr = [["a"]*c for i in range(r)]
for i in range(r):
    for j in range(c):
        index = i*c+j
        arr[i][j] = ctext[index]
arr = [*zip(*arr)]

r,c = c,r
ans = ""
for i in arr:
    for j in i:
        ans += j
print (ans)

