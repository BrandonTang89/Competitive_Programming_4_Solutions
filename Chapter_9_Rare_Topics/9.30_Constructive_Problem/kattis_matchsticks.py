'''
Kattis - matchsticks
Quite a weird constructive problem. For the largest number, it seems fairly obvious that we should just spam 1s as much as possible
(in the less significant digits), then the MSD shall be either 1 or 7 depending on the parity of n.

For the smallest number, its abit weirder. Clearly we want to minimise the number of digits so we want to use as many 8s as possible.
We express n as a multiple of 7 (since 7 match sticks make an 8), so n = x+7+7+...+7 for some x in [0..6].

The issue if we can possibly distribute some 7s to get a better solution:
E.g. for n = 4+7+7+7+7 we would get 48888 by just greedily putting 8s, but we can actually get 20888
if we distribute to become n = 5+6+7+7+7. 

We could perform some analysis on how many "special cases" there are, but we know that these are finite and small so the strategy is to
use a table to store the answers for the first n <= k cases and greedily put 8s until we reach a number in the table. Increase k until
we go from WA to AC.

It might be ugly but it works.

Time: O(n), Space: O(n)
'''
tc = int(input())

tb = {
    2: 1, 3: 7, 4: 4, 5: 2, 6: 6, 7: 8, 8: 10, 9: 18,
    10: 22, 11: 20, 12: 28, 13: 68, 14: 88, 15: 108, 16: 188, 17: 200,
    18: 208, 19: 288, 20: 688, 21: 888, 22: 1088, 23: 1888, 24: 2008,
}

for _ in range(tc):
    n = int(input())

    arr = []
    r = n
    while r >= 4:
        arr.append('1')
        r -= 2
    if r == 3:
        arr.append('7')
    elif r == 2:
        arr.append('1')

    bignum = ''.join(arr[::-1])

    arr = []
    r = n
    while r not in tb:
        arr.append('8')
        r -= 7

    if r in tb:
        arr.append(str(tb[r]))
    else:
        assert r == 0

    smallnum = ''.join(arr[::-1])

    print(smallnum, bignum)
