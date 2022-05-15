'''
Kattis - musicalnotation
Note that tedious. Just follow the question. 

Time: O(n), Space: O(n)
'''
ans = {
    "G": "G: ",
    "F": "F: ",
    "E": "E: ",
    "D": "D: ",
    "C": "C: ",
    "B": "B: ",
    "A": "A: ",
    "g": "g: ",
    "f": "f: ",
    "e": "e: ",
    "d": "d: ",
    "c": "c: ",
    "b": "b: ",
    "a": "a: ",
}

auto_line = {"F", "D", "B", "g", "e", "a"}
n = int(input())
notes = input().split()

for note in notes:
    if len(note) == 1:
        letter = note[0]
        length = 1
    else:
        letter, length = note[0], note[1]
    
    length = int(length)
    for l in ans:
        if letter == l:
            ans[l] += "*" * length
        else:
            ans[l] += ("-" if l in auto_line else " ") * length
            
    letter = "_ "
    length = 1
    for l in ans:
        if letter == l:
            ans[l] += "*" * length
        else:
            ans[l] += ("-" if l in auto_line else " ") * length    
for l in ans:
    print(ans[l][:-1])