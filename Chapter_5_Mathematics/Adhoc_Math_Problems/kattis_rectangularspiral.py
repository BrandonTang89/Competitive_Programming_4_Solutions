'''
Kattis - rectangularspiral
Constructive kind of problem. Clearly when x < y we can do it by just going x to the right then going y up which is valid.

Next we consider what kind of points with x >= y we can do with just 6 segments. We let the first 3 segments be 1, 2, and 3 units
long (we will justify this later). Then suppose the 4th segment is n units long, the 5th segment will need to be
x+2 units long and the 6th segment n' will need to be y+n-2 units long. 

This gives the conditions: n < x + 2 < y + n -2 which can be converted into x-y+4 < n < x + 2 which means that n exists if and only if
y > 3 and we let n = x-y+5 to make the spiral as short as possible.

For y <= 3 can reason that it is impossible since |y| increases with each vertical segment and we have already tried either 2
or 6 segments which corresponds to 1 or 3 vertical segments so any more will have |y| > 3 which we can do better with the above
construction.

Now, suppose in the construction we try to vary the first 3 segments. We note that for each segment we extend, we will need to
extend the 4th 5th or 6th segments so this is unoptimal since we can already do all required points with the above construction.

The writeup is definitely handwavy but I'm tired

Time: O(1), Space: O(1)
'''
for _ in range(int(input())):
    t, x, y = map(int, input().split())
    
    if x < y:
        print(f"{t} 2 {x} {y}")
    elif y > 3: # x >= y
        n = x-y+5
        nprime = y+n-2
        print(f"{t} 6 1 2 3 {n} {x+2} {nprime}")
    else: # y <= 3
        print(f"{t} NO PATH")