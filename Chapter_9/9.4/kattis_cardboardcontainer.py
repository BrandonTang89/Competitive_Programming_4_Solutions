'''
Kattis - cardboardcontainer
We just need to make the key observation that V=LWH and thus at least 2 of L,W,H must be
<= sqrt(v). From there, we can bruteforce.

Time: O(v), Space: O(1)
'''
v = int(input())
sqrtv = int((v**0.5))+1

def surface_area(l, w, h):
    return 2*l*w + 2*w*h + 2*h*l

ans = 1e10
for l in range(1, sqrtv):
    for w in range(1, sqrtv):
        if (v%(l*w) == 0):
            ans = min(ans, surface_area(l, w, v//(l*w)))

print(ans)