'''
Kattis - jughard
Seems like d being a multiple of the GCD is actually both a necessary and sufficient condition.
Time: O(log n), Mem: O(1)
'''
tc = int(input())
from math import gcd
for _ in range(tc):
    a, b, d = map(int, input().split())
    if (d % gcd(a, b)  == 0):
        print("Yes")
    else:
        print("No")