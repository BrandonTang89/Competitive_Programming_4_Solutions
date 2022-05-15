'''
Kattis - toilet
Linear simulation 3 times.

Time: O(n), Space: O(n)
'''
arr = list(input())
init = arr[0]
arr.pop(0)
arr = ''.join(arr)

# First policy: Everyone puts the seat up
ans = 0
cur_state = init
for c in arr:
    if cur_state != c:
        ans += 1
        cur_state = c
    
    if cur_state != 'U':
        ans += 1
        cur_state = 'U'
print(ans)

# Second policy: Everyone puts the seat down
ans = 0
cur_state = init
for c in arr:
    if cur_state != c:
        ans += 1
        cur_state = c
    
    if cur_state != 'D':
        ans += 1
        cur_state = 'D'
print(ans)


# Third policy, based on preference
ans = 0
cur_state = init
for c in arr:
    if cur_state != c:
        ans += 1
    
    cur_state = c
print(ans)