'''
Kattis - tetris
Relatively boring question. The best it does is encourage efficient coding, I'd like to think what I did was
mostly minimal.
Time: O(c), Space: O(c)
'''
x = {
    1: {
        (0, 0, 0, 0),
        (0,) # interestingly, we do this to avoid making this an int (would like a tuple)
    },
    2: {
        (0, 0)
    },
    3: {
        (0, 0, 1),
        (0, -1),
    },
    4: {
        (0, -1, -1),
        (0, 1)
    },
    5: {
        (0, 0, 0),
        (0, 1),
        (0, -1, 0),
        (0, -1)
    },
    6: {
        (0, 0, 0),
        (0, 0),
        (0, 1, 1),
        (0, -2)
    },
    7: {
        (0, 0, 0),
        (0, 2),
        (0, 0, -1),
        (0, 0),
    }
}
c, p = map(int, input().split())
a = list(map(int, input().split())) + [-100 for i in range(5)] # padding avoid dealing with edges

ans = 0
for i in range(c):
    for req in x[p]:
        if a[i] == req:
            ans += 1

        fine = True
        for j in range(i, i + len(req)):
            if (a[j] - req[j - i]) != a[i]:
                fine = False
                break
        if fine:
            ans += 1
print(ans)
