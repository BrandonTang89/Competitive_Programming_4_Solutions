'''
Kattis - permcode
Time waster problem. Just slowly reverse the information given in the question. 
We rely on that fact that a ^ (a ^ b) = b to recover the ps and pp arrays.
A lot of potential for confusion with all the arrays (s, p, c). 
Not that fun, yet not even trivial.

Time: O(n * sn), Space: O(n + sn)
'''
while True:
    x = int(input())
    if x == 0:
        break
    s = input()
    p = input()
    c = input()
    sn = len(s)
    n = len(c)
    m = ['' for _ in range(n)]

    d = int(n**1.5 + x) % n
    posins = 0
    for i in range(sn):
        if s[i] == c[d]:
            posins = i
            break

    # posins is the same as the position of m[d] in p
    m[d] = p[posins]
    y = [-1] * n  # y[j] = position of m[j] in p ^ position of m[j+1%n] in s
    for j in range(n):
        if j == d:
            continue
        for i in range(sn):
            if s[i] == c[j]:
                y[j] = i
                break

    # position of m[d] in p == posins
    pp = [0] * n  # pp[j] = position of m[j] in p
    pp[d] = posins
    ps = [0] * n  # ps[j] = position of m[j] in s
    for i in range(sn):
        if m[d] == s[i]:
            ps[d] = i
            break

    for j in range(d-1, -1, -1):
        pp[j] = y[j] ^ ps[(j+1) % n]
        m[j] = p[pp[j]]
        for i in range(sn):
            if m[j] == s[i]:
                ps[j] = i
                break

    for j in range(n-1, d, -1):
        pp[j] = y[j] ^ ps[(j+1) % n]
        m[j] = p[pp[j]]
        for i in range(sn):
            if m[j] == s[i]:
                ps[j] = i
                break

    print(''.join(m))
