'''
Kattis - rhyming
Relatively easy, for each set, determine if the common word has any of the words as a suffix, if so,
put add all the words into a set of eligible suffixes. For each phrase, extract the last word and
test all possible suffixes for presence within the set of eligible suffixes.

Time: O(num_phrases * len(last word) * num_suffixes)
Space: O(num_suffixes)
'''
common = input()
num_sets = int(input())
eligible_suffixes = set()

for _ in range(num_sets):
    candidate_set = input().split()
    
    accepted = False
    for candidate in candidate_set:
        if (common.endswith(candidate)):
            accepted = True
            break
        
    if (accepted):
        for candidate in candidate_set:
            eligible_suffixes.add(candidate)

num_tests = int(input())
for _ in range(num_tests):
    word = input().split()[-1]
    yes = False
    for i in range(len(word)):
        if (word[i:] in eligible_suffixes):
            yes = True
            break
    print("YES" if yes else "NO")