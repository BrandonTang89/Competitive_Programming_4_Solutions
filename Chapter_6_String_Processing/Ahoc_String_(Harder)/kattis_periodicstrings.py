'''
Kattis - periodicstrings
Complete search all divisors of the length of the string and check if they are eligible
to be the periods.

Time: O(n^2), Space: O(n)
'''
s = input()
n = len(s)
for i in range(1, n +1):
    if (n % i):
        continue
    
    p = s[:i]
    s_copy = s
    
    possible = True
    while (len(s_copy) > 0):
        if (not s_copy.startswith(p)):
            possible = False
            break
        s_copy = s_copy[i:]
        p = p[-1] + p
        p = p[:-1]
    if (possible):
        print(i)
        break