'''
Kattis - howmanydigits
The numeber of digits of a number k = floor(log10(k)) + 1
We precompute (bottom up dp) the values of log10(k!) for k = 1 to 1_000_000
then answer each query in O(1)
Time: O(1) per query, Space: O(1)
'''
from sys import stdin
import math
log10s = [0]
for i in range(1, 1_000_001):
    log10s.append(log10s[-1] + math.log10(i))
for line in stdin:
    x = int(line)
    print(math.floor(log10s[x]) + 1)
