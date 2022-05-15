'''
Kattis - divideby100
Use a list, deal with the cases where theres a leading 0. and theres no leading 0. Also deal with
any trailing zeros and the case where the answer is an integer (trailing .0000...0)

Time: O(n + m), Space: O(n + m)
'''
n = list(input())
m = len(input())-1

ans = []
for i in range(m):
    if (len(n) > 0):
        ans.append(n.pop())
    else:
        ans.append("0")
# print(ans)
if len(n) == 0:
    ans.append(".")
    ans.append("0")
else:
    ans.append(".")
    ans.extend(n[::-1])
    
while (ans[0] == "0"):
    ans.pop(0)
if ans[0] == ".":
    ans.pop(0)
    
ans = ans[::-1]
print("".join(ans))