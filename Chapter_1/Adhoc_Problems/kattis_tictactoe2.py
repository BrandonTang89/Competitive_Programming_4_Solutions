'''
Kattis - tictactoe
Implicit graph. We do BFS from the starting empty board, stopping propagation when we encounter
a win or a draw.

Time: O(n), Space: O(1)
'''
possible_boards = set()
base = "........."
q = []
q.append(base)
possible_boards.add(base)

while len(q) > 0:
    b = q.pop(0)
    
    # Check for horizontal tictactoe win
    if b[0] == b[1] == b[2] != ".":
        continue
    if b[3] == b[4] == b[5] != ".":
        continue
    if b[6] == b[7] == b[8] != ".":
        continue
    
    # Check for vertical tictactoe win
    if b[0] == b[3] == b[6] != ".":
        continue
    if b[1] == b[4] == b[7] != ".":
        continue
    if b[2] == b[5] == b[8] != ".":
        continue
    
    # Check for diagonal tictactoe win
    if b[0] == b[4] == b[8] != ".":
        continue
    if b[2] == b[4] == b[6] != ".":
        continue
    
    # Check for draw
    if "." not in b:
        continue
    
    # Check for possible moves
    # Determine current player (O or X), X starts first
    cur_player = "X" if b.count('X') == b.count('O') else "O"
    
    # Check for possible moves
    for i in range(9):
        if b[i] == ".":
            new_board = list(b)
            new_board[i] = cur_player
            new_board = "".join(new_board)
            if new_board not in possible_boards:
                q.append(new_board)
                possible_boards.add(new_board)

n = int(input())
for i in range(n):
    board = [input() for i in range(3)]
    if i != n-1: input()
    board = "".join(board)
    
    print("yes" if board in possible_boards else "no")