'''
Kattis - accessdenied
Quite a fun problem, actually real life applicable. We should first study the time taken given {wrong length, 0 correct letters, 1 correct letters, ...}
to develop a formula for determining the case. We can do this by printing stuff to the given testing tool.

Theres 2 phases, detecting the right length, then detecting the right letters. The first is done by printing a string
of increasing length. The second is done by trying all possible symbols for the firrst letter, once we get 1 correct
letter then we try for the second one, etc until we are done.

The most annoying thing is just that we can't try invalid symbols, so we need to check if we get it right early
and thus exit cleanly.

Time: O(n), Space: O(n)
'''

# First we find how many letters there are
def get_time(res):
    x = res.split(" ")
    if (len(x) == 2):
        return -1 # finished
    return int(x[-2][1:])

def num_correct(t):
    if (t == -1): return -1
    return (t-14)//9

cur = 0
s = "a"
while cur != 14:
    print(s, flush=True)
    cur = get_time(input())
    if (cur == -1): exit()
    s += "a"

n = len(s)-1

# All upper and lowercase letters and digits
chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

s = list(s[:-1])
for i in range(n-1):
    for c in chars:
        s[i] = c
        print(''.join(s), flush=True)
        x = num_correct(get_time(input()))
        if (x == -1):
            exit()
        if x >= i+1:
            break

def getGranted(res):
    return res.split(" ")[-1] == "GRANTED"

for c in chars:
    s[n-1] = c
    print(''.join(s), flush=True)
    if getGranted(input()):
        exit()