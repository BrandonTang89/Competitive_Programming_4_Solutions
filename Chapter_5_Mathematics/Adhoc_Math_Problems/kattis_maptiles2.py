'''
Kattis - maptiles2
This is a pretty adhoc problem, just read the description and realise that its something like doing
binary addition where each level down is half the size of the previous level. Fiddle around with it
and you'll get the answer.

Time: O(len(s)), Space: O(1)
'''
s = input()
level = len(s)
x, y = 0, 0
for index, c in enumerate(s):
    c = int(c)
    if c == 1  or c == 3:
        x += 2**(level-index-1)
    if c == 2 or c == 3:
        y += 2**(level-index-1)

print(level, x, y)