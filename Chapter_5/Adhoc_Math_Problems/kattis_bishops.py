'''
Kattis - bishops
Assume that we only consider bishops on black squares. Every bishop placed will use one / and one \
diagonal. If we consider n to be even, the minimum number of / and \ diagonals is n-1. Then since
the number of white tiles is the same as the number of black tiles, then we just take 2*(n-1) as the
max possible answer. You can apply this to odd n to see that 2*(n-1) is still the maximum possible
answer.

But can we reach this all the time? Yes. Just fill the entire left and right columns. We will realise
the corners will attack each other, remove 2 corners. We are done. The rest of the bishops wont attack
each other.

Time: O(1), Space: O(1)
'''
from sys import stdin
for line in stdin:
    line = line.strip()
    n = int(line)
    if n==1:
        print(1)
    else:
       print(2*(n-1))
       