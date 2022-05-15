'''
Kattis - froggie
Just as expected of a time waster problem. Many small bugs to debug. One easy trick is to 
generate cars that are yet to come. How much to generate? We should generate such that the
further away car from the screen has no chance of getting into the screen, ie generate
until -w or 2*w (depending on the direction of traffic). Also note that since we reverse
the cars array, whether the traffic flow is left or right depends on whether h is even or odd.
We also need a special consideration for 0 speed cars since we cannot pass through where they
previously were.

Time & Space complexity - not relevant.
'''
h, w = map(int, input().split())
cars = [[] for i in range(h)]
for i in range(h):
    offset, interval, speed = map(int, input().split())
    if i&1:
        speed = -speed
        offset = w-1 - offset
        for pos in range(offset, -1, -interval):
            cars[i].append((pos, interval, speed))
        for pos in range(offset+interval, 2*w+2, interval):
            cars[i].append((pos, interval, speed))
        
    else:
        for pos in range(offset, w, interval):
            cars[i].append((pos, interval, speed))
        for pos in range(offset - interval, -w-2, -interval):
            cars[i].append((pos, interval, speed))
    cars[i].sort()
cars = cars[::-1]

frog_c, cmds = input().split()
frog_c = int(frog_c)
frog_pos = (-1, frog_c)

for cmd in cmds:
    # print(frog_pos, cmd, " -> ", end="")
    if cmd == 'L':
        frog_pos = (frog_pos[0], frog_pos[1]-1)
    elif cmd == 'R':
        frog_pos = (frog_pos[0], frog_pos[1]+1)
    elif cmd == 'U':
        frog_pos = (frog_pos[0]+1, frog_pos[1])
    else: # D
        frog_pos = (frog_pos[0]-1, frog_pos[1])
    # print(frog_pos)
    # Update all the cars
    for lane in range(h):
        new_lane = []
        for car in cars[lane]:
            
            if frog_pos[0] == lane:
                if car[2] == 0:
                    if car[0] == frog_pos[1]:
                        print("squish")
                        exit()
                else:
                    if (lane & 1 == (h & 1)):
                        for i in range(1, -car[2]+1):
                            if car[0] - i == frog_pos[1]:
                                print('squish')
                                exit()
                    else:
                        for i in range(1,car[2]+1):
                            if car[0] + i == frog_pos[1]:
                                print('squish')
                                exit()
                            
            new_car = (car[0] + car[2], car[1], car[2])
            if new_car[0] < 2*w+2 and new_car[0] >= -w-2:
                new_lane.append(new_car)
                
        new_lane.sort()
        if lane & 1 == (h & 1):
            offset, interval, speed = new_lane[-1]
            for pos in range(offset+interval, 2*w+2, interval):
                new_lane.append((pos, interval, speed))
        else:
            offset, interval, speed = new_lane[0]
            for pos in range(offset - interval, -w-2, -interval):
                new_lane.append((pos, interval, speed))
        new_lane.sort()
        
        cars[lane] = new_lane

if frog_pos[0] < h:
    print("squish")
else:
    print("safe")