'''
Kattis - equations
A tedious question! Ensure to craft all test cases (with 4, 3, 2, 1, 0 zeros) when testing the code!
Use Fraction library, else it would be much worse...

Time: O(num symbols), Space: O(num symbols)
'''
num_tc = int(input())
from fractions import Fraction
for tc in range(num_tc):
    if (tc > 0): 
        _ = input()
        print()

    eqs = ["",""]
    eqs[0], eqs[1] = input(), input()

    for i in range(2):
        eqs[i] = eqs[i].split()
        # print(eqs[i])
        
        cx = cy = ct = 0
        past_equals = False
        neg = False
        for j in range(len(eqs[i])):
            c = eqs[i][j]
            if (c == '='):
                past_equals = True
                continue
            elif (c == '+'):
                continue
            elif (c == '-'):
                neg = True
                continue
            
            if c[-1] == 'x':
                if (c == "x"): c = "1x"
                elif (c == "-x"): c = "-1x"
                cx += (-1 if neg else 1) * (-1 if past_equals else 1) * int(c[:-1])
            elif c[-1] == 'y':
                if (c == "y"): c = "1y"
                elif (c == "-y"): c = "-1y"
                cy += (-1 if neg else 1) * (-1 if past_equals else 1) * int(c[:-1])
            else:
                ct += (-1 if neg else 1) * (1 if past_equals else -1) * int(c)
                
            neg = False
            
        eqs[i] = [Fraction(cx), Fraction(cy), Fraction(ct)]
        
    # Checks
    impossible = False
    useless = False
    
    yset = xset = 0
    y = x = 0
    for i in range(2):
        cx = eqs[i][0]
        cy = eqs[i][1]
        ct = eqs[i][2]
        if (cx == 0 and cy == 0 and ct != 0): impossible = True
        if (cx == 0 and cy == 0 and ct == 0): useless = True
        
        if (cx == 0 and cy != 0):
            if (yset != 0):
                if y == ct / cy:
                    yset -= 1
                    useless = True
            yset += 1
            y = ct / cy
        if (cy == 0 and cx != 0): # mutually exclusive to above
            if (xset != 0):
                if x == ct / cx:
                    xset -= 1
                    useless = True
            xset += 1
            x = ct / cx
        
    if (impossible):
        print("don't know\ndon't know")
        continue
    
    if (yset + xset == 2 or useless): # either both equations set somehting, or theres infinite solutions
        if (xset == 1): # x is set
            print(x)
        else:
            print("don't know")
        
        if (yset == 1):
            print(y)
        else:
            print("don't know")
        continue
    
    if (yset == 1): # the other equation is not useless or x/y setting
        for i in range(2):
            cx = eqs[i][0]
            cy = eqs[i][1]
            ct = eqs[i][2]
            if (cx != 0):
                x = (ct - cy * y) / cx
                break
        print(x)
        print(y)
        continue
    elif (xset == 1): # the other equation is not useless or x/y setting
        for i in range(2):
            cx = eqs[i][0]
            cy = eqs[i][1]
            ct = eqs[i][2]
            if (cy != 0):
                y = (ct - cx * x) / cy
                break
        print(x)
        print(y)
        continue
    
    # No more zeros in coefficients!
    cx0, cy0, ct0 = eqs[0][0], eqs[0][1], eqs[0][2]
    cx1, cy1, ct1 = eqs[1][0], eqs[1][1], eqs[1][2]
    
    factor = cx0 / cx1
    
    if (cy0 / cy1 == factor): # parallel
        print("don't know")
        print("don't know")
        continue
    
    # else we gaussian elimination
    cx1 = cx1 * factor
    cy1 = cy1 * factor
    ct1 = ct1 * factor
    
    y = (ct1 - ct0) / (cy1 - cy0)
    x = (ct0 - cy0 * y) / cx0    
    
    print (x)
    print (y)