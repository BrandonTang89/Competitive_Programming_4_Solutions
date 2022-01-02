'''
Kattis - chopin
ngl all these adhoc problems which just mainly involve copying a hashmap from the question are
getting kinda boring.

Time: O(n), Space: O(1)
'''
alternates = {
    "Ab": "G#",
    "G#": "Ab",
    "F#": "Gb",
    "Gb": "F#",
    "D#": "Eb",
    "Eb": "D#",
    "C#": "Db",
    "Db": "C#",
    "A#": "Bb",
    "Bb": "A#",
}

from sys import stdin
for index,line in enumerate(stdin):
    a, b = line.split()
    if a in alternates:
        print(f"Case {index+1}: {alternates[a]} {b}")
    else:
        print(f"Case {index+1}: UNIQUE")