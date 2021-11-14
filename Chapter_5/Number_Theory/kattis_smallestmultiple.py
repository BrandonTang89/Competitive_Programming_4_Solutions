'''
Lattis - smallestmultiple
Just return LCM of all the numbers.

Time: O(n * log(INT_MAX)) Space O(n), Assuming Euclidean algorithm is O(log (INT_MAX))
'''
from math import gcd
from sys import stdin
def lcm(a, b):
    return a * b // gcd(a, b)

for line in stdin:
    arr = [int(x) for x in line.split()]
    ans = arr[0]
    for i in range(1, len(arr)):
        ans = lcm(ans, arr[i])
    
    print(ans)
