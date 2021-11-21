''' Kattis - dragondropped
An interactive cycle finding problem. This is annoying because
1. its an interactive problem so its hard to debug
2. the constraints are kinda tight

The key observation is that in this case, we don't need to know mu. After doing the first phase of Floyd's cycle finding algorithm, we already
know how many steps it takes to get into the cycle to that position. From there, we just move around the cycle to determine lambda. Using the
information on how many steps left after getting into the position where the tortise and hare meet, we can get the number of steps to take to get
into the final position.

Time: O(mu + lambda*3 = mu + lambda)
Space: O(1)
'''

import sys
from sys import stdout
n = int(input())
tor_counter = 0
hare_counter = 0

def move_tor():
    global tor_counter
    tor_counter += 1
    
    print("NEXT SPIKE")
    stdout.flush()
    okay, same_place = map(int, input().split())
        
    if (tor_counter) == n:
        print("ASK SPIKE")
        stdout.flush()
        sys.exit()

    return okay, same_place


def move_hare():
    global hare_counter
    hare_counter+= 1 

    print("NEXT GABBY")
    stdout.flush()
    okay, same_place = map(int, input().split())
    
    if (hare_counter) == n:
        print("ASK GABBY")
        stdout.flush()
        sys.exit()
        
    return okay, same_place

def reset_hare():
    global hare_counter
    hare_counter = 0
    print("RETURN GABBY")
    stdout.flush()
    okay, same_place = map(int, input().split())

# Move both at once
x = 0
while (1):
    move_tor()
    move_hare()
    okay, same_place = move_hare()
    x += 1
    
    if same_place == 1:
        break # i = k * lambda
    
# Get lambda
l = 0
while (1):
    okay, same_place = move_hare()
    l += 1
    if same_place == 1:
        break
    
# Go to the end
num_steps = (n-x)%l
for i in range(num_steps):
    move_hare()
    
print("ASK GABBY")
stdout.flush()