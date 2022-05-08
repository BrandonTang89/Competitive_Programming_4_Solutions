'''
Kattis - base2plaindrome
Constructive problem about constructing base 2 palindromes. Esssentially notice that if we just count upwards
in binary and use that as the front of the palindrome, we can generate palindromes in a somewhat increasing
order. Issue is that we have both odd and even length palindromes, so we will generate palindromes of the
length 2n+1 while still generating palindromes of the length 2n, obviously those of the larger length
will be larger... So we just generate way more palindromes than needed so that at least the first 50k will
be generated.

Note that if we TLE, we can actually just use the pre-computation technique to generate the list of palindromes
offline then put that into our source code.

Time: O(1), Space: O(1)
'''
S = {1}
cur = 1
while (len(S) <= 80000):
    # Check if cur is a palindrome in base 2
    binrep = '{0:b}'.format(cur)
    S.add(int(binrep + binrep[::-1], 2))
    S.add(int(binrep + '0' + binrep[::-1], 2))
    S.add(int(binrep + '1' + binrep[::-1],2))
    cur += 1

S = sorted(list(S))

n = int(input())
print(S[n-1])