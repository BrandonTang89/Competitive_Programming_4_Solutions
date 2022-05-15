'''
Kattis - throwns
Use a stack to record previous egg positions. Use mod after every new throw.

Time: O(k), Space: O(k)
'''
n, k = map(int, input().split())
commands = input().split()
st = []
pos = 0

for i,c in enumerate(commands):
    if commands[i-1] == "undo":
        for j in range(int(c)):
            pos = st.pop() 
    elif c == "undo": continue
    else:
        st.append(pos)
        pos += int(c)    
        pos %= n

print(pos)