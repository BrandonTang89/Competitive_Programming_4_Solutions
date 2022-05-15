'''
Kattis - irepeatmyself
More or less complete search for each prefix of the input string. Use math to figure out how big n
must be for p*n to be longer than s.

Time: O(len(s) * n), Space: O(len(s))
'''

n = int(input())

for _ in range(n):
    s = input()
    
    for i in range(1,len(s)+1):
        p = s[:i]
        n = (len(s) // i) + 1
        
        if ((p*n).startswith(s)):
            print(i)
            break