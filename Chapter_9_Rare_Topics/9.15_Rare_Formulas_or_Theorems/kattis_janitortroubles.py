'''
Kattis - janitortroubles
Refer to https://byjus.com/maths/area-of-quadrilateral/, notice that the area of a random 
quadrilateral is sqrt((s-a)(a-b)(s-c)(s-d) - abcd cos^2(theta/2)) where theta is the sum of 2
opposite angles in the quadrilateral. Notice that given a, b, c, d we can maximise this area
by setting theta = 180 (ie a cyclic quadrilateral).

Time: O(1), Space: O(1)
'''
a, b, c, d = map(int, input().split())
s = (a + b + c + d) /2  
print(((s - a) * (s - b) * (s - c) * (s - d)) ** 0.5)