'''
Kattis - smartphone
The key part is to efficiently determine the length of the common prefix, we can do that in O(n) time.
After that, we note that we will only use the suggestion once at the start and never again (if 
we used it after pressing a non-zero number of buttons, we could improve the solution by just pressing
it once at the start). 

Time: O(max length of string), Space: O(1)
'''
def manual_match(cur, target):
    common_prefix_length = 0
    for i in range(min(len(cur), len(target))):
        if (cur[i] == target[i]):
            common_prefix_length = i+1
        else:
            break
    
    ans = len(cur) - 2*common_prefix_length + len(target) 
    return ans

num_tc = int(input())
for _ in range(num_tc):
    target = input()
    cur = input()
    
    ans = manual_match(cur, target)
    for i in range(3):
        suggestion = input()
        ans = min(ans, 1 + manual_match(suggestion, target))
    
    print(ans)