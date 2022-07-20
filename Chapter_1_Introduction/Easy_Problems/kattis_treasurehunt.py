'''
Kattis - treasurehunt
Easy enough question, just simulate and keep track of whether we revist a node.

Time: O(hw), Space: O(hw)
'''
h, w = map(int, input().split())
grid = [list(input()) for _ in range(h)]

past = set()
r = 0
c = 0
x = 0
while 1:
    if (grid[r][c] == 'T'):
        print(x)
        exit()
    
    if ((r, c) in past): 
        print("Lost")
        exit()
    
    past.add((r, c))
    if (grid[r][c] == 'E'):
        c += 1
    elif (grid[r][c] == 'N'):
        r -= 1
    elif (grid[r][c] == 'S'):
        r += 1
    elif (grid[r][c] == 'W'):
        c -= 1
    
    if (r < 0 or r >= h or c < 0 or c >= w):
        print("Out")
        exit()
    
    x += 1
