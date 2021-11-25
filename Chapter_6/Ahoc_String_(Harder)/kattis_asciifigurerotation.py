'''
Kattis - asciifigurerotation
One of those annoying adhoc problems with funky output formatting. Just fiddle around for a while to
get the solution. Note that we needed to strip all trailing white space from each line and we need
to put a newline between edge test case but not at the end of all testcases.

Time: O(n*max_len), Space: O(n*max_len)
'''
# from pprint import pprint

def modify_char(c):
    if (c == '|'): return '-'
    if (c == '-'): return '|'
    return c

tc = 0
while 1:
    n = int(input())
    if (n == 0): break
    fig = [list(input()) for _ in range(n)]
    
    max_width = max(map(len, fig))
    for i in fig:
        if (len(i) < max_width):
            i += [" "] * (max_width - len(i))
    
    # pprint(fig)
    # for i in fig:
    #    print("".join(i))
    
    rotated_fig = [[] for _ in range(max_width)]
    for i in range(max_width):
        for j in range(n-1,-1,-1):
            rotated_fig[i].append(modify_char(fig[j][i]))
            
    # pprint(rotated_fig)
    if (tc != 0): print()
    tc += 1
    for i in rotated_fig:
        print(("".join(i)).rstrip())