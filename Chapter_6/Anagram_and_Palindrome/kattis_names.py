'''
Kattis - names
Simple to implement, but requires some prior thinking. Notice that the upper bound on the length
of the eventual string is n + n/2 because any more than that, we might as well change half of s
to be palindromic. Now for each k in the range of n to 3/2 n, we try making s into a k length
palindrome.

We can actually extend s with a bunch of dummy "_"s since the cost of a mismatch is equal to 
the cost of an addition of a character. Then we just check the number of mismatches in the string.

Time: O(n^2), Space: O(n)
'''
s = input()
n = len(s)

s += "_"*n
ans = n # default number of operations by just changing everything
for i in range(n, n + n//2 +1): # we try to get a palindrome of length i
    cur = 0
    for j in range(i//2):
        if (s[j] != s[i-1-j]):
            cur += 1
    ans = min(ans, cur)
print(ans)