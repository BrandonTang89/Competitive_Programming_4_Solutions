'''
Kattis - traffic
One of those annoying implementation issues
I tried to do it the legit O(n) method but it was annoying. So heres a simulation that is O(max t) but still ACs
Time: O(max t), Mem: O(n)
'''
xs = list(map(int, input().split()))
t1s = map(int, input().split())
t2s = map(int, input().split())
x1 = xs[0]
x2 = xs[1]
if (x1 > x2):
    x1, x2 = x2, x1
    t1s, t2s = t2s, t1s
    
t1s = list(t1s)[1:]
t2s = list(t2s)[1:]

pos = x2 - x1 - 4
t1 = len(t1s)
t2 = len(t2s)
i1, i2 = 0, 0
moving1, moving2 = False, False
t = 0
while t <= 3e6:
    if i1 < t1 and t1s[i1] == t:
        moving1 = not moving1
        i1 += 1
    if i2 < t2 and t2s[i2] == t:
        moving2 = not moving2
        i2 += 1
    if moving1:
        pos -= 1
    if moving2:
        pos += 1
        
    if pos <= 0:
        print('bumper tap at time {}'.format(t+1))
        exit()
    
    t += 1
print('safe and sound')