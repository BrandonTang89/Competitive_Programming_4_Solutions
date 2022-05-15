'''
Kattis - lowerorderzeros
This is a scam solution... It is quite obvious that we don't need to store all the digits before the
trailing zeros, but how many is a good enough number? Well.. im not sure but we can just store as many
as we can... 20 digits is probably enough since people coding in C++ will not even be able to store
that many digits in a long long. (note storing 20 digits will give AC)

Thinking abit, the number of digits before the trailing zeros must be at least 1 more than the number
of additional zeros that can occur after multiplying by i. Every matching 2 and 5 prime factor will
produce 1 more additional zero. E.g. from 14! to 15!, we multiply by 15 = 3 * 5. We are adding 1
more 0 due to the additional prime factor of 5. Note that the pairing is limited by the number of 5s
rather than the number of 2s. So in the worse case scenario, we are adding 7 5s to the prime
factorisation when we go from (5^8 -1)! to (5^8)!, so thats 8 extra 0s and thus we need to minimally
store 9 digits.

Note that generally, if we compute until UPPERBOUND!, we need to store floor(log5(UPPERBOUND)) + 1
digits.

Time: O(1e6), Space: O(1e6)
'''
from math import log10, floor
lowestnonzero = [1]

for i in range(1, int(1e6) + 1):
    x = lowestnonzero[-1] * i
    while (x % 10 == 0):
        x //= 10
    x %= 10**(9) # store minimally 9 digits
    lowestnonzero.append(x)
    # print(i, x)

while(1):
    c = int(input())
    if (c == 0):
        break
    print(lowestnonzero[c] % 10)
