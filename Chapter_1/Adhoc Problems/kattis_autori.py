'''
Kattis - Autori
Simple string tokenisation followed by extraction of first char
'''
line = [i[0] for i in input().split('-')]
ans = ""
for i in line:
    ans += i

print (ans)