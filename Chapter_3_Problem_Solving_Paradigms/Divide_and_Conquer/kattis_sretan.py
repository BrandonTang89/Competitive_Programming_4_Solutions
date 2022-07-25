'''
Kattis - sretan
Make some observations regarding the relationship between the sequence of lucky numbers and binary... Then just do it.

Time: O(log(n)), Space: O(log(n))'''
from math import log2, floor
x = int(input())

num_digits = floor(log2(x + 1))
num = bin(x+1 - 2**num_digits)[2:]
num = num.replace('0', '4').replace('1', '7')
num = (num_digits - len(num)) * '4' + num

print(num)