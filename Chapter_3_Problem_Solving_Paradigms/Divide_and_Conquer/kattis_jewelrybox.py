'''
Kattis - jewelrybox
Can be solved with ternary search. Or pen and paper differentiation.

TimeL: O(1), Space: O(1)
'''
tc = int(input())
for _ in range(tc):
    x, y = map(int, input().split())
    h = ((x+y - (x*x + y*y - x*y)**0.5)/6)
    
    print((x-2*h)*(y-2*h)*h)