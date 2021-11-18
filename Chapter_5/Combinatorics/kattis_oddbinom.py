'''
Kattis - oddbinom
I don't get why the difficulty rating is so low, this is is actually not that easy to determine an
efficient solution for.

The most obvious solution is the O(n^2) DP solution where we just keep computing n choose k mod 2.
This will definitely TLE.

The first step is to draw pascal's triangle mod 2. Now, if we let f(x) be the sum of row x, (1 indexed)
we realise that f(x) = 2*f(x - 2**floor(log2(x))). This is due to the symmetry of the triangle:
notice that rows 5 to 8 are just 2 copies of rows 1 to 4, while rows 9 to 16 are 2 copies of rows
1 to 8 and so on.

But with n <= 1e11, it is MLE to store f(x) for all f(x) required... Is there a better way?
Yes. Notice that f(x) = 2**pop_count(x-1). This is also due to symmetry. This gives an O(n) solution
but with TLE...

The next key insight is that that we are counting 2**pop_count(x-1) for each x in the range [0, n-1],
but we don't have to go in that order... A better way is to look at x in binary form. E.g. bin(4) = 100.

Now for x = 4, we notice that we can arrange [0, 3] in the following way: 
(000)
(001) (010)
(011)

where the number of numbers in each row i is 2 choose i. Then then the answer is the sum of (2 choose i)
* 2**i. But the issue is generalising this for x which might not be a power of 2.

Well now we consider x = 6 = b110. Similarly, we can let the first digit be 0 and get
(000)
(001) (010)
(011)

However, we can next let the first digit be 1. And then we are left with choosing the other 2 digits.
We can repeat the above process to do this. Since the second digit is 1, we let it be 0. and get
(100)
(101)

In general, we can iterate across the binary representation of a number, if our digit is 1, we process
the numbers less than x with that binary digit being 0. Then we assume it is 1 and move on to the next
digit in our iteration.

Assuming we use the DP binomial coefficient code, we get the following complexities
Time: O(log(n)**2), Space: O(log(n)**2)
Since we use 2 nested for loops on the binary rep of n. We can assume that the total time for all
the calls to comb will only be O(log(n)**2) since it has a state space of O(log(n)**2) and a transition
of O(1)
'''
from functools import lru_cache
@lru_cache(maxsize=None)
def comb(n, r):
    if (r == 0 or r == n): return 1
    return (comb(n-1, r-1) + comb(n-1, r))


x = int(input())
x = bin(x)[2:]
ans = 0
ones = 0
for i in range(0, len(x)):
    if (x[i] == '0'): continue
    for r in range(0, len(x) - i):
        ans += comb(len(x) - i - 1, r) * (1 << (r + ones))
    ones += 1
print(ans)