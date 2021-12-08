'''
Kattis - delimitersoup
Did you know that you could use else after a for loop which runs if the loop does not break??
Well the more your know huh...

Time: O(n), Space: (n)
'''
brackets = {
    "(" : ")",
    "[" : "]",
    "{" : "}",
}

n = int(input())
s = input()

st = []
for i,c in enumerate(s):
    if (c == " "): continue
    if c in brackets:
        st.append(c)
    else:
        if len(st) == 0:
            print(c, i)
            break
        if brackets[st.pop()] != c:
            print(c, i)
            break
else:
    print("ok so far")