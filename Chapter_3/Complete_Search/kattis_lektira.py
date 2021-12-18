'''
Kattis - lektira

Relatively easy complete search problem. Use string slicing and reversing.
Time: O(n^3), Space: O(n)
'''
s = input()
n = len(s)

cur_min = s
for i in range(1, n-1):
    for j in range(i+1, n):
        a = s[0:i]
        b = s[i:j]
        c = s[j:n]
        
        new_s = a[::-1] + b[::-1] + c[::-1]
        cur_min = min(cur_min, new_s)

print(cur_min)