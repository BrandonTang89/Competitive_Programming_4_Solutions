'''
Kattis - exam
Though listed as a DP question, since the order of the questions doesn't matter, we can reduce the state
to just (number of answers that are the same, number of answers that friend got correct) and then use math
to solve.

Time: O(n), Space: O(1)
'''
num_correct = int(input())
friend = input()
me = input()

num_same = sum(1 if friend[i] == me[i] else 0 for i in range(len(friend))) 

print(len(friend) - abs(num_correct - num_same))