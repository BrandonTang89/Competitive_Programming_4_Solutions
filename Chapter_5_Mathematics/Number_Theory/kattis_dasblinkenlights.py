'''
Kattis - dasblinkenlights
Simple lcm check.

Time: O(log (max(a, b))), Space: O(1)
'''
from math import gcd
a, b, m = map(int, input().split())
def lcm(a, b):
    return a * b // gcd(a, b)
if lcm(a, b) <= m:
    print('yes')
else:
    print('no')
