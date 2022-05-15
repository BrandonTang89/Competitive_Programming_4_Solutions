'''
Kattis - empleh
Again relatively simple input parsing and output formatting. Easy to get the right answer, thus
the focus is more on how to do it efficiently and neatly. My answer to which is using lots of
list comprehension and ternary operators.

Rememeber to handle the case where there are no white / black inputs

Time: O(1), Space: O(1)
'''

try:
    d, white = input().split()
except:
    white = ""
white = white.upper().split(",")
white = ['P' + e if len(e) == 2 else e for e in white]

try:
    d, black = input().split()
except:
    black = ""

black = black.lower().split(",")
black = ['p' + e if len(e) == 2 else e for e in black]

board = [[":"]*8 for _ in range(8)]

for e in white:
    if e == '': continue
    r = 8 - int(e[2]);
    c = ord(e[1]) - ord('A')
    board[r][c] = e[0]
for e in black:
    if e == '': continue
    r = 8 - int(e[2]);
    c = ord(e[1]) - ord('a')
    board[r][c] = e[0]

for i in range(len(board)):
    board[i] = [":"+e+":" if (j+i)%2==1 else '.'+e+'.' for j,e in enumerate(board[i])]
    board[i] = ["..." if e == ".:." else e for e in board[i]]
    board[i] = "|" + "|".join(board[i]) + "|"

print("+---+---+---+---+---+---+---+---+")
for i, row in enumerate(board):
    print(row)
    print("+---+---+---+---+---+---+---+---+", end = "\n" if i != 7 else "")