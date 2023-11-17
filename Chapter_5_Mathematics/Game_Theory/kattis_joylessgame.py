'''
Kattis - joylessgame
A game theory problem with a constructive solution. If the terminal letters are different then playing when the length is even is a losing position.
After playing any move, the opponent will always be able to play a move going from the rightmost to leftmost letter and choosing the first 
possible valid letter to remove. This must exist (its up to u to check out case analysis). On the otherhand, if the terminal letters are the same,
then playing when the length is odd is a losing position. 

Time: O(1), Space: O(1)
'''
t = int(input())

for _ in range(t):
    s = input()
    if (s[0] == s[-1]):
        firstWin = (len(s) % 2 == 0)
    else:
        firstWin = (len(s) % 2 == 1)
    
    if (firstWin):
        print("Chikapu")
    else:
        print("Bash")