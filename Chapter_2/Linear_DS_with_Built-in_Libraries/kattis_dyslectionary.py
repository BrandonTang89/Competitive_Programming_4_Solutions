'''
Kattis - dyslectionary
The sorting part is actually the easy part, the input formatting is honestly the hardest part. 
The sorting part is just about sorting based on reverse order of the word.

Time: O(n log n), Space: O(n)
'''
from sys import stdin

lines = stdin.readlines()
lines[-1] += ('\n')
lines.append("\n")

while len(lines) > 0:
    words = []
    max_len = 0
    while (lines[0] != "\n"):
        words.append(lines.pop(0).strip())
        max_len = max(max_len, len(words[-1]))
    lines.pop(0)
    
    words.sort(key= lambda x: x[::-1])
    
    for word in words:
        print(" " * (max_len - len(word)) + word)
    
    if (len(lines) > 0):
        print()