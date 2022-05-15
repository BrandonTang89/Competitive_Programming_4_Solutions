'''
Kattis - shuffling
If you didn't already know, you can store functions into variables.

Time: O(?), Space: O(n)
'''
def outshuffle(cards):
    n = len(cards)
    left = cards[:(n+1)//2]
    right = cards[(n+1)//2:]
    
    new_cards = []
    for i in range(n):
        if i % 2 == 0:
            new_cards.append(left.pop(0))
        else:
            new_cards.append(right.pop(0))
    return new_cards
    
def inshuffle(cards):
    n = len(cards)
    left = cards[:(n//2)]
    right = cards[(n//2):]
    
    new_cards = []
    for i in range(n):
        if i % 2 == 1:
            new_cards.append(left.pop(0))
        else:
            new_cards.append(right.pop(0))
    return new_cards

n, shuffle = input().split()
shuffle = outshuffle if shuffle == "out" else inshuffle

cards = [i for i in range(int(n))]
cards = shuffle(cards)
count = 1
while cards != sorted(cards):
    cards = shuffle(cards)
    count += 1
print(count)