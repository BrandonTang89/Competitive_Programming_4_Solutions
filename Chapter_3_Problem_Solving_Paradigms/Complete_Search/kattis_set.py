'''
Kattis - set
Mostly reading comprehension...

Time: O(1), Space: O(1)
'''
arr = []
for i in range(4):
    arr.extend(list(input().split()))

hasset = False
for i in range(12):
    for j in range(i+1, 12):
        for k in range(j+1, 12):
            for l in range(4):
                if (arr[i][l] == arr[j][l] and arr[i][l] == arr[k][l]):
                    continue
                if (arr[i][l] == arr[j][l] or arr[i][l] == arr[k][l] or arr[j][l] == arr[k][l]):
                    break
            else:
                print(i+1, j+1, k+1)
                hasset = True

if not hasset:
    print('no sets')
                
