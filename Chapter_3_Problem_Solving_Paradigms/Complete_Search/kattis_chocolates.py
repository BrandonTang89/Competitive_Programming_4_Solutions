'''
Kattis - chocolates
Pre-computable complete search problem. Since the input space is small (16), we can compute all the values
first. Notice that there are 2 check to check if a placing of chocolates forms a polygon: first we check 
if the chocolates are a single connected component in terms of 4 directional flood fill. Then we check
if the all the non-chocolate cells are reachable from the edges of the box in terms of 8 directional
flood fill. Doing both is sufficient.

Time: O(1), Space: O(1)
'''
'''
def check_polygon(h: int, w: int, p: int):
    if (p == 0): return False # not a polygon if it doesn't exist
    source = (-1, -1)
    board = []
    for r in range(h):
        board.append([])
        for c in range(w):
            board[r].append(0)
            board[r][c] = 1 if ((1 << r*w+ c) & p) else 0
            if (source == (-1, -1) and board[r][c]): source = (r, c)
    
    #for r in range(h):
        #print(board[r])

    # All the chocolates should be in 1 connected component
    # print("source", source)
    q = [source]
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    visited = [[False for _ in range(w)] for _ in range(h)]
    visited[source[0]][source[1]] = True
    while (len(q)):
        r, c = q.pop()
        for i in range(4):
            nr = r + dr[i]
            nc = c + dc[i]
            if (nr < 0 or nr >= h or nc < 0 or nc >= w): continue
            if (visited[nr][nc]): continue
            if (board[nr][nc]):
                q.append((nr, nc))
                visited[nr][nc] = True
    
    for r in range(h):
        for c in range(w):
            if ((not visited[r][c]) and board[r][c]): return False

    # print("passed first check")
    # Ensure that all the non-chocolates are connected to the edges
    q = []
    dr = [0, 1, 0, -1, 1, 1, -1, -1]
    dc = [1, 0, -1, 0, 1, -1, 1, -1]
    visited = [[False for _ in range(w)] for _ in range(h)]
    
    for r in range(h):
        if (not board[r][0]): q.append((r, 0))
        if (not board[r][w-1]): q.append((r, w-1))
    for c in range(1, w-1):
        if (not board[0][c]): q.append((0, c))
        if (not board[h-1][c]): q.append((h-1, c))
    
    for r, c in q:
        visited[r][c] = True
    
    while (len(q)):
        r, c = q.pop()
        for i in range(8):
            nr = r + dr[i]
            nc = c + dc[i]
            if (nr < 0 or nr >= h or nc < 0 or nc >= w): continue
            if (visited[nr][nc]): continue
            if (board[nr][nc]): continue
            q.append((nr, nc))
            visited[nr][nc] = True

    for r in range(h):
        for c in range(w):
            if (not visited[r][c] and not board[r][c]): return False
    
    return True

answer_matrix = [[0 for w in range(4)] for h in range(4)]


for h in range(4):
    for w in range(4):
        for p in range(1 << ((h+1)*(w+1))):
            if (check_polygon(h+1, w+1, p)): answer_matrix[h][w] += 1
print(answer_matrix)
'''
# print(check_polygon(4, 4, 0b1111100111100000))
answer_matrix = [[1, 3, 6, 10], [3, 13, 40, 108], [6, 40, 217, 1109], [10, 108, 1109, 10977]]
    
h, w = map(int, input().split())
print(answer_matrix[h-1][w-1])