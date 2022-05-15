'''
Kattis - otpor
This recursive parser is not exactly the most efficient since it needs to iterate over the entire string
to find where to recurse. But it was more interesting to code compared to the stack based parser.

Time: O(n^2), Space: O(n)
'''
n = int(input())
r = list(map(float, input().split()))
x = input()

def parse(s, e):
    # print(s, e)
    if (s + 1 == e): # base case
        return r[int(x[e]) -1]
    
    nest_counter = 0
    for i in range(s, e):
        if (x[i] == '('):
            nest_counter += 1
        elif (x[i] == ')'):
            nest_counter -= 1
        elif (nest_counter == 0):
            if (x[i] == '-'):
                return parse(s, i-1) + parse(i+1, e)
            elif (x[i] == '|'):
                a = parse(s, i-1)
                b = parse(i+1, e)
                return (a*b)/(a+b)
    return parse(s+1, e-1) # the whole expression is in a big bracket

print(parse(0, len(x)-1))