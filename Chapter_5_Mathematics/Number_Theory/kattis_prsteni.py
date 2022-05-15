'''
Kattis - prsteni
Simple fraction question. Look around for the pattern, the key insight is radius and number of turns
are inversely proportional. Just take the ratio of the radius of the first and the ith circle to get
the ratio of the turns of the ith circle to the first circle.

Time: O(1)
Space: O(1)
'''
n = int(input())
arr = list(map(int, input().split()))

from fractions import Fraction
for i in range(1, n):
    f = Fraction(arr[0], arr[i])
    print(str(f.numerator) + "/" +  str(f.denominator))