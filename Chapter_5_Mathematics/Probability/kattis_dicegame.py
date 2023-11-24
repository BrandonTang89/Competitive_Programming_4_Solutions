'''
Kattis - dicegame
Straightforward expected value problem with linearity of expectation and symmetry.

Time: O(n^2), Space: O(1)
'''
def e(a1, b1, a2, b2):
    return (a1+b1)/2 + (a2+b2)/2

a1, b1, a2, b2 = map(int, input().split())
e1 = e(a1, b1, a2, b2)

a1, b1, a2, b2 = map(int, input().split())
e2 = e(a1, b1, a2, b2)

if e1 > e2:
    print("Gunnar")
elif e1 < e2:
    print("Emma")
else:
    print("Tie")