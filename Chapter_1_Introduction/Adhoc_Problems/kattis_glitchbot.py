'''
Kattis - glitchbot
Try changing each command, run a simulation for each time.

Time: O(n^2), Space: O(n)
'''
def simulate(cmds):
    pos = (0, 0)
    direction = (0, 1) # upwards
    
    for cmd in cmds:
        if cmd == "Forward":
            pos = (pos[0] + direction[0], pos[1] + direction[1])
        elif cmd == "Right":
            direction = (direction[1], -direction[0])
        elif cmd == "Left":
            direction = (-direction[1], direction[0])
    
    return pos

target = tuple(map(int, input().split()))
n = int(input())

cmds = []
for i in range(n):
    cmds.append(input())

possible_cmds = ["Forward", "Right", "Left"]
for i in range(n):
    # Try Changing i
    initial = cmds[i]
    for j in possible_cmds:
        if j != initial:
            cmds[i] = j
            pos = simulate(cmds)
            if pos == target:
                print(i + 1, j)
                exit()
            cmds[i] = initial