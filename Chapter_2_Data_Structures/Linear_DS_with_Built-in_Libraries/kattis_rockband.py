'''
Kattis - rockband
Simply loop through the positions and add all the songs at that position to a hashset. If the hashset is the same size as the position (+1)
Then it means that all the musicians like all the same songs up to that position, so we can stop there. Think about why this works.

Time: O(hw), Space: O(hw)
'''
h, w = map(int, input().split())
arr = [list(map(int, input().split())) for _ in range(h)]

s = set()
for c in range(w):
    for r in range(h):
        s.add(arr[r][c])
        
    if (len(s) == c + 1):
        print(c+1)
        print(' '.join(map(str, sorted(list(s)))))
        exit()