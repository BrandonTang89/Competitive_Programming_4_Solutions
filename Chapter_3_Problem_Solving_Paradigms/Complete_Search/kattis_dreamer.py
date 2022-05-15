'''
Kattis - dreamer
Relatively straightforward complete search problem. Use python datetime libary to ensure a valid
date and to easily compare dates. Use set to prevent duplicates. 

Time: O(8!), Space: O(8!)
'''
import itertools
import datetime

def process(x):
    x = str(x)
    if (len(x) == 1):
        x = '0' + x
    return x

num_tc = int(input())
for _ in range(num_tc):
    x = "".join(input().split())
    x = list(x)
    
    best_date = None
    ans = 0
    # print(x)
    s = set()
    for i in itertools.permutations(x):
        day = i[0] + i[1]
        month = i[2] + i[3]
        year = i[4] + i[5] + i[6] + i[7]
        
        try:
            d = datetime.date(int(year), int(month), int(day))
        except:
            continue
        
        if (d < datetime.date(2000, 1,1)):
            continue
        
        if (d in s):
            continue
        s.add(d)
        if best_date == None:
            best_date = d
        elif d < best_date:
            best_date = d
        
        ans+= 1
         
    
    print(ans, end=" ")
    if (best_date != None):
        print(process(best_date.day), process(best_date.month), process(best_date.year), end="")
    print()