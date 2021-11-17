'''
Kattis - lockedtreasure
The answer is just n choose (m-1), easy to implement. But why? the proof is not as easy.

Idea 1:
    We create 1 lock for every way to choose m-1 pirates from n pirates. For each combination,
    the lock cannot be opened by the pirates of that combination and can be opened by any other pirate.
    
    This ensures that for each set of m-1 or less prirates, there is exactly 1 lock that the set
    cannot open.
    
    Illustration, 0 represents no key, 1 represents a key.
    1 2 3 4
    1 1 0 0
    1 0 0 1
    0 0 1 1
    1 0 1 0
    0 1 0 1
    1 0 0 1
    0 1 1 0
    
    E.g. if 1 and 3 try, the lock (0 1 0 1) prevents them from opening the chest.
    
    However, we note that any combination of m or more pirates can definitely open the chest. This is
    because for each lock, there are only m-1 '0's, but we have m pirates, thus by pigeonhole principle,
    at least one pirate will a key to that lock.
    
    So now we know that this idea with n choose m-1 locks will be a valid solution. But is it the best?

Observation 1:
    Notice that for each lock, we prevent a specific combination of m-1 pirates from opening the chest.
    But is there any way to use less locks? ote that if we want to use less locks, for at least 1
    of the new locks, we must have > m-1 '0' to prevent at least 2 different combinations of m-1
    pirates from opening the chest.
    
    But in this case, we can choose m pirates such that all these pirates have no key to the above
    mentioned lock, since the lock has >= m '0's, then m pirates would be unable to open the chest,
    making it an invalid solution.
    
    Thus it is not possible to use less locks.

Time: O(n^2), Space: O(n^2)
'''

from functools import lru_cache
@lru_cache(maxsize=None)
def comb(n, r):
    if (r == 0 or r == n): return 1
    return (comb(n-1, r-1) + comb(n-1, r))

num_tc = int(input())
for tc in range(1, num_tc+1):
    n, m = map(int, input().split())
    print(comb(n, m-1))