'''
Kattis - rijeci
from fibo(0) = 0, fibo(1) = 1, output the x-1th and xth fibo numbers, x <= 45
Simply use a for loop.

Time: O(x), Space: O(1)
'''
x = int(input())
a = 1
b = 0

for i in range(x):
    a, b = b, a+b

print(a, b)