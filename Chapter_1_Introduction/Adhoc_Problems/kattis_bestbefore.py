'''
Kattis - bestbefore
Annoying time problem. Be careful and it should be okay.

Time: O(1), Space: O(1)
'''
import datetime
import itertools
s = input()
arr = s.split('/')
arr = [int(x) for x in arr]

cur_best = None
max_date = datetime.date(2999, 12, 31)
for per in itertools.permutations(arr):
    # [year, month, day]
    year, month, day = per[0], per[1], per[2]
    if year < 2000:
        year += 2000
    
    # print(year, month, day)
    try:
        cur = datetime.date(year=year,month=month,day=day)
    except:
        continue
    if cur > max_date:
        continue
    
    if cur_best is None:
        cur_best = cur
    elif cur_best > cur:
        cur_best = cur

if cur_best is None:
    print(f"{s} is illegal")
else:
    print(cur_best.strftime("%Y-%m-%d"))