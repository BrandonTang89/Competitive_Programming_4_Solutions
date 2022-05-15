'''
Kattis - batteries
The egg dropping problem but with a fixed number of eggs, 2.

Time: O(n), Space: O(1)
'''
def f(d, k): # number of floors we can determine with d drops and k eggs
    ans = 0
    cur = 1 # d choose i
    
    for i in range(1, k+1):
        cur = cur * (d-i+1) // i # d choose i = d choose (i-1) * (d-i+1) / i
        ans += cur
    return ans

while (True):
    n = int(input())
    if (n == 0): break
    n -= 1 # we only need to test from 1 to n-1
    k = 2
    for i in range(n+1):
        if (f(i, k) >= n): # able to do these many floors
            print(i)
            break