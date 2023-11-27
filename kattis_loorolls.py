'''
Kattis - loorolls
Mathy. Suppose we are taking k cm each time from roll i, then we are taking k-(l%k) from the next roll. 
Start with k=n and create more rolls until k=0.
Note that n is a variant which decreases by at least 1 each time so we are bounded by O(n) iterations.

Time: O(n), Space: O(1)
'''
ans = 1
l, n = map(int, input().split())
while l%n != 0:
    ans += 1
    n = n - (l%n)
print(ans)