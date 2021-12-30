'''
Kattis - battleship
Really annoying problem again. Very vague problem statement, lots of reading comprehension.

Time: O(n), Space: O(1)
'''
num_tc = int(input())

for tc in range(num_tc):
    w, h, n = map(int, input().split())

    p0 = [list(input()) for i in range(h)]
    p1 = [list(input()) for i in range(h)]

    cur_player = 0
    last_turn = False
    moves_processed = 0
    while moves_processed < n:
        # Start turn
        while moves_processed < n:
            c, r = map(int, input().split())
            moves_processed += 1
            r = h-1 - r
        
            cur_board = p1 if cur_player == 0 else p0 # Shoot each other's board
        
            if cur_board[r][c] == '#':
                cur_board[r][c] = '_'
                sc = ''.join([''.join(row) for row in cur_board])
                if sc.count('#') == 0:
                    break
            else:   
                break
        
        if last_turn: break
        
        # Check wins
        sp0 = ''.join([''.join(row) for row in p0])
        sp1 = ''.join([''.join(row) for row in p1])
        
        if cur_player == 1 and sp0.count('#') == 0:
            break
        elif cur_player == 0 and sp1.count('#') == 0:
            # Give player one another turn
            last_turn = True
        
        cur_player = 1 - cur_player
    # print("ignored", n - moves_processed)
    for i in range(n - moves_processed): input()

    p0 = ''.join([''.join(row) for row in p0])
    p1 = ''.join([''.join(row) for row in p1])
    
    #pprint(p0)
    #pprint(p1)
    if not p0.count('#') and not p1.count('#'):
        print('draw')
    elif p0.count('#') and p1.count('#'):
        print('draw')
    elif p0.count('#'):
        print('player one wins')
    else:
        print('player two wins')
    