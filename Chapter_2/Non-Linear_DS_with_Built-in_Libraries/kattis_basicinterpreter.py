'''
Kattis - basicintepreter
Rather tedious and annoying question. Note that we can't use space splitting on the line and then
rejoin the string if we are printing a string literal as there might be more than 1 space in a
row. Note how we simulate a 32 bit signed integer with some mathematics here.

Time: O(INF), Space: O(1)
'''
from sys import stdin
import re
lines = stdin.readlines() 
lines = [line.strip() for line in lines]
lines = [(int(line.split()[0]), line.split()[1], line) for line in lines]
lines.sort()
# Initilise all variables A to Z to 0
var = {
    'A': 0,
    'B': 0,
    'C': 0,
    'D': 0,
    'E': 0,
    'F': 0,
    'G': 0,
    'H': 0,
    'I': 0,
    'J': 0,
    'K': 0,
    'L': 0,
    'M': 0,
    'N': 0,
    'O': 0,
    'P': 0,
    'Q': 0,
    'R': 0,
    'S': 0,
    'T': 0,
    'U': 0,
    'V': 0,
    'W': 0,
    'X': 0,
    'Y': 0,
    'Z': 0,
}
line_map = {}
for i,l in enumerate(lines):
    line_map[l[0]] = i

def arithmetic_statement(s):
    # print("S: ", s)
    if (s[0].isupper()):
        s[0] = var[s[0]]
    if (len(s) == 1):
        ans = int(s[0])
        return (ans & 0xffffffff) - ((1 << 32) if ans & (1 << 31) else 0)
    
    if (s[2].isupper()):
        s[2] = var[s[2]]
        
    if (s[1] == '+'):
        ans = int(s[0]) + int(s[2])
    elif (s[1] == '-'):
        ans = int(s[0]) - int(s[2])
    elif (s[1] == '*'):
        ans = int(s[0]) * int(s[2])
    elif (s[1] == '/'):
        ans = int(int(s[0]) / int(s[2]))

    # print("ANS: ", ans)
    return (ans & 0xffffffff) - ((1 << 32) if ans & (1 << 31) else 0)

def process_condition(c):
    # print("C", c)
    if (c[0].isupper()):
        c[0] = var[c[0]]
    if (c[2].isupper()):
        c[2] = var[c[2]]
    
    if (c[1] == '<'):
        return int(c[0]) < int(c[2])
    if (c[1] == '>'):
        return int(c[0]) > int(c[2])
    if (c[1] == "="):
        return int(c[0]) == int(c[2])
    if (c[1] == '<='):
        return int(c[0]) <= int(c[2])
    if (c[1] == '>='):
        return int(c[0]) >= int(c[2])
    if (c[1] == '<>'):
        return int(c[0]) != int(c[2])
    
cur_line = 0
while (cur_line < len(lines)):
    # Execute the line
    line = lines[cur_line]
    line_args = line[2].split()[2:]
    
    if line[1] == 'LET':
        var[line_args[0]] = arithmetic_statement(line_args[2:])
    elif line[1] == 'PRINT' or line[1] == 'PRINTLN':
        if line[2][-1] == '"':
            print_obj = re.findall('"([^"]*)"', line[2])[0]
            print(print_obj, end=('' if line[1] == 'PRINT' else '\n'))
        else:
            print_obj = line_args[0]
            print(var[print_obj], end=('' if line[1] == 'PRINT' else '\n'))
    elif line[1] == 'IF':
        accepted = process_condition(line_args[0:3])
        
        if (accepted):
            cur_line = line_map[int(line_args[-1])]
            continue
    cur_line += 1