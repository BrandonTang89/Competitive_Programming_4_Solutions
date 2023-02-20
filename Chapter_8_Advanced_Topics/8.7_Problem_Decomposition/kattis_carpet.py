
# Kattis - carpet
# BSTA + Mathematics. Possibly my least legit solve ever. First I set up the triangle in the coordinate plane with A at (0, 0),
# B at (l/2, sqrt(3)*l/2) and C at (0, l) for any length of triangle l that we are trying. Then I calculate the position of S
# soley based on a and c. I then increase l if S is too near to B and decrease l if S is too far from B. 
#
# This basic idea is correct. The issue comes in finding a starting bracket for l. The one I used has quite a loose lower bound
# However, playing with the values in a graphing calculator shows that it is good enough to ensure we don't converge on a wrong
# answer (like the point S being outside the triangle and too far from B but we decrease l further and further).
# 
# The next issue is that we still might not have a solution even if ri >= le. The exact classes of not having solutions were too
# difficult for me to comprehend, so I made the assuption that if we converge at a answer where S is still not within 1e-9 of the
# correct distance from B, then we don't have a solution. I'm not sure if this is indeed true, but it ACs on kattis
# 
# Time: O(500), Space: O(1)

a, b, c = map(float, input().split())
ri = min(a+b, b+c, c+a)
le = max(a, b, c)


def dist(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return ((x1-x2)**2 + (y1-y2)**2)**0.5


if (ri < le):
    print(-1)
else:
    closeEnuf = False
    for _ in range(500):
        l = (le+ri)/2
        cx = (l*l-c*c+a*a)/(2*l)
        cy = (a*a - cx*cx)**0.5

        if (dist((cx, cy), (l/2, (3)**0.5/2*l)) < b):
            le = l
        else:
            ri = l

        if (abs(dist((cx, cy), (l/2, (3)**0.5/2*l)) - b) < 1e-9):  # check forward error
            closeEnuf = True

    if (closeEnuf):
        print(l*l*(3**0.5)/4)
    else:
        print(-1)
