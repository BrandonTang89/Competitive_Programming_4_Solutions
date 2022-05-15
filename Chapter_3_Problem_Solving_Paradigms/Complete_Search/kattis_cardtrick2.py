'''  Kattis - Cardtrick2
A precomputable complete search problem. Usually wouldn't use python for complete search problems but since its pre-computing
the slower speed is less of an issue.

Note that tqdm library is used to keep track of precomputation progress for sanity reasons

Time: O(1) for execution, O(n!) for each n to precompute
Mem: O(1) for execution, O(n) for each n to precompute
'''
import itertools
#from tqdm import tqdm

def check_val(deck,n):
    def move_card(temp_d):
        temp_d.append(temp_d[0])
        temp_d.pop(0)

    valid = True
    temp_d = deck
    for counter in range(1, n+1):
        for i in range(counter):
            move_card(temp_d)
        if (temp_d[0] != counter):
            valid = False
            break
        temp_d.pop(0)

    return valid

def precompute_deck(n):
    deck = []
    for i in range(1,n+1):
        deck.append(i)

    for deck_i in tqdm(itertools.permutations(deck)):
        #if deck_i[1] != 1 or deck_i[4] != 2 or deck_i[8] != 3: #valid speed up for n == 11 12 and 13
        #    continue
        if check_val(list(deck_i), n):
            print (deck_i)
            break

solutions = [
(1),
(2, 1),
(3, 1, 2),
(2, 1, 4, 3),
(3, 1, 4, 5, 2),
(4, 1, 6, 3, 2, 5),
(5, 1, 3, 4, 2, 6, 7),
(3, 1, 7, 5, 2, 6, 8, 4),
(7, 1, 8, 6, 2, 9, 4, 5, 3),
(9, 1, 8, 5, 2, 4, 7, 6, 3, 10),
(5, 1, 6, 4, 2, 10, 11, 7, 3, 8, 9),
(7, 1, 4, 9, 2, 11, 10, 8, 3, 6, 5, 12),
(4, 1, 13, 11, 2, 10, 6, 7, 3, 5, 12, 9, 8)]

t = int(input())
for i in range(t):
    n = int(input())
    ans = ""
    if n > 1:
        for j in solutions[n-1]:
            ans += str(j) + " "
    else:
        ans = "1 "
    
    print(ans[:-1])

