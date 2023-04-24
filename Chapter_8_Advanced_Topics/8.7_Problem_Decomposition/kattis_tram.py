'''Kattis - tram
Univariate minimisation problem. We do some simple linear algebra to find the cost of a given value of a for
some specific point (x, y) to be 0.5 * (x - y - a)^2. Thus, we are looking to minimize the objective function 
f(a) = sum((x - y - a)^2) for all points (x, y).  
Observe that f is convex since it is the sum of convex functions so there is a single local minimum 
that is also the global minimum. We could use golden section search at this stage, but a simple ternary 
search will suffice (linear convergence as well) and it is faster to code.

Also you can just solve the equation analytically to find the single minimum lol.
Time: O(1), Space: O(1).
'''
n = int(input())
points = [map(int, input().split()) for _ in range(n)]
print(sum([y - x for x, y in points]) / n)

'''
points = [(x, y) for x, y in points]

def f(a):
    return sum([(x-y+a)**2 for x, y in points])

lo = -1e6
hi = 1e6

while hi - lo > 1e-6:
    m1 = lo + (hi - lo) / 3
    m2 = hi - (hi - lo) / 3
    if f(m1) < f(m2):
        hi = m2
    else:
        lo = m1

print("%.9f" % (lo))
'''
