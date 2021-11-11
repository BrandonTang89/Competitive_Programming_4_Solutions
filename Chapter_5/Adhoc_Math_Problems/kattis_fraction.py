'''
Kattis - fraction
A relatively elementary problem, but it's worth knowing how to solve it. Simply convert between
fractions and continued fractions. Way easier with python fraction library compared to C++.

Time: O(len of continued fraction), Space: O(len of continued fraction)
'''
from fractions import Fraction
import copy
def from_continued_fraction(o_pq):
    pq = copy.deepcopy(o_pq[::-1])
    a = Fraction(pq[0])
    for i in range(1, len(pq)):
        a = Fraction(1)/a
        a = Fraction(pq[i]) + a
    return a

def to_continued_fraction(a):
    if (a.denominator == 1):
        return [a.numerator]
    
    cur = [a.numerator // a.denominator]
    cur += to_continued_fraction(1/(a - cur[0]))
    return cur

na, nb = list(map(int, input().split()))
a_pq = list(map(int, input().split()))
b_pq = list(map(int, input().split()))

a = from_continued_fraction(a_pq)
b = from_continued_fraction(b_pq)

s = a + b
d = a - b
m = a * b
q = a / b

for i in to_continued_fraction(s):
    print(i, end=" ")
print()
for i in to_continued_fraction(d):
    print(i, end=" ")
print()
for i in to_continued_fraction(m):
    print(i, end=" ")
print()
for i in to_continued_fraction(q):
    print(i, end=" ")
print()
