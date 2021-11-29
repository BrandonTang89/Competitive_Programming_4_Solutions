'''
Kattis - scrollingsign
Complete search to try to find the longest prefix of the next word that is a suffix of the current
big word.

Time: O(sum of (lengths of words^2)), Space: O(sum length of words)
'''
n = int(input())

for _ in range(n):
    k, w = map(int, input().split())
    s = ""
    for i in range(w):
        x = input()
        for j in range(len(x), 0, -1):
            if (s.endswith(x[:j])):
                s += x[j:]
                break
        if (not s.endswith(x)):
            s += x
    print(len(s))