'''
Kattis - savingdaylight
Some time delta computations.

Time: O(n), Space: O(1)
'''
from sys import stdin
import datetime
for line in stdin:
    line = line.split()
    
    a = line[-1].split(':')
    b = line[-2].split(':')
    
    td = datetime.datetime(2000, 1, 1, int(a[0]), int(a[1])) - datetime.datetime(2000, 1, 1, int(b[0]), int(b[1]))
    hr, mi = td.seconds//3600, (td.seconds//60)%60
    
    print(f"{line[0]} {line[1]} {line[2]} {hr} hours {mi} minutes")