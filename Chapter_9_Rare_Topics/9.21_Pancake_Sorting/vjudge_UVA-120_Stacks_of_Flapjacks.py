'''vjudge - UVA-120 - stacks of flapjacks
Pancake sorting, greedy version. Python is great at these adhoc problems.

Time: O(n), Space: O(n)'''
from sys import stdin
for line in stdin:
    line = line.strip()
    s = [int(x) for x in line.split()]
    inv = {e: i for i, e in enumerate(sorted(s))}

    s = [inv[x] for x in s]
    n = len(s)
    print(line)
    
    for i in range(len(s)-1, -1, -1):
        for j in range(i+1):
            if s[j] == i:
                pos = j
                break
        if (pos == i):
            continue # already at bottom
        
        if (pos != 0): # not at top, flip to top
            print(n-pos, end = ' ')
            s = s[:pos+1][::-1] + s[pos+1:]
            
        print(n-i, end=' ')
        pos = i
        s = s[:pos+1][::-1] + s[pos+1:]
        
    print(0)