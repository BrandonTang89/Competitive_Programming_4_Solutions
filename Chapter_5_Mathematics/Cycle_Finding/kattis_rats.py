'''
Kattis - rats
Actually not too hard of a problem with Python since we can do all the operations required pretty
easily, including big integer arithmetic. There are also a lot of nice string processing tools
like endswith, startswith and checking whether all the chars of a string are the same.

Time: O(m * (log(m) +  length(x) * log(length(x)))), Space: O(m)

'''
num_tc = int(input())

def check_creeper(x):
    if (x.startswith("1233") and x.endswith("34444")):
        x = x[3:-4]
        return x == len(x) * x[0]
    if (x.startswith("5566") and x.endswith("67777")):
        x = x[3:-4]
        return x == len(x) * x[0]
    return False

def rats(x):
    rev = x[::-1]
    x = int(x)
    rev = int(rev)
    
    x = x + rev
    x = list(str(x))
    x.sort()
    x = "".join(x)
    return str(int(x))

for tc in range(1, num_tc+1):
    tc, m, x = map(int, input().split())
    x = str(x)
    
    creeper = False
    repeat = False
    visited_nums = set()
    for i in range(1,m+1):
        # print(i, x)
        if (check_creeper(x)):
            print(f"{tc} C {i}")
            creeper = True
            break
        if (x in visited_nums):
            print(f"{tc} R {i}")
            repeat = True
            break
        
        visited_nums.add(x)
        if (i != m):
            x = rats(x)
    
    if (not (creeper or repeat)):
        print(f"{tc} {x}")
        
    