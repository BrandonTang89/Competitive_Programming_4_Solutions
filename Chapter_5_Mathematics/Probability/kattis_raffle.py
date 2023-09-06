'''
Kattis - raffle
Relatively easy but mathy linear search. Let x be the number of raffle tickets we put.
Probability of exactly 1 being chosen is 
F = (x/x+n) * (n/x+n-1) * (n-1/x+n-2) * ... * (n-p+2/x+n-p+1) * P.
(with the + and - binding tighter than the / within each bracket for neatness).

We just try all values of x from [1..n], but we notice that we can update the value of F
is O(1) since a lot of the factors are actually repeated from one value of x to another.
Just do abit of math and you'll see.

Time: O(n), Space: O(1)
'''

n, p = map(int, input().split())

x = 1
F = p
for i in range(n-p+1, n+1):
    F /= (x+i)
    if i == n:
        F *= x
    else:
        F *= (i+1)
maxx = 1
maxF = F
for x in range(2, n+1):
    F /= (x+n)
    F *= (x+n-p)
    F *= (x/(x-1))
    if F > maxF:
        maxF = F
        maxx = x

print(maxF)
