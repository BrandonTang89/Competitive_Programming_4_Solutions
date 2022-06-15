'''Kattis - messages
Given the string, we determine the left-most position we can cut off from the left of the string such that the
cut off left part contains a word. Notice that this left-part will end with said word. We then repeat this
greedily. 

Time: O(len of s * num words * max length of word), Space: O(len of s + num words + max length of word)'''
words = []
while 1:
    s = input()
    if s == '#': break
    words.append(s)

while 1:
    s = ''
    while not s.endswith("|"):
        s += input()
        if s == '#': exit()
    
    ans = 0
    start = 0
    for i in range(len(s)): # we try to cut from start to i
        for word in words:
            if (s[start: i+1].endswith(word)):
                ans += 1
                start = i+1
                break
    print(ans)