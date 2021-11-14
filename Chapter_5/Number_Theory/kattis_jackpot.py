'''
Kattis - jackpot
Simply get the LCM of all numbers. Note the property that LCM(a, b, c, ...) = LCM(LCM(a, b), c, ...)
GCD also has this property.

Time: O(n * log(INT_MAX)) Space O(n), Assuming Euclidean algorithm is O(log (INT_MAX))
'''
from math import gcd
def lcm(a, b):
    return a * b // gcd(a, b)

num_tc = int(input())
for _ in range(num_tc):
    n = int(input())
    arr  = list(map(int, input().split()))
    cur = arr[0]
    
    if (n == 1):
        print(cur)
        continue
    
    for i in range(1, n):
        cur = lcm(cur, arr[i])
        if (cur > 1e9):
            print("More than a billion.")
            break
        
        if (i == n-1):
            print(cur)
