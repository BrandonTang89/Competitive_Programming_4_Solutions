'''
Kattis - apaxiaaans
I fail to see why anyone would use regex for something like this. Just use a for loop bruh.

Time: O(n), Space: O(n)
'''
x = input()
ans = ""
for i in range(len(x)):
    if (i != len(x) - 1):
        if (x[i + 1] == x[i]):
            continue
    ans += x[i]
print(ans)