'''
Kattis - juryjeopardy
Actually quite a cool problem. Here we just keep track of the movement, expanding the maze on the fly.
Note that
1. we dont need to insert any column on the left since it is gauranteed that theres only 1 hole
which is the entrance on the left
2. if we insert a row on the top, we need to update the pos since the absolute position of the player
has changed

Also using Github Copilot makes the decision on how to change direction super easy... It's almost unfair.

Time complexity: O(n^2), Space: O(n^2) where n is the input size. The worse case scenario is when the
player moves diagonally to the upper right or bottom right.
'''
num_tc = int(input())
print(num_tc)
for _ in range(num_tc):
    path = input()
    maze = [
        ['#', '#', '#'],
        ['.', '#', '#'],
        ['#', '#', '#']
    ]
    pos = [1, 0]
    direction = [0, 1]


    def update_maze(pos):
        maze[pos[0]][pos[1]] = '.'
        if (pos[0] == 0):
            maze.insert(0, ['#'] * len(maze[0]))
            pos = [1, pos[1]]   
        if (pos[0] == len(maze) - 1):
            maze.append((['#'] * len(maze[0])))
        if (pos[1] == len(maze[0]) - 1):
            for i in maze:
                i.append('#')
        return pos

    for m in path:
        if (m == 'R'):
            direction = [direction[1], -direction[0]]
        elif (m == 'L'):
            direction = [-direction[1], direction[0]]
        elif (m == 'B'):
            direction = [-direction[0], -direction[1]]
        
        pos = [pos[0] + direction[0], pos[1] + direction[1]]
        pos = update_maze(pos)

    print(len(maze), len(maze[0]))
    for i in maze:
        print("".join(i))