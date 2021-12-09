'''
Kattis - workout
Tedious time based problem.. Spend time analyzing the time_until_can_start function, consider the
cases correctly.

Time: O(1), Space: O(1)
'''
x = list(map(int, input().split()))
jusage = [i for i in x[::2]]
jrecovery = [i for i in x[1::2]]


others = [] # [usage, recovery, time_used_machine]
for i in range(10):
    others.append(list(map(int, input().split())))
    
current = 0
t = 0

def time_until_can_start(index):
    machine = others[index]
    x = t - machine[2] # time since started using
    if (x < 0):
        # max of time to start j finishing
        machine[2] = max(machine[2], t + jusage[index])
        return 0 # can start immediately
    x %= (machine[0] + machine[1])
    if (x < machine[0]): # using at the moment
        # machine[0] - x is the amount of time left for the person to finish
        # we get the max of time for person to finish followed by j to finish and
        # time for the person to finish and then recover
        machine[2] = max(jusage[index] + machine[0] - x + t, machine[0] - x + machine[1] + t)
        return machine[0] - x
    else:
        # max of time for j to finish and person to recover
        machine[2] = max(jusage[index] + t, t + machine[0] + machine[1] - x)
        return 0
    
while (current < 30):
    t += time_until_can_start(current%10)
    t += jusage[current%10] + jrecovery[current%10]
    current += 1

t -= jrecovery[9]

print(t)