'''
Kattis - odds
The probability part is rather easy, just get number of cases where A wins over total number of
cases to simulate. The more difficult part is the simulation with a variable number of variables
to simulate. Note the use of the ternary operator to simplify the code.

Time: O(7**4 per test case), Space: O(1)
'''

from fractions import Fraction
def a_wins(a1, a2, b1, b2):
    if ( (b1, b2) == (1, 2) or (b1, b2) == (2, 1) ):
        return False
    if ( (a1, a2) == (1, 2) or (a1, a2) == (2, 1) ):
        return True

    type_a = 1 if a1 == a2 else 0
    type_b = 1 if b1 == b2 else 0
    if (type_b == 1 and type_a == 0):
        return False
    if (type_a == 1 and type_b == 0):
        return True
    if (type_a == 1 and type_b == 1):
        return a1 > b1
    
    a = int(str(max(a1, a2)) + str(min(a1, a2)))
    b = int(str(max(b1, b2)) + str(min(b1, b2)))
    return a > b
    
while (True):
    a1, a2, b1, b2 = input().split()
    if (a1 == '0' and a2 == '0' and b1 == '0' and b2 == '0'): break 
    num_sim = (a1 == "*") + (a2 == "*") + (b1 == "*") + (b2 == "*")
    denom = 6**num_sim
    
    num = 0
    for i in range(1, 7) if a1 == "*" else range(int(a1), int(a1)+1):
        for j in range(1, 7) if a2 == "*" else range(int(a2), int(a2)+1):
            for k in range(1, 7) if b1 == "*" else range(int(b1), int(b1)+1):
                for l in range(1, 7) if b2 == "*" else range(int(b2), int(b2)+1):
                    num += a_wins(i, j, k, l)
                    
    print(Fraction(num, denom))