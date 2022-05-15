'''
Kattis - deadfraction
The solution involves assuming the last i digits are repeating for all possible values of i.
We can then calculate the fraction using a generalisation of the classic proof that 0.9... is 1.

x = 0.999999...
10x = 9.999999...
10x - x = 9x = 9
=> x = 1

The generalisation is left as a proof to the reader :)

Note that we cant just print(best_f) for the edge case where best_f = 1 (hard to find)

Time: O(len(s)), Space: O(1)
'''
from fractions import Fraction
while True:
    s = input()
    if s == "0":
        break

    s = s[2:-3] # remove 0. and ...

    l = len(s)
    x = int(s)

    best_f = Fraction(0, 1)
    for i in range(1, l+1): # last i digits are repeating...
        f = Fraction(x-(x//10**i), 10**l-10**(l-i))
        # print(i, f)
        if (f.denominator < best_f.denominator or best_f == Fraction(0, 1)):
            best_f = f
    
    print(str(best_f.numerator) + '/' + str(best_f.denominator))
