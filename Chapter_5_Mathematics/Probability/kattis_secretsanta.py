'''
Kattis - secretsanta
Kinda cool combination of theory and practice for calculating 1 - d(n)/n! where d(n) is the number of derangements of n.
We use the principle of inclusion and exclusion to derive the formula for d(n) = n! * (1/2! - 1/3! + 1/4! - ... + (-1)^n * 1/n!)
Then clearly our invariant should not be i! but 1/i! since this prevents python from doing big integer calculations.
We also note that the terms get smaller quite fast and so we can stop at n = 100.

Time: O(n), Space: O(1)
'''
n = int(input())
oneoverifac = 0.5
ans = 0
for i in range(2,min(100, n+1)):
    # inv: oneoverifac = 1/i!
    ans += (-1 if i&1 else 1) * oneoverifac
    oneoverifac /= (i+1)

print(1 - ans)