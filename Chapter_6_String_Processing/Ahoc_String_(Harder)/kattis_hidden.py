'''
Kattis - hidden
We opt to try using regular expressions. Note the importance of the \A (and sometimes \Z) to ensure
no erroneous matches are made.

Time: O(n), Space: O(n)
'''
p, x = input().split()
import re
s = "\A"                   # \A = start of string
for i,c in enumerate(p):
    s += f"[^{p[i:]}]*{c}" # any amount of any char exept the ones up to and including the current char
                           # followed by current char

print("PASS" if re.search(s, x) != None else "FAIL")