'''
Kattis - connectthedots
Kinda a time waster problem. Just follow the instructions, at each dot, try all 4 directions 
and note if we find a direction that works. If theres no such direction, thats the end.

Time: O(num dots * max(height, width)), Space: O(height * width)
'''
from sys import stdin
lines = stdin.readlines()

lines.append("\n")

dc = [1, -1, 0, 0]
dr = [0, 0, 1, -1]
ordering = list("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") # Dummy ending
while len(lines) > 0:
    img = []
    while(lines[0] != "\n"):
        img.append(list(lines.pop(0).strip()))
    lines.pop(0)

    h, w = len(img), len(img[0])
    
    # Detect the 0
    for r in range(h):
        for c in range(w):
            if img[r][c] == '0':
                cr, cc = r, c
                break
    
    ordering_index = 0
    while True:
        #print(ordering_index)
        correct_dir = None
        for i in range(4):
            nr = cr
            nc = cc
            
            while nr >= 0 and nr < h and nc >= 0 and nc < w:
                if img[nr][nc] == ordering[ordering_index+1]:
                    correct_dir = i
                    break
                
                nr += dr[i]
                nc += dc[i]
            
            if correct_dir is not None:
                break
        
        if correct_dir is None:
            break
    
        nr = cr
        nc = cc
        nr += dr[correct_dir]
        nc += dc[correct_dir]
        while nr >= 0 and nr < h and nc >= 0 and nc < w:
            if img[nr][nc] == ordering[ordering_index+1]:
                cc, cr = nc, nr
                break
            
            correct_symbol = '|' if correct_dir >= 2 else '-'
            inverse_symbol = '|' if correct_dir < 2 else '-'
            if img[nr][nc] == '.':
                img[nr][nc] = correct_symbol
            elif img[nr][nc] == inverse_symbol:
                img[nr][nc] = '+'
            
            nr += dr[correct_dir]
            nc += dc[correct_dir]
        ordering_index += 1    
    
    for r in range(h):
        print(''.join(img[r]))
    print()