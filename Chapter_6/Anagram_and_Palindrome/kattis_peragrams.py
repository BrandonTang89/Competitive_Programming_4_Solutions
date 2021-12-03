'''
Kattis - peragrams
In the peragram, we can have a max of 1 odd frequency char as we just count the number of odd
chars -1. Edge case when all frequencies are even.

Time: O(n), Space: O(1)
'''
s = input()
from collections import Counter
c = Counter(list(s))

ans = 0
for f in c.values():
    if (f % 2 == 1):
        ans += 1

print(max(ans - 1, 0))