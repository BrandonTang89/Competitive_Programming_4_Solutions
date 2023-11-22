'''
Kattis - sheldon
Like many other questions of this type, we tackle the subproblem of finding the number of sheldon numbers under a certain bound:
    define f(q) which returns the number of sheldon numbers <= q
    
All sheldon numbers are of the form
y = (2^n - 1) * (2^m) * (1 + 2^(n+m) + 2^(2(n+m)) + ... + 2^((k)(n+m))) / (d) for some n > 0, m > 0, k >= 0, d in {1, 2^m}
We notice that since our queries are always less than 2^63, we can just iterate through all possible
values of (n, m, k, d) where n, m, k <= 63 and check if y <= q.

It is possible to have overlapping answers so we use a hashset to store the unique solutions. Since the total number of tuples (n, m, k, d)
is O(64^3 * 2), this set will not take up too much memory. The rest of the problem is just implementing this such that we can check each
(n, m, k, d) in O(1) by the use of accumulating parameters.

Time: O(64^3 * 2), Space: O(64^3 * 2)
'''
def f(q):
    seen = set()
    for n in range(1, 64):
        for m in range(1, 64):
            x = ((1 << n) - 1) << m     # x = (2^n - 1) * 2^m
            y = x                       # sheldon number
            z = x                       # z = x * 2^(k(n+m))
            for k in range (0, 64):
                if y <= q:              # d = 1
                    seen.add(y)
                if y >> m <= q:         # d = 2^m
                    seen.add(y >> m)
                else: 
                    break
                
                z <<= (n+m)             # z *= 2^(n+m)
                y += z                  # next sheldon number 

    return len(seen)

a, b = map(int, input().split())
print(f(b) - f(a - 1))
                