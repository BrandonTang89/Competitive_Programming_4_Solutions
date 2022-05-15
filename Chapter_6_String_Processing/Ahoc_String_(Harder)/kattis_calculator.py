'''
Kattis - calculator
Incredibly hacky Python 3 solution. 

Time: O(length of input), Space: O(1)
'''
from sys import stdin
for line in stdin:
    x = line.strip()
    x = eval(x)
    print("{:.2f}".format(x))