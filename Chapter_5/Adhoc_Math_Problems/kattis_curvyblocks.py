'''
Kattis - curvyblocks
This is a somewhat long question I will have to say. Not too algorithmically challenging, but
gotta think abit mathematically.

First, we need to find out where the blocks meet. 
    This is done by first taking the difference in polynomials and then finding the x value of the
    minimum in the valid bounds of [0, 1].
    To do this, we compute the derivative of the polynomial and get the roots to get our candidate
    gobal x values. Then we check which of [0, r1, r2, 1] is the minimum. Note that r1 and r2 might
    not be real and should thus be ignored if complex. They also might not be within the valid bounds.

Secondly, we modify the polynomial by translating it along the y axis such that at the x value of 
where the blocks meet, the y value is 0.
    This is done by subtracting the y value of the minima to poly[0] which is the constant term.
    
    This modified polynomial now represents the distance between the 2 blocks between 0 and 1, being
    0 where they touch. 

Now we gotta find the max distance between the 2 blocks, ie the maxima of the modified polynomial. 
    Note that the modified polynomial is actually just a vertical translation of the original polynmial,
    meaning that the candidate global x values are the same. Thus we don't need to compute the derivative
    and roots again.

    Now, we just let ans be max of the y values of the modified polynomial at [0, r1, r2, 1], checking
    if r1 and r2 are valid.


Time: O(1), Space: O(1)
'''
from sys import stdin
lines = stdin.readlines()

def compute_third_deg_poly(poly, x):
    return poly[0] + poly[1]*x + poly[2]*x**2 + poly[3]*x**3

for line_num in range(0,len(lines),2):
    bottom = list(map(float, lines[line_num].strip().split()))
    top = list(map(float,lines[line_num+1].strip().split()))
    
    poly = [top[i] - bottom[i] for i in range(len(bottom))]

    # Differentiate the polynomial
    diffed_poly = []
    for i in range(len(poly)):
        diffed_poly.append(i*(poly[i]))
    diffed_poly.pop(0)

    [c, b, a] = diffed_poly

    # Get Quadratic Roots
    r1 = (-b + (b**2 - 4*a*c)**0.5)/(2*a)
    r2 = (-b - (b**2 - 4*a*c)**0.5)/(2*a)

    # print(diffed_poly)
    # print(r1, r2)

    # Determine where the 2 blocks meet
    arr = [float(0), r1, r2, float(1)]
    meet_x = 1000000
    meet_y = 1000000
    for x in arr:
        if (type(x) != float): # complex roots
            continue
        if (x < float(0) or x > float(1)): # out of bounds
            continue
        if (compute_third_deg_poly(poly, x) < meet_y):
            meet_x = x
            meet_y = compute_third_deg_poly(poly, x)
    # print(meet_x)

    # Determine the answer
    poly[0]-= meet_y # get modified polynomial
    ans_x = 0
    ans_y = 0
    for x in arr:
        if (type(x) != float): # complex roots
            continue
        if (x < float(0) or x > float(1)): # out of bounds
            continue
        if (compute_third_deg_poly(poly, x) > ans_y):
            ans_x = x
            ans_y = compute_third_deg_poly(poly, x)
    print(ans_y)