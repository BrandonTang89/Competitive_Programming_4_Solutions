'''
Kattis - sidewaysorting
Matrix transposition and stable sorting ignoring case. Python makes the solution pretty elegant.

Time: O(hw log w), Space: O(hw)
'''
while 1:
    h, w = map(int, input().split())
    if (h == 0 and w == 0): break
    arr = []
    for r in range(h):
        arr.append(list(input()))
    
    # Transpose
    arr = [*zip(*arr)]
    
    # Sort
    arr = [''.join(x) for x in arr]
    arr.sort(key=lambda x: x.lower())
    
    # Transpose back
    arr = [*zip(*arr)]
    arr = [''.join(x) for x in arr]
    
    for l in arr:
        print (l)

    print()