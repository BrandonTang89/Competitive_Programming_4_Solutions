from itertools import combinations

def is_palindrome(seq):
    return seq == seq[::-1]

def g(arr):
    subsequences = []
    for i in range(1, len(arr) + 1):
        subsequences.extend(combinations(arr, i))

    palindromic_subsequences = [seq for seq in subsequences if is_palindrome(seq)]

    max_length = max(len(seq) for seq in palindromic_subsequences)
    longest_palindromic_subsequences = [seq for seq in palindromic_subsequences if len(seq) == max_length]
    count_longest_palindromic_subsequences = len(longest_palindromic_subsequences)

    return count_longest_palindromic_subsequences

for _ in range(int(input())):
    n = int(input())
    
    if n == 6:
        print("1 1 2 3 1 2")
    elif n == 7:
        print("1 1 2 1 3 2 2")
    elif n == 8:
        print("2 1 1 2 1 2 2 1")
        
    else:
        if n % 2 == 0: # even case
            # 3 4 5 6 ... (2 1 1 2 1 2 2 1) ... 5 6 3 4
            arr = [0] * n
            for i in range(0,(n-8) // 2, 2):
                arr[i] = i + 3
                arr[i + 1] = i + 4
                
                arr[n - i - 2] = i + 3
                arr[n - i - 1] = i + 4
                
            arr[(n-8) // 2] = 2
            arr[(n-8) // 2 + 1] = 1
            arr[(n-8) // 2 + 2] = 1
            arr[(n-8) // 2 + 3] = 2
            arr[(n-8) // 2 + 4] = 1
            arr[(n-8) // 2 + 5] = 2
            arr[(n-8) // 2 + 6] = 2
            arr[(n-8) // 2 + 7] = 1
            
        else:
            # 3 4 5 6 ... (2 1 1 2 (n) 1 2 2 1) ... 5 6 3 4
            arr = [0] * n
            for i in range(0,(n-9) // 2, 2):
                arr[i] = i + 3
                arr[i + 1] = i + 4
                
                arr[n - i - 2] = i + 3
                arr[n - i - 1] = i + 4
            
            arr[(n-9) // 2] = 2
            arr[(n-9) // 2 + 1] = 1
            arr[(n-9) // 2 + 2] = 1
            arr[(n-9) // 2 + 3] = 2
            arr[(n-9) // 2 + 4] = n
            arr[(n-9) // 2 + 5] = 1
            arr[(n-9) // 2 + 6] = 2
            arr[(n-9) // 2 + 7] = 2
            arr[(n-9) // 2 + 8] = 1
            
        print(' '.join(map(str, arr)))
            
