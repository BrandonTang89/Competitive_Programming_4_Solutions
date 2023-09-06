'''
Kattis - redsocks
Another kinda mathy problem. We are trying to find r, b such that r/(r+b) * (r-1)/(r+b-1) = p/q.

We can rearrange this to get b = ((1-2r) + sqrt((2r-1)^2 + 4r(r-1)(q/p-1))/2
So now we can check if each value of r results in a valid b in O(1). However, getting this
check programmed without floating point errors is non-trivial. We note that we need to ensure
4r(r-1)(q/p-1) is an integer and then ensure (2r-1)^2 + 4r(r-1)(q/p-1) is a perfect square then
ensure ((1-2r) + sqrt((2r-1)^2 + 4r(r-1)(q/p-1)) is even...

Now, we can linear search all values of r, then check if there is a corresponding valid b,
and also take care of the edge cases of p==q and p==0.
Time: O(50000), Space: O(1)
'''
def D(r):
    a = 4*r*(r-1)*q
    if a % p != 0:
        return -1
    return (2*r-1)**2 + a//p - 4*r*(r-1)

def isSquare(n):
    if n == -1: return False
    return int(n**0.5 + 0.4)**2 == n

while True:
    p, q = map(int, input().split())
    
    if p == 0 and q == 0:
        break

    if p == 0:
        print("0 2")
        continue
    if p == q:
        print("2 0")
        continue

    for r in range(2, 50001):
        d = D(r)
        if isSquare(d):
            num = (1-2*r + int(d**0.5 + 0.4))
            if num%2 == 1: continue
            b = num//2
            assert (b >= 0)
            if (r + b > 50000): continue
            assert (r*(r-1)*q == p*(r+b)*(r+b-1))
            
            print(r, b)
            break
    
    else:
        print("impossible")