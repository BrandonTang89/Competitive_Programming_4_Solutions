'''
Kattis - pervasiveheartmonitor
Simple input parsing, just try to write as little code as possible.
'''
import statistics
from sys import stdin
for line in stdin:
    line = line.strip()
    line = line.split()
    name = []
    while line[0][0].isalpha():
        name.append(line.pop(0))
    while line[-1][0].isalpha():
        name.insert(0, (line.pop()))
    name = ' '.join(name)
    
    line = [float(x) for x in line]
    line = statistics.mean(line)
    print(line, name)