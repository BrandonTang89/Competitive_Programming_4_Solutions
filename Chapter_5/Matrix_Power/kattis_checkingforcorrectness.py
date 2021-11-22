'''
Kattis - checkingforcorrectness
Pretty simple with python due to built-in efficient power with modulus function and native big integer
support.

Time: O(log b), Space: O(1)
'''
from sys import stdin
for line in stdin:
    line = line.strip()
    a, op, b = line.split()
    a = int(a)
    b = int(b)
    if op == "+":
        print((a + b) % 10000)
    elif op == "-":
        print((a - b) % 10000)
    elif op == "*":
        print((a * b) % 10000)
    elif op == "^":
        print(pow(a,b, 10000))