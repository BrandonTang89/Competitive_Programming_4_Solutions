'''
Kattis - absurdistan2
Probability. To be honest I needed to google for the solution for this :(
    
c(k) computes the number of connected graphs of size k
    The total number of graphs of size k is (k-1)^k
    The sum counts the number of disconnected graphs
        Index i is the size of the component containing node 1
        comb(k-1, i-1) chooses which of the nodes are in this component
        c(i) deals with how to arrange the component
        (k - i - 1)^(k - i) deals with how to arrange the remaining nodes

comb(n, k) computes the binomial coefficient n choose k
'''
from functools import lru_cache

@lru_cache(maxsize=None)
def comb(n, k):
    return 1 if k == 0 else 0 if n == 0 else comb(n-1, k) + comb(n-1, k-1)
@lru_cache(maxsize=None)
def c(k):
    return (k-1)**k - sum(c(i) * comb(k-1, i-1) * (k - i - 1)**(k - i) for i in range(2, k-1))

n = int(input())
print(c(n) / (n-1)**n)