'''
Kattis - alphabetspam
Just check what kind of char each char is.

Time: O(len(s)), Space: O(len(s))
'''
s = input()

d = {
    "white_space": 0,
    "upper": 0,
    "lower": 0,
    "symbol": 0,
}

for c in s:
    if (c.islower()):
        d["lower"] += 1
    elif (c.isupper()):
        d["upper"] += 1
    elif (c == '_'):
        d["white_space"] += 1
    else:
        d["symbol"] += 1
    
s = sum(d.values())
print(d["white_space"] / s)
print(d["lower"] / s)
print(d["upper"] / s)
print(d["symbol"] / s)