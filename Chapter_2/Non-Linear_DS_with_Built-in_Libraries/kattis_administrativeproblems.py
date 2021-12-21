'''
Kattis - administrativeproblems
Mostly reading comprehension and just being careful. Can be done with a balanced BST in C++ but Python
is more convenient here and the time is not that tight.

Time: O(num_spies log num_spies + n log num_spies), Space: O(n + num_spies)
'''
from math import ceil
num_tc = int(input())
for _ in range(num_tc):
    n, m = map(int, input().split()) # number of cars, number of events
    cars = {}
    state = {}
    cost = {}
    for i in range(n):
        car, catalog, pick_up, cost_per_km = input().split()
        catalog = int(catalog)
        pick_up = int(pick_up)
        cost_per_km = int(cost_per_km)
        
        cars[car] = (catalog, pick_up, cost_per_km)
    
    
    for event in range(m):
        t, spy, e, x = input().split()
        if not spy in state:
            state[spy] = None
            cost[spy] = 0
        
        if cost[spy] == -1:
            continue # Spy is inconsistent already
        
        if e == "p":
            # Ensure state = None
            if state[spy] != None:
                cost[spy] = -1
                continue
            
            state[spy] = x
            cost[spy] += cars[x][1]
            
        elif e == "r":
            if state[spy] == None: # Spy must be in a car
                cost[spy] = -1
                continue
            cost[spy] += int(x) * cars[state[spy]][2]
            state[spy] = None
        elif e == "a":
            if state[spy] == None: # Spy must be in a car
                cost[spy] = -1
                continue
            cost[spy] += ceil(int(x)*cars[state[spy]][0]/100)
            
    for spy in state:
        if state[spy] != None:
            cost[spy] = -1
    
    arr = [(spy, cost[spy]) for spy in cost]
    arr.sort()
    
    for spy, c in arr:
        print(spy, end=" ")
        if c == -1:
            print("INCONSISTENT")
        else:
            print(c)