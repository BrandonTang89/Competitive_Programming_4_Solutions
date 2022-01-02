'''
Kattis - fizzbuzz
The classic CS interview problem.

Time: O(n), Space: O(1)
'''
x, y, n = map(int, input().split())
for i in range(1, n+1):
    ans = ""
    if i % x == 0:
        ans += "Fizz"
    if i % y == 0:
        ans += "Buzz"
    if ans == "":
        ans = str(i)
    
    print(ans)