'''
Kattis - eatingout
We split each of the m options into 2 virtual items corresponding to the fact that each item can only be chosen by up to 2 people.
Then we just check if it possible for each person to choose a disjoint set of these 2m virtual items.

Time: O(1), Space: O(1)
'''
m, a, b, c = map(int, input().split())
print('possible' if a+b+c <= 2*m else 'impossible')