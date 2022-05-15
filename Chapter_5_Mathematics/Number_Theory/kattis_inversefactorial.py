'''
Kattis - inversefactorial
A key insight is that past 10!, each subsequent factorial is more than an order of magnitude larger
than the previous factorial, and thus is also at least 1 more digit in length. Thus, we can store
the a dictionary of inverse_fact[len(n!) - 1] = [all a such that len(a!) = n!]. This will be
a size 1 list for all n > 10. If the list is not of size 1, n! must be sufficiently small to compute
manually so we just check all n! from 1 to 10.

Time: O(1), Space: O(1)
'''
from math import log10, floor
inverse_fact = dict() # inverse_fact[len(n!) - 1] = [all a such that len(a!) = n!]

# Calculate factorial recursively
def factorial(n):
    if (n == 0):
        return 1
    return n * factorial(n - 1)


cur = 0 # log10(0!) = 0
for i in range(1, 100000000):
    cur += log10(i)
    if (not floor(cur) in inverse_fact):
        inverse_fact[floor(cur)] = [i]
    else:
        inverse_fact[floor(cur)].append(i)
        
    if (cur > 1e6):
        break

# print(inverse_fact)
n = input()

if (len(inverse_fact[len(n) - 1]) == 1):
    print(inverse_fact[len(n)-1][0])
else:
    n = int(n)
    for i in range(1, 11):
        if (factorial(i) == n):
            print(i)
            break