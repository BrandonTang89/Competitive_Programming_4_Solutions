'''
Kattis - bela
Simple syntax problem.

Time: O(n), Space: O(1)
'''
cards = {
    "A": [11, 11],
    "K": [4, 4],
    "Q": [3, 3],
    "J": [20, 2],
    "T": [10, 10],
    "9": [14, 0],
    "8": [0, 0],
    "7": [0, 0],
}

n, trump = input().split()
n = int(n)

total = 0
for i in range(4 *n):
    card = list(input())
    total += cards[card[0]][not card[1] == trump]
print(total)