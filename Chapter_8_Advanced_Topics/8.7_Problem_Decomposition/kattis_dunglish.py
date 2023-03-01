'''
Kattis - dunglish
Relatively easy math + hashtable problem. To get the total number of translations, we just find the product of the number of translations
of each word (regardless of whether it is correct or incorrect). To get the number of correct translations, we find the product of the
number of correct translations of each word. Incorrect = total - correct.

We should also record a single translation of each word for the case where total = 1.

Time: O(n + m), Mem: O(n + m)
'''
n = int(input())
s = input().split()
m = int(input())
correct = {}
incorrect = {}
single_translation = {}

for _ in range(m):
    dutch, eng, correct_or_incorrect = input().split()
    single_translation[dutch] = eng
    if correct_or_incorrect == "correct":
        if dutch not in correct:
            correct[dutch] = 0
        correct[dutch] += 1
    else:
        if dutch not in incorrect:
            incorrect[dutch] = 0
        incorrect[dutch] += 1

total = 1
num_correct = 1
for word in s:
    if word in correct:
        num_correct *= correct[word]
    else:
        num_correct = 0
        
    if (word not in correct):
        correct[word] = 0
    if (word not in incorrect):
        incorrect[word] = 0
    if word in incorrect:
        total *= (incorrect[word]+correct[word])

if (total == 1):
    print(' '.join([single_translation[word] for word in s]))
    if (num_correct == 1):
        print("correct")
    else:
        print("incorrect")
else:
    print(num_correct, "correct")
    print(total - num_correct, "incorrect")