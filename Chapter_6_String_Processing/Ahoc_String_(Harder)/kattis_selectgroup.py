'''
Kattis - selectgroup
A fun little recursive descent parser. Heavy use of Python's built-in set makes life
much easier.

Time: O(num_queries * total number of people), Space: O(num_queries * number of people)
'''
from sys import stdin

lines = stdin.readlines()
groups = {}
while lines[0].startswith('group'):
    arr = lines[0].split()
    lines.pop(0)
    groups[arr[1]] = arr[3:]

for line in lines:
    inputStream = line.split()

    def parse():
        if inputStream[0] in groups:  # if it is a group
            group = inputStream.pop(0)
            return set(groups[group])

        action = inputStream.pop(0)
        if action == "union":
            return parse().union(parse())
        elif action == "intersection":
            return parse().intersection(parse())
        elif action == "difference":
            return parse().difference(parse())
        else:
            assert False, "Unknown action: " + action

    print(" ".join(sorted(parse())))
