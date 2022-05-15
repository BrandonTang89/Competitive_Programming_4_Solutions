'''
Kattis - ornaments
Draw a proper diagram and then do some highschool mathematics. 

Time: O(1), Space: O(1)
'''
while 1:
    r, h, s = map(int, input().split())
    if r == 0 and h == 0 and s == 0:
        break
    
    from math import pi as PI
    from math import acos
    ans = 2*(h**2 - r**2)**0.5
    theta = acos(r/h)
    ans += (2*PI - 2*theta) * r
    ans *= (1 + s/100)
    ans = round(ans, 2)
    ans = "{:.2f}".format(ans)
    print(ans)