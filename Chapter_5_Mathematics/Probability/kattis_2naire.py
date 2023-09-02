'''
Kattis - 2naire
Non-trivial probability, relatively easy recurrence to implement once you're done.
Let X be the earnings.
E(X | won n questions) = 2^n
E(X | won k questions) = 1/(1-t) integral_t^1(E(X | probability of winning is P, won k questions) dp)
                       = 1/(1-t) integral_t^1(max(2^k, P*E(X | won k+1 questions)) dp)
               
let q = E(X | won k+1 questions)        
At pcut == 2^k / q, 2^k = pcut*q so we can split the integral into two parts:
E(X | won k questions) = 1/(1-t) (integral_t^pcut(2^k dp) + integral_pcut^1(pq dp))
                       = 1/(1-t) (2^k(pcut - t) + q/2 (1 - pcut^2)))

Note it is possible for pcut < t, in which case we only have the second part of the integral:
E(X | won k questions) = 1/(1-t) (q/2 (1 - t^2)))
Time: O(n), Space: O(1)
'''
def ewonx(k):
    if k == n:
        return 2**n
    q = ewonx(k+1)
    pcut = 2**k / q

    if pcut < t:
        return (1/(1-t)) * (q/2 * (1-t**2))
    return (1/(1-t)) * (2**k * (pcut - t) + q/2 * (1 - pcut**2))


while True:
    n, t = input().split()
    if n == '0' and t == '0':
        break
    n = int(n)
    t = float(t)
    print("{:.3f}".format(round(ewonx(0), 3)))