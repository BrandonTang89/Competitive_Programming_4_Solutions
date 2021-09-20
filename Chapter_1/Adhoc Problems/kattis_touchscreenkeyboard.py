'''
kattis - touchscreenkeyboard
A basic adhoc problem that is made more optimised by precomputation
Even more optimised form of the code involves computing the lpos dict in one run and then hardcoding it for submission

Time: O(T(n len(sug) + n log n)), Mem: O(n)
'''
# Precompute letter positions
row1 = "qwertyuiop"
row2 = "asdfghjkl"
row3 = "zxcvbnm"

lpos = {}
for j,row in enumerate([row1,row2, row3]):
    for i,l in enumerate(row):
        lpos[l] = (j, i)

def l_distance(a, b):
    x1, y1 = lpos[a]
    x2, y2 = lpos[b]
    return (abs(x1-x2) + abs(y1-y2))

T = int(input())
for t in range(T):
    original, n = input().split()
    n = int(n)
    
    words = []
    for k in range(n):
        sug = input()
        dist = 0
        for i in range(len(sug)):
            dist += l_distance(sug[i], original[i])

        words.append((dist, sug))
    
    words.sort()

    for dist, sug in words:
        print(sug, dist)