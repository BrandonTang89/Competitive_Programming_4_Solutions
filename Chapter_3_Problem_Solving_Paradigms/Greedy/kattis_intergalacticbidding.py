'''
Kattis - intergalacticbidding
Consider the sorted list of bets. Observe that if the largest bet is > s, we cannot take that as part of a
winning set. Observe that if it is <= s, we have to take it as part of a winning set since the sum of all
bets below it is < the largest bet. This is true because each smaller bet is <= half the bet larger than
itself. Thus, we have a greedy strategy to determine the 1 possible winning set. Note that if once we process
the entire list, we have not reduced s to 0, then there is no winning set.

Time: O(n log n), Space: O(n)'''
n, s = map(int, input().split())
v = []
for i in range(n):
    name, amt = input().split()
    amt = int(amt)
    v.append((amt, name))
    
v.sort(reverse=True)

winners = []
for i in range(n):
    amt, name = v[i]
    if s >= amt:
        winners.append(name)
        s -= amt
if s != 0:
    print(0)
    exit()

print(len(winners))
for w in winners:
    print(w)