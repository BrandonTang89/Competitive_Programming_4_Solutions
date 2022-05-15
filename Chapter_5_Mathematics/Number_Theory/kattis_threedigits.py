'''
Kattis - threedigits
A relatively strange question... We can't just keep the last 3 digits since that will give the wrong
answer at times. But again similar to the question on the last non-zero digit, we don't know how many
digits past the last non-zero digit to keep... So instead of doing math, we will binary search the
grader. If we keep too many digits, it will TLE, if we keep too few, it will WA. At a sliver in between,
we can find AC.

Time: O(n), Space: O(1)
'''
n = int(input())
x = 1

for i in range(1,n+1):
    x *= i
    while (x %10 == 0):
        x //= 10
    x %= 10000000000000

print(str(x)[-3:])