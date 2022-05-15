'''
Kattis - turtlemaster
Relatively basic follow the instruction type of problem.

Time: O(len(commands), Space: O(len(commands))
'''
import sys
grid = [list(input()) for i in range(8)]

commands = input()

cur_pos = (7, 0)
cur_direction = (0, 1) # Facing right

bug = False
for c in commands:
    #print(c, cur_pos)
    if c == 'F':
        cur_pos = (cur_pos[0] + cur_direction[0], cur_pos[1] + cur_direction[1])
        if cur_pos[0] < 0 or cur_pos[0] > 7 or cur_pos[1] < 0 or cur_pos[1] > 7:
            bug = True
            break
        if grid[cur_pos[0]][cur_pos[1]] == 'C' or grid[cur_pos[0]][cur_pos[1]] == 'I':
            bug = True
            break
    elif c == 'L':
        # Turn left
        cur_direction = (-cur_direction[1], cur_direction[0])
    elif c == 'R':
        # Turn right
        cur_direction = (cur_direction[1], -cur_direction[0]) 
    
    elif c == 'X':
        # Fire laser at the position infront
        fire_pos = (cur_pos[0] + cur_direction[0], cur_pos[1] + cur_direction[1])
        if (grid[fire_pos[0]][fire_pos[1]] == 'I'):
            grid[fire_pos[0]][fire_pos[1]] = '.'
        else:
            bug = True
            break
    

if bug:
    print("Bug!")
    sys.exit()

if grid[cur_pos[0]][cur_pos[1]] == 'D':
    print("Diamond!")
else:
    print("Bug!")