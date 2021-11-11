'''
Kattis - thermostat
This is a somewhat elementary fractions question. Note that due to the availability of time, we choose
to convert the source language to celcius before converting it to the target lanaguage, reducing
memory use and complexity of code.

Time: O(q + n), Space: O(n)
'''

from fractions import Fraction
num_lang, q = map(int, input().split())

langs = []
for _ in range(num_lang):
    c, x = map(int, input().split())
    m = Fraction((x - c), 100)
    langs.append((m, Fraction(c)))

for _ in range(q):
    x, y, v = list(map(int, input().split()))
    x-= 1
    y-= 1

    m, c = langs[x]
    cel = (Fraction(v) - c)/m

    res = langs[y][0] * cel + langs[y][1]
    if (res == Fraction(0)):
        print("0/1")
    else:
        print(str(res.numerator) + "/" + str(res.denominator))