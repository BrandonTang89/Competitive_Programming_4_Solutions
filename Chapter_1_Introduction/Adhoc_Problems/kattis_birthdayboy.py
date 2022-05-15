'''
Kattis - birthdayboy
annoying time problem.

Time: O(n), Space: O(1)
'''
import datetime

year = datetime.timedelta(days=365) # 365 days
soy = datetime.date(2001, 1, 1)
tdy = datetime.date(2001, 10, 27)

n = int(input())
mini = 400
arr = [0 for _ in range(365)]
for i in range(n):
    _, d = input().split()
    d = d.split('-')
    d = datetime.date(2001, int(d[0]), int(d[1]))
    
    x = (d - soy).days
    arr[x] = 1
    mini = min(mini, x)

# print(arr)
pt = (mini + 1) % 365
counter = 0 # counts how many days since last birthday
best_day, best_counter = 0, 0
while pt != mini:
    if arr[pt] == 1:
        counter = 0
    else:
        counter += 1
    
    cur = soy + datetime.timedelta(days=pt)
    if cur <= tdy:
        cur += year
        
    # print(cur)
        
    # print(cur, counter)
    if counter > best_counter:
        best_day = cur
        best_counter = counter
    elif counter == best_counter and best_counter > 0:
        if cur < best_day:
            best_day = cur
        
    pt = (pt + 1) % 365
    
print(best_day.strftime("%m-%d"))