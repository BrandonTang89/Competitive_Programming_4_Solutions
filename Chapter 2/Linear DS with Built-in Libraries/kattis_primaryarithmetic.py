'''
Kattis - Primary Arithmetic

As this is a basically an adhoc problem, we use python as our "go to" language for fast coding with many different library functions (like reversing strings)

Time: O(num cases * num digits of larger number) Mem: O(num digits of larger number)

'''

import sys
for line in sys.stdin.readlines():
    lin = line[:-1]
    x = lin.split(" ")
    a = x[0]
    b = x[1]

    if a == '0' and b == '0':
        break

    # a smaller than b
    if int(a) > int(b):
        a,b = b,a

    a = str(a)
    b = str(b)

    a = a[::-1]
    b = b[::-1]

    for i in range(len(b) - len(a)):
        a += "0"
    
    a.split()
    a = [int(i) for i in a]
    b.split()
    b = [int(i) for i in b]

    cc = 0 # carry counter
    carry = 0
    for i in range(len(a)):
        carry = (a[i] + b[i] + carry)//10
        if carry != 0:
            cc+=1


    if (cc == 0):
        print("No carry operation.")
    elif (cc == 1):
        print("1 carry operation.")
    else:
        print(cc, "carry operations.")



    