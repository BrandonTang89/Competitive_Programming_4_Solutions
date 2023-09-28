'''
Kattis - zapis
In theory this isn't terribly hard, but it may be non-trivial to see the state and transitions.
Let getSol(l, r) be the number of ways to make s[l:r] a valid expression. The transitions are
decomposing it into something of the form (A)B where A and B are valid expressions. We try all
possible lengths of A (and correspondingly B). The base cases are when l == r (empty string)
or when it is straight up impossible (starting with a closing or ending with an opening bracket).

Note a super annoying bug where they want the last 5 digits. If we just take mod 1e5, we may lose
leading zeros so we need to remember to deal with that... Cost me 2 hours.

Time: O(n^3), Space: O(n^2)
'''
from functools import lru_cache
n = int(input())
s = input()
m = {'(': ')', '[': ']', '{': '}'}
closing = set(')]}')
mod = int(1e5)

fiveormore = False

@lru_cache(maxsize=None)
def getSol(l, r):  # how many ways to make s[l:r] a valid expression
    global fiveormore
    assert (l <= r and l >= 0 and r <= n and (r-l) % 2 == 0)
    if l == r:
        return 1
    if s[l] in closing:
        return 0  # impossible
    if s[r-1] in m:
        return 0  # impossible

    ans = 0
    for i in range(l+2, r+1, 2):
        if s[l] in m:                               # s[l] is an opening bracket
            if s[i-1] == m[s[l]] or s[i-1] == '?':  # s[i-1] can match with s[l]
                ans += (getSol(l+1, i-1)*getSol(i, r))
        else:  # s[l] == '?'
            if s[i-1] == '?':
                ans += (3*getSol(l+1, i-1)*getSol(i, r))
            elif s[i-1] in closing:                 # set s[l] to the corresponding opening bracket
                ans += (getSol(l+1, i-1)*getSol(i, r))

        if ans >= mod:
            fiveormore = True
            ans %= mod

    return ans


x = getSol(0, n)
if fiveormore:
    print("{:05d}".format(x % mod))
else:
    print(x % mod)
