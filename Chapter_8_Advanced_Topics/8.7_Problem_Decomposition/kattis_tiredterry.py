# Kattis - tiredterry
# Basically adhoc, do a sliding window kind of thing. Add back the first p elements to the end of 
# the string to also consider periods that wrap around the end of the string.
# Time: O(n), Mem: O(n)
n, p, d = map(int, input().split())

sp = input()
sp = sp + sp[:p-1]
ans = 0
num_sleep = sum([1 for i in sp[:p] if i == 'Z'])
for i in range(p-1, len(sp)-1):
    if num_sleep < d:
        ans += 1

    num_sleep -= 1 if sp[i-p+1] == 'Z' else 0
    num_sleep += 1 if sp[i+1] == 'Z' else 0

if num_sleep < d:
    ans += 1
print(ans)
