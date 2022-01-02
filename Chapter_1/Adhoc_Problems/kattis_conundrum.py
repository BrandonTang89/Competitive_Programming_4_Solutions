'''
Kattis - conundrum
Super basic question.

Time: O(n), Space: O(n)
'''
s = input()
ans = 0
per = "PER"
for i, c in enumerate(s):
    ans += not(c == per[i % 3])
print(ans)