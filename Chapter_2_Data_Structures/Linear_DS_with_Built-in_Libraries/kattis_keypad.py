'''
Kattis - keypad
Logical thinking mostly.
Time: O(hw), Space: O(hw)
'''
tc = int(input())
for _ in range(tc):
    h, w = map(int, input().split())
    grid = [list(input()) for _ in range(h)]
    
    onRows = set()
    onCols = set()
    
    for r in range(h):
        for c in range(w):
            if grid[r][c] == '1':
                onRows.add(r)
                onCols.add(c)
    
    isDone = False
    for r in range(h):
        for c in range(w):
            if r in onRows and c in onCols and grid[r][c] == '0':
                isDone = True
                break
        if isDone:
            break
    
    if isDone:
        print("impossible\n----------")
        continue
    
    for r in range(h):
        for c in range(w):
            if (grid[r][c] == '0'): print('N', end='')
            else:
                if len(onRows) == 1 or len(onCols) == 1: print('P', end='')
                else: print('I', end='')
        print()
    print("----------")
    