'''
Kattis - allaboutthatbase
A relatively simple problem in python (could be do able in c++ but seems like much more work)

Essentially just test all 36 bases and see if each of them work, code could be better designed with use of eval(exp)

Time: O(t), Mem: O(1)
'''

t = int(input())

for tc in range(t):
    (a, op, b, dummy, c) = tuple(input().split())
    ans = ""
    # print("list set, ",list(set(a)))
    if list(set(a)) == ['1'] and list(set(b)) == ['1'] and list(set(c)) == ['1']:
        a_converted = len(a)
        b_converted = len(b)
        c_converted = len(c)

        if op == "+":
            if a_converted + b_converted == c_converted:
                ans += "1"
        elif op == "-":
            if a_converted - b_converted == c_converted:
                ans += "1"
        elif op == "*":
            if a_converted * b_converted == c_converted:
                ans += "1"
        elif op == "/":
            if a_converted / b_converted == c_converted:
                ans += "1"

    # Try the rest of the bases
    for base in range(2,36+1):
        try:
            a_converted = int(a, base)
            b_converted = int(b, base)
            c_converted = int(c, base)
        except:
            continue

        if base < 10:
            str_base = str(base)
        elif base == 36:
            str_base = "0"
        else:
            str_base = chr(ord('a') + base-10)

        if op == "+":
            if a_converted + b_converted == c_converted:
                ans += str_base
        elif op == "-":
            if a_converted - b_converted == c_converted:
                ans += str_base
        elif op == "*":
            if a_converted * b_converted == c_converted:
                ans += str_base
        elif op == "/":
            if a_converted / b_converted == c_converted:
                ans += str_base
    
    if ans == "":
        ans = "invalid"
    print(ans)