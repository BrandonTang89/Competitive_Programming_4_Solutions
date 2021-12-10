'''
Kattis - anewalphabet
Very straightforward chracter replacement problem. 

Time: O(len(s)), Space: O(len(s))
'''
alphabet = {
    "a": "@",
    "b": "8",
    "c": "(",
    "d": "|)",
    "e": "3",
    "f": "#",
    "g": "6",
    "h": "[-]",
    "i": "|",
    "j": "_|",
    "k": "|<",
    "l": "1",
    "m": "[]\/[]",
    "n": "[]\[]",
    "o": "0",
    "p": "|D",
    "q": "(,)",
    "r": "|Z",
    "s": "$",
    "t": "']['",
    "u": "|_|",
    "v": "\/",
    "w": "\/\/",
    "x": "}{",
    "y": "`/",
    "z": "2"
}

s = input()
s = s.lower()
s = [alphabet[i] if i in alphabet else i for i in s]
print("".join(s))