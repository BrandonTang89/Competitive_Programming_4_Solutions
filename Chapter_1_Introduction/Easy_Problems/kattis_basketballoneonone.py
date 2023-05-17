'''
Kattis - basketballoneonone
Simple.

Time: O(n), Space: O(n)
'''
m = {'A': 0, 'B': 0}
a = input()
for (p, s) in zip(a[::2], a[1::2]):
    m[p] += int(s)

print('A' if m['A'] > m['B'] else 'B')