'''
Kattis - battlesimulation
Something like a sliding window. Note to use ans as a list rather than a string since string + string takes O(length of combined string) to do.

Time: O(n), Space: O(n)
'''
s = input()

hashmap = {
    "RBL",
    "RLB",
    "LRB",
    "LBR",
    "BLR",
    "BRL"
}
hashmap2 = {
    'R': 'S',
    'B': 'K',
    'L': 'H',
}
ans =  [""]
q = ""
for c in s:
    if len(q) < 2:
        q += c
        continue
    q += c
    if q in hashmap:
        ans.append('C')
        q = ""
    else:
        ans.append( hashmap2[q[0]])
        q = q[1:]

for c in q:
    ans.append(hashmap2[c])
print("".join(ans))
