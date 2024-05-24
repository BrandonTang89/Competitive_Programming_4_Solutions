'''
CF1974D
Another easy problem that is just annoying to implement.
Clearly if the total movement on any axis is odd it is impossible
Now if there is some net movement on any axis, we can just move the H to that directly and the rover will do whatever is left
Otherwise, we try to move the H away from the origin then back, with the R doing the rest. But it could be that R doesn't move, which would be impossible
'''
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(input())
    
    N = len([i for i in a if i == 'N'])
    S = len([i for i in a if i == 'S'])
    E = len([i for i in a if i == 'E'])
    W = len([i for i in a if i == 'W'])
    
    if abs(N-S)%2 == 1: 
        print("NO")
        continue
    
    if abs(E-W)%2 == 1:
        print("NO")
        continue
    
    moves = ['R'] * n
    
    netV = (N-S)//2
    netH = (E-W)//2
    Hy = 0
    Hx = 0
    if netV != 0 or netH != 0:
        for i in range(n):
            if Hy < netV and a[i] == 'N':
                moves[i] = 'H'
                Hy += 1
            if Hy > netV and a[i] == 'S':
                moves[i] = 'H'
                Hy -= 1
            if Hx < netH and a[i] == 'E':
                moves[i] = 'H'
                Hx += 1
            if Hx > netH and a[i] == 'W':
                moves[i] = 'H'
                Hx -= 1
        print(*moves, sep='')
        continue
            
    if N > 0:
        # first N and S should be H
        doneS = False
        doneN = False
        for i in range(n):
            if a[i] == 'N' and not doneN:
                moves[i] = 'H'
                doneN = True
            if a[i] == 'S' and not doneS:
                moves[i] = 'H'
                doneS = True
    else:
        # first E and W should be V
        doneE = False
        doneW = False
        for i in range(n):
            if a[i] == 'E' and not doneE:
                moves[i] = 'H'
                doneE = True
            if a[i] == 'W' and not doneW:
                moves[i] = 'H'
                doneW = True
    
    if not 'R' in moves:
        print("NO")
        continue
    print(*moves, sep='')