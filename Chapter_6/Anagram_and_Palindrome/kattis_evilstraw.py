'''
Kattis - evilstraw
problem looks easy, but it is annoying and tedious. We need to first determine if the string is an
anagram of a palindrome, then deal with the annoying middle character if it the string is odd in length.

We use recursion to make life easier.
If the left and right most chars are the same, we can only consider making s[1:n-1] a palindrome.
We try to move the most right char equal to the most left char to the most right position. 
However, if the left most char is the middle char, then we might have no other equal char to move into 
the rightmost position. In this case, we reverse the string and continue as per usual. Note that the 
reverse operation should only be done once ever.

Time: O(n^2), Space: O(n)
'''
num_tc = int(input())
from collections import Counter
def can_be_palindrome(s):
    c = Counter(list(s))

    ans = 0
    key = -1
    for k, f in c.items():
        if (f % 2 == 1):
            ans += 1
            key = k
            if (ans > 1):
                return (False, -1)
            
    for index, c in enumerate(s):
        if (c == key):
            return (True, index) # Can be Palindrome, with middle char
    
    return (True, -1) # No middle Character

def solve(s, middle_char):
    # print(s , middle_char)
    n = len(s)
    if (s[0] == s[n - 1]):
        return (s[1:n-1], 0)
    
    if (s[0] == middle_char):
        s.reverse()
       
    ans = 0
    cur_char = s[0]
    for j in range(n-1, 0, -1):
        if s[j] == cur_char:
            for k in range(j, n-1):
                s[k], s[k+1] = s[k+1], s[k]
                ans += 1
            break
    return (s[1:n-1], ans)
    
for _ in range(num_tc):
    s = input()
    possible, index = can_be_palindrome(s)
    mc = s[index]
    if (not possible):
        print("Impossible")
        continue
    
    total = 0
    s = list(s)
    while (len(s) > 1):
        s, ans = solve(s, mc)
        total += ans
        
    print(total)