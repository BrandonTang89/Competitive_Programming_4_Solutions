'''
Kattis - battlesimulation
Something like a sliding window.

Time: O(n), Space: O(n)
'''
s = input()
s = s.replace('R', 'S')
s = s.replace('L', 'H')
s = s.replace('B', 'K')

hashmap = {
    "SKH",
    "SHK",
    "HSK",
    "HKS",
    "KHS",
    "KSH"
}
ans = ""
q = ""
for c in s:
    if len(q) < 2:
        q += c
        continue
    q += c
    if q in hashmap:
        ans += 'C'
        q = ""
    else:
        ans += q[0]
        q = q[1:]

ans += q
print(ans)