'''
Kattis - blackout
We start by blocking off 1 row, then we are left with a 4x6 grid, notice that both lengths are even! So what we can do
is to mirror the moves of the opponent on both axes and then we will definitely win!s

Time: O(1), Space: O(1)'''
num_tc = int(input())
for _ in range(num_tc):
    print("5 1 5 6", flush=True)
    
    while True:
        move = input()
        if (move == "GAME"): break
        move = move.split()[1:]
        move = [int(x) for x in move]
        
        if (move[2] == 5):
            move[2] = 4 # pretend the last row is not there
        
        move[0] = 5-move[0]
        move[2] = 5-move[2]
        move[1] = 7-move[1]
        move[3] = 7-move[3]
        
        if (move[0] > move[2]):
            move[0], move[2] = move[2], move[0]
        elif (move[1] > move[3]):
            move[1], move[3] = move[3], move[1]
        
        print("{} {} {} {}".format(move[0], move[1], move[2], move[3]), flush=True)