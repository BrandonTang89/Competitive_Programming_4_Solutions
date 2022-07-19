'''
Kattis - cantor
Consider the input x and how to find its representation in base 3.
Notice x = a0*3^-1 + a1*3^-2 + a2*3^-3 + ..., Observe then that 3x = a0 + a1*3^-1 + a2*3^-2 + ...
And we can thus extract a0. We can repeat this process for the remaining digits. Until we start repeating
digits. Note the edge case of x == 1. I have no proof for this, but I believe it is correct to suggest that
finite floats in decimal correspond to infinitely recurring floats in ternary and vice versa... 

Time: O(?), Space: O(1)'''
while 1:
    x = input()
    if (x == "END"):
        break

    x = float(x)
    if (abs(x - 1.0) < 1e-12):
        print("MEMBER")
        continue
    y = x

    x *= 3
    is_member = int(x) != 1
    x = x - int(x)

    while (abs(x - y) > 1e-9 and is_member):
        x *= 3
        is_member = int(x) != 1
        x = x - int(x)

    print("MEMBER" if is_member else "NON-MEMBER")
