'''
Kattis - skijumping
Simple binary search + some mechanics. Note we can avoid dealing with vectors if we just consider the
gradient of h and f.

Time: O(1) Mem: O(1)
'''
from math import atan
tc = int(input())
g = 9.81
pi = 3.141592653589793238462643383279502884197169399375105820974944
for _ in range(tc):
    j, p, H, L = map(float, input().split())

    v0 = (2*g*j)**0.5

    def h(l: float):
        assert (l >= 0)
        if l < L/2:
            return H * (1 - (2 * ((l / L)**2)))
        elif l < L:
            return 2*H*(l/L - 1)**2
        return 0

    def f(l: float):
        assert (l >= 0)
        return (-g/2.0 * (l/v0)**2 + H + p)

    l = 0
    r = 1e6

    for _ in range(100):
        m = (l + r) / 2
        if f(m) > h(m):  # go further
            l = m
        else:
            r = m

    vl = (2*g*(j+p+H-h(l)))**0.5
    eps = 1e-6
    gradf = (f(l+eps) - f(l-eps)) / (2*eps)
    gradh = (h(l+eps) - h(l-eps)) / (2*eps)

    angle = abs(atan(gradf) - atan(gradh))*180 / pi
    print(l, vl, angle)
