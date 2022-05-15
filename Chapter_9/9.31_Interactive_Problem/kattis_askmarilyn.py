'''
Kattis - askmarilyn
Monty hall but abit modified, also interactive. Effectively we are betting that we select the wrong door initially,
this occurs 2/3 of the time, then if she opens the bottle, go there, else swap. Either way, we get the bottle. But if we
select the right door initially, we're gonna lose that bottle.

Time: O(1), Space: O(1)'''
from random import choice
doors = ['A','B','C']
for _ in range(1000): # 1000 reounds
    inital = choice(doors)
    print(inital, flush=True)
    
    res = input()
    res = res.split()
    
    if res[1] == '1':
        print(res[0], flush=True)
    else:
        for door in doors:
            if door != res[0] and door != inital:
                print(door, flush=True)
                break
    
    res = input()