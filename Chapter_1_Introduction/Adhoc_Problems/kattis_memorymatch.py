'''
Kattis - memorymatch
Consider the 2 different corner cases and the rest is not too hard.

Time: O(num_opens), Space: O(n)
'''
n = int(input())
num_opens = int(input())
cards = {}

turned_off = set()
for i in range(num_opens):
    x, y, cx, cy = input().split()
    x, y = int(x), int(y)
    
    if not cx in cards:
        cards[cx] = set()
    if not cy in cards:
        cards[cy] = set()
    
    cards[cx].add(x)
    cards[cy].add(y)
    
    if cx == cy:
        turned_off.add(x)
        turned_off.add(y)

# Corner case where u know at least 1 of every type of card
if len(cards) == n//2:
    min_length = min(len(cards[c]) for c in cards)
    if min_length >= 1:
        print(n//2 - len(turned_off)//2)
        exit()
        
ans = 0
for x in cards:
    if len(cards[x]) == 2:
        for e in cards[x]:
            if e in turned_off:
                break
        else:
            ans += 1

if ans + len(turned_off)//2 == n//2 - 1:
    print(ans + 1) # Corner case where u have n-1 pairs already
    exit()

print(ans)