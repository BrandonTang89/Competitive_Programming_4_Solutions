'''
Kattis - karte
Simple problem, use set and dictionary to reduce code length.
Time: O(n), Space: O(1)
'''
s = input()
x = [s[i:i+3] for i in range(0, len(s), 3)]
if (len(list(set(x))) < len(x)):
    print("GRESKA")
    exit()

d = {'P': 13, 'K': 13, 'H': 13, 'T': 13}
for i in range(0, len(s), 3):
    d[s[i]] -= 1

print(d['P'], d['K'], d['H'], d['T'])