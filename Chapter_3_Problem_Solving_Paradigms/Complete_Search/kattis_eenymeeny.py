'''
Kattis - eenymeeny
Josephus problem simulation.
 
Time: O(n), Space: O(n)
'''
p = len(input().split()) -1
n = int(input())
people = [input() for _ in range(n)]

a = []
b = []

cur_pos = 0
cur_team = 0
while len(people) > 0:
    cur_pos += p
    cur_pos %= len(people)
    if cur_team == 0:
        a.append(people[cur_pos])
    else:
        b.append(people[cur_pos])
    cur_team = 1 - cur_team
    
    people.remove(people[cur_pos])
    if (len(people) == 0):
        break
    cur_pos = cur_pos % len(people)

print(len(a))
for i in a:
    print(i)
print(len(b))
for i in b:
    print(i)