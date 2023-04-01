# Kattis - drmmessages
# Just do it!
# Time: O(n), Space: O(n)
s = input()
a = s[:len(s)//2]
b = s[len(s)//2:]

r1 = sum([ord(a[i]) - ord('A') for i in range(len(a))])
a = [chr((ord(a[i]) - ord('A') + r1)%26 + ord('A')) for i in range(len(a))]

r2 = sum([ord(b[i]) - ord('A') for i in range(len(b))])
b = [chr((ord(b[i]) - ord('A') + r2)%26 + ord('A')) for i in range(len(b))]

c = [chr((ord(a[i]) - ord('A') + ord(b[i]) - ord('A'))%26 + ord('A')) for i in range(len(a))]
print(''.join(c))