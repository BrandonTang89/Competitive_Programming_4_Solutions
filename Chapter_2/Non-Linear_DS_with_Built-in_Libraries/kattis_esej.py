'''
Kattis - esej
Very different problem than normal. I opted to generate random length 15 words and store in a hashtable.
Just ensure that the number of words produced is correct.

Time: O(max(b/2, a)), Space: O(max(b/2, a))
'''
from random import randint
from math import ceil

a, b = map(int, input().split())
s = set()

while len(s) < max(ceil(b/2), a):
    w = ""
    for i in range(15):
        w += chr(randint(97, 122))
    
    s.add(w)

for i in s:
    print(i, end=" ")