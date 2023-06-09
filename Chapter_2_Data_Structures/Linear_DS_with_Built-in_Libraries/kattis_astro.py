'''
Kattis - astro
The problem we are trying to solve is: find the smallest k, m >= 1 such that a + kx = b + my. 
This corresponds to the both stars flashing after the first star flashes k times and the
second flashes m times. This problem could get annoying fast if we attempt to use math to solve this.

Fortunately, we observe that by reformulating the problem as targ = (a-b) = (my-kx) = cur, we can 
iteratively modify cur by adding y or subtracting x until we reach targ. Proof by induction:
at each stage, we cannot make targ with any m' < m or k' < k. Then if we my-kx != targ, we need
to increase either m or k. Clearly we need to increase m if my-kx < targ and increase k if my-kx > targ.
Doing this will ensure we find the smallest m and k that satisfy the equation.

Now, there might not actually be a solution to the problem. We can detect this by checking if we encounter
any cycle during our iterative search. If so, we know that we will just keep going in the cycle forever.
The max size of the graph is O(y + x) nodes. By pigeon hole principle, we will terminate either by getting
a cycle of getting to target after O(y + x) iterations.

The rest of the stuff is just converting between time and minutes. As well we dealing with the day and
formatting. Generic stuff.

Time: O(y + x), Space: O(y + x)
'''
ah, am = map(int, input().split(':'))
a = ah * 60 + am
bh, bm = map(int, input().split(':'))
b = bh * 60 + bm

xh, xm = map(int, input().split(':'))
x = xh * 60 + xm
yh, ym = map(int, input().split(':'))
y = yh * 60 + ym

day = {
    0: 'Saturday',
    1: 'Sunday',
    2: 'Monday',
    3: 'Tuesday',
    4: 'Wednesday',
    5: 'Thursday',
    6: 'Friday'
}
s = set()
targ = a - b
cur = y - x
k = 1
while cur not in s:
    s.add(cur)
    if cur == targ:
        t = k*x + a
        print(day[(t//1440) % 7])
        print(str((t//60) % 24).zfill(2), str(t % 60).zfill(2), sep=':')
        exit()

    if cur < targ:
        cur += y
    else:
        cur -= x
        k += 1

print('Never')
