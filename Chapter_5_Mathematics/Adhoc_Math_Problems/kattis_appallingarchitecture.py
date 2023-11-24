'''
Kattis - appallingarchitecture
Straightforward, just calculate the x coordinate of the center of mass of the blocks and compare it to the x coordinate of the
left and right of the house.

Time: O(hw), Space: O(hw)
'''
h, w = map(int, input().split())

grid = [list(input()) for _ in range(h)]
totalBlocks = sum([sum([1 if grid[i][j] != '.' else 0 for j in range(w)]) for i in range(h)])

leftmost = w+1
rightmost = 0
for i in range(w):
    if grid[-1][i] != '.':
        leftmost = min(leftmost, i)
        rightmost = max(rightmost, i+1)

t = 0
for i in range(h):
    for j in range(w):
        if grid[i][j] != '.':
            t += (j+0.5)

t /= totalBlocks
if leftmost > t:
    print('left')
elif rightmost < t:
    print('right')
else:
    print('balanced')