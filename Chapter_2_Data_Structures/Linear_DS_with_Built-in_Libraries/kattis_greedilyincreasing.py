'''
Kattis - greedilyincreasing
Very easy greedy problem.

Time: O(n), Space: O(n)
'''
n = int(input())
arr = list(map(int, input().split()))
ans = []

for i in arr:
    if (len(ans) == 0 or ans[-1] < i):
        ans.append(i)

print(len(ans))
print(*ans)

