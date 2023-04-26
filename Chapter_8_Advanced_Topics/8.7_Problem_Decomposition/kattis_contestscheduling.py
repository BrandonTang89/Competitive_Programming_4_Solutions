'''
Kattis - contestscheduling
Adhoc + dp problem. The first part is just to generate all the possible fridays in october for the given years.
The DP part is quite simple, let dp(cur_date) be the sum of surprises for all the years after cur_date.year.
We transition to the next year by trying all the fridays in the next year that are not forbidden and take the minimum.

Time: O(z*32 + z*4) = O(z), Space: O(z)
'''
import datetime 
import functools
z = int(input())
f = int(input())
# generate a list of all fridays in october [2019 to 2018 + z]

forbidden = set()
for _ in range(f):
    y, m, d = map(int, input().split())
    forbidden.add(datetime.date(y, m, d))
fridays = {}
for y in range(2019, 2018 + z + 1):
    cnt = 0
    for d in range(1, 32):
        date = datetime.date(y, 10, d)
        if date.weekday() == 0:
            cnt += 1
            if (cnt == 2): 
                blocked_friday = date - datetime.timedelta(days=3)
                assert blocked_friday.weekday() == 4
                break
    
    fridays[y] = []
    for d in range(1, 32):
        date = datetime.date(y, 10, d)
        if date.weekday() == 4 and date != blocked_friday:
            fridays[y].append(date)
            
            
@functools.lru_cache(maxsize=None)     
def dp(cur_date: datetime.date):
    if (cur_date.year == 2018 + z): return 0 # base case
    
    ans = int(1e9)
    for ndate in fridays[cur_date.year + 1]:
        if ndate in forbidden: continue
        ans = min(ans, dp(ndate) + (ndate.day - cur_date.day)**2)
    return ans

print(dp(datetime.date(2018, 10, 12)))

def printsol(cur_date: datetime.date):
    if (cur_date.year > 2018):
        print(f"{cur_date.year} {cur_date.month} {cur_date.day:02d}")
    if (cur_date.year == 2018 + z): return # base case
    
    for ndate in fridays[cur_date.year + 1]:
        if ndate in forbidden: continue
        if dp(ndate) + (ndate.day - cur_date.day)**2 == dp(cur_date):
            printsol(ndate)
            return
        
printsol(datetime.date(2018, 10, 12))