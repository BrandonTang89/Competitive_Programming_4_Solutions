'''
Kattis - shiritori
We use a hashtable to keep track of words used. 

Time: O(n), Space: O(n)
'''
n = int(input())
S = set()

prev = ""
for i in range(n):
    s = input()
    if ((prev != "" and s[0] != prev[-1]) or s in S):
        # lost
        print(f"Player { i % 2 + 1 } lost")
        break

    S.add(s)
    prev = s
else:
    print("Fair Game")