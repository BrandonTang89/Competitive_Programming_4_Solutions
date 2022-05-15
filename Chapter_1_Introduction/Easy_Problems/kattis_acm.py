'''
Kattis - acm
Just follow instructions. They might try to submit solutions for question that have already
been solved.

Time: O(n), Space: O(n)
'''
arr = []
while True:
    a = input()
    if a == '-1': break 
    else: arr.append(a.split())

solved = set()
tp = 0
hashmap = {}
for a in arr:
    if a[-1] == "right":
        if a[1] in solved: continue
        solved.add(a[1])
        tp += int(a[0])
        if a[1] in hashmap:
            tp += hashmap[a[1]] * 20
        
    else:
        if not a[1] in hashmap:
            hashmap[a[1]] = 0
        hashmap[a[1]] += 1

print(len(solved), tp)