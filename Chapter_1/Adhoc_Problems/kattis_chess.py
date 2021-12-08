'''
Kattis - chess
Adhoc problems are very annoying, I dislike them. They are simple yet tedious.

Time: O(1), Space: O(1) since the chess board dimensions are fixed
'''

num_tc = int(input())
dc = [1, 1, -1, -1]
dr = [1, -1, 1, -1]
for _ in range(num_tc):
    c1, r1, c2, r2 = input().split()
    c1 = ord(c1) - ord('A')
    r1 = int(r1) - 1
    c2 = ord(c2) - ord('A')
    r2 = int(r2) - 1

    board = [[(-1, -1)] * 8 for i in range(8)]
    board[r1][c1] = (8, 8)

    done = False
    if (r1 == r2) and (c1 == c2):
        print(f"0 {chr(c1 + ord('A'))} {r1 + 1}")
        done = True
    if not done:
        for i in range(4):
            r = r1
            c = c1
            while 1:
                r += dr[i]
                c += dc[i]
                if (r >= 0 and r < 8 and c >= 0 and c < 8):
                    board[r][c] = (r1, c1)
                    if (r == r2 and c == c2):
                        print(
                            f"1 {chr(c1 + ord('A'))} {r1 + 1} {chr(c2 + ord('A'))} {r2 + 1}")
                        done = True
                        break
                else:
                    break

    if not done:
        for i in range(4):
            if (done):
                break
            r = r1
            r = r2
            c = c2
            while 1:
                r += dr[i]
                c += dc[i]
                if (r >= 0 and r < 8 and c >= 0 and c < 8):
                    if (board[r][c] != (-1, -1) and (not((r1, c1) == (r, c)))):
                        print(
                            f"2 {chr(c1 + ord('A'))} {r1 + 1} {chr(c + ord('A'))} {r + 1} {chr(c2 + ord('A'))} {r2 + 1}")
                        done = True
                        break
                else:
                    break
    if not done:
        print("Impossible")