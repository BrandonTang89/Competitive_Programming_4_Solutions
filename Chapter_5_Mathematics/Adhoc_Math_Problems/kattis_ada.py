'''
kattis - ada
A good observation to make is that the next element is just the sum of the last element of 
all the computed layers.

The main difficulty for this problem is not thinking of the solution but rather just implementing it.
We use a 2D array to store all the layers of differences. Note however that we could improve memory
complexity by only storing the last layer of differences and the last element of each previous layer.
This is not too important though since there are at most 10 layers.

Time: O(n), Space: O(n^2)
'''
arr = list(map(int, input().split()))
arr.pop(0);

memo = [arr]
for i in range(100000): # to INF
    new_layer = []
    const_diff = memo[i][1] - memo[i][0]
    continue_flag = False
    for j in range(len(memo[i]) - 1):
        new_layer.append(memo[i][j+1] - memo[i][j])
        if (new_layer[j] != const_diff): # there is a difference not the same as the constant difference
            continue_flag = True
    
    memo.append(new_layer)
    if (not continue_flag):
        break

next_item = 0
for i in range(len(memo)):
    next_item += memo[i][-1]
print(len(memo) - 1, next_item)