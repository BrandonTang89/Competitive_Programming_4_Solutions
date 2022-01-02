'''
Kattis - gamerank
Another timewaster type problem. This is the hearthstone ranking system, a lot of random
things to note and implement.

Time: O(n), Space: O(1)
'''
s = input()

arr = []
for i in range(5):
    arr.append(2)
for i in range(5):
    arr.append(3)
for i in range(5):
    arr.append(4)
for i in range(10):
    arr.append(5)

legend = False
num_star = 0
cur_rank = 25
streak = 0
for c in s:
    
    if c == 'W':
        streak += 1
        num_star += 2 if (streak >= 3 and cur_rank >= 6) else 1
        
        if num_star > arr[25 - cur_rank]:
            num_star -= arr[25 - cur_rank]
            cur_rank -= 1
            if cur_rank == 0:
                legend = True
                break
    else:
        streak = 0
        if cur_rank <= 20:
            num_star -= 1
            if num_star < 0:
                cur_rank += 1
                num_star = arr[25 - cur_rank] - 1
            
            if cur_rank > 20:
                cur_rank = 20
                num_star = 0

if legend:
    print("Legend")
    exit()

print(cur_rank)