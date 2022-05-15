'''
Kattis - thebackslashproblem

This problem is pretty simple. Notice that the number of backslashes is just 2**n -1. This is because
for each next level of indentation, the number of backslashes is doubled and + 1 for each special
char.

Honestly the hardest part about this was reading in input until EOF. I don't know if this is the best
way but I read all the input first and used a 2 step for loop to read the input for each testcase...

Time: O(length of input), Space: O(length of input)
'''
def is_special(c):
    if (ord(c) >= ord('!') and ord(c) <= ord('*')):
        return True
    if (ord(c) >= ord('[') and ord(c) <= ord(']')):
        return True
    
    return False

from sys import stdin
lines = stdin.readlines()
for line_num in range(0,len(lines),2):
    n = int(lines[line_num])

    n_slashes = 2**n - 1
    s = lines[line_num+1].strip()
    a = ""
    for c in s:
        if (is_special(c)):
            a += '\\'*n_slashes
        
        a += c
    
    print(a)